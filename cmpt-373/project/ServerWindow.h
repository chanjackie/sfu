#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <functional>
#include <memory>
#include <string>


// Note: The ncurses state needs to be hidden from the public interface
// due to macro conflicts with boost asio. Thus, we hide the implementation
// requiring state behind indirection for a compilation firewall.
class ServerWindowImpl;


class ServerWindow {
public:
  explicit ServerWindow(std::function<void(std::string)> onTextEntry)
    : ServerWindow{std::move(onTextEntry), 1}
      { }

  ServerWindow(std::function<void(std::string)> onTextEntry, int updateDelay);
  // The default constructor is out of line to defer it until the implementation
  // of ServerWindowImpl is known.
  ~ServerWindow();

  void update();

  void displayText(const std::string& text);

  void clearText();

private:
  std::unique_ptr<ServerWindowImpl> impl;
};


#endif
