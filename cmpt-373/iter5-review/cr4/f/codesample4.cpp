class ASTNode {
public:
  int getChildrenCount() const { return this->numChildren; }
  std::vector<ASTNode *> getChildren() {
    std::vector<ASTNode *> returnValue;
    for (auto &x : children) {
      returnValue.push_back(x.get());
    }
    return returnValue;
  }
  const ASTNode &getParent() const { return *parent; }
  void setParent(ASTNode *parent) { this->parent = parent; }
  coro::Task<> accept(ASTVisitor &visitor) {
    auto coroutine = acceptHelper(visitor);
    while (not coroutine.isDone()) {
      co_await coroutine;
    }
  }
  virtual ~ASTNode(){};

protected:
  std::vector<std::unique_ptr<ASTNode>> children;
  ASTNode *parent;
  int numChildren;
  void appendChild(std::unique_ptr<ASTNode> &&child) {
    children.push_back(std::move(child));
  }

private:
  virtual coro::Task<> acceptHelper(ASTVisitor &visitor) = 0;
};

class AST {
public:
  AST(std::unique_ptr<ASTNode> &&root) : root{std::move(root)} {}
  const ASTNode &getParent() const { return *root; }
  void setRoot(std::unique_ptr<ASTNode> &&root) { root.swap(this->root); }
  coro::Task<> accept(ASTVisitor &visitor) {
    auto coroutine = root->accept(visitor);
    while (not coroutine.isDone()) {
      co_await coroutine;
    }
  }

private:
  std::unique_ptr<ASTNode> root;
};

class ASTVisitor {
public:
  explicit ASTVisitor() = default;
  coro::Task<> visit(GlobalMessage &node);
  coro::Task<> visit(FormatNode &node);
  // More visit nodes...
  virtual ~ASTVisitor() = default;

private:
  virtual coro::Task<> visitHelper(GlobalMessage &) = 0;
  virtual coro::Task<> visitHelper(FormatNode &) = 0;
  // More visit helpers...
};

class Interpreter : public ASTVisitor {
public:
  Interpreter(PopulatedEnvironment &&env, Communicator &communicator)
      : environment{std::move(env.envPtr)}, players{std::move(env.players)},
        communicator{communicator} {}

private:
  coro::Task<> visitHelper(GlobalMessage &node) override {
    visitEnter(node);
    for (auto &&child : node.getChildren()) {
      co_await child->accept(*this);
    }
    visitLeave(node);
    co_return;
  }
  coro::Task<> visitHelper(FormatNode &node) override {
    visitEnter(node);
    for (auto &&child : node.getChildren()) {
      co_await child->accept(*this);
    }
    visitLeave(node);
    co_return;
  }
  // More helpers...

  void visitEnter(GlobalMessage &node){};
  void visitLeave(GlobalMessage &node) {
    const auto &formatMessageNode = node.getFormatNode();
    auto &&formatMessage = formatMessageNode.getFormat();
    communicator.sendGlobalMessage(formatMessage);
  };

  void visitEnter(FormatNode &node){};
  void visitLeave(FormatNode &node){};
  // More visitEnters and visitLeaves...

private:
  std::unique_ptr<Environment> environment;
  PlayerList players;
  Communicator &communicator;
}

class FormatNode : public ASTNode { // parser complete
public:
  explicit FormatNode(std::string format) : format{std::move(format)} {}
  const std::string &getFormat() const { return format; }

private:
  virtual coro::Task<> acceptHelper(ASTVisitor &visitor) override;
  std::string format;
};

class GlobalMessage : public ASTNode { // parser complete
public:
  explicit GlobalMessage(std::unique_ptr<FormatNode> &&formatNode) {
    appendChild(std::move(formatNode));
  }
  const FormatNode &getFormatNode() const {
    return *static_cast<FormatNode *>(children[0].get());
  }

private:
  virtual coro::Task<> acceptHelper(ASTVisitor &visitor) override;
};

coro::Task<> GlobalMessage::acceptHelper(ASTVisitor &visitor) {
  auto coroutine = visitor.visit(*this);
  while (not coroutine.isDone()) {
    co_await coroutine;
  }
}

coro::Task<> FormatNode::acceptHelper(ASTVisitor &visitor) {
  auto coroutine = visitor.visit(*this);
  while (not coroutine.isDone()) {
    co_await coroutine;
  }
}

class ParallelFor : public ASTNode {
public:
  ParallelFor(std::unique_ptr<Variable> &&variable,
              std::unique_ptr<VarDeclaration> &&varDeclaration,
              std::unique_ptr<Rules> &&rules) {
    appendChild(std::move(variable));
    appendChild(std::move(varDeclaration));
    appendChild(std::move(rules));
  }
  Variable &getListName() const {
    return *static_cast<Variable *>(children[0].get());
  }
  VarDeclaration &getElementName() const {
    return *static_cast<VarDeclaration *>(children[1].get());
  }
  Rules &getRules() const { return *static_cast<Rules *>(children[2].get()); }

private:
  virtual coro::Task<> acceptHelper(ASTVisitor &visitor) override;
};

class InputText : public ASTNode {
public:
  explicit InputText(std::unique_ptr<FormatNode> &&prompt,
                     std::unique_ptr<Variable> &&to,
                     std::unique_ptr<VarDeclaration> &&result) {
    appendChild(std::move(prompt));
    appendChild(std::move(to));
    appendChild(std::move(result));
  }
  const FormatNode &getPrompt() const {
    return *static_cast<FormatNode *>(children[0].get());
  }
  const Variable &getTo() const {
    return *static_cast<Variable *>(children[1].get());
  }
  const VarDeclaration &getResult() const {
    return *static_cast<VarDeclaration *>(children[2].get());
  }

private:
  virtual coro::Task<> acceptHelper(ASTVisitor &visitor) override;
};