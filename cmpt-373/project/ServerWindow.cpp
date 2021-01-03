#include "ServerWindow.h"

#include <cassert>

#include <form.h>
#include <ncurses.h>


////////////////////////////////////////////////////////////////////////////////
// Hidden ServerWindow implementation
////////////////////////////////////////////////////////////////////////////////

class ServerWindowImpl {
public:
  ServerWindowImpl(std::function<void(std::string)> onTextEntry, int updateDelay);
  ~ServerWindowImpl();
  ServerWindowImpl(ServerWindowImpl&) = delete;
  ServerWindowImpl(ServerWindowImpl&&) = delete;
  ServerWindowImpl& operator=(ServerWindowImpl&) = delete;
  ServerWindowImpl& operator=(ServerWindowImpl&&) = delete;

  void resizeOnShapeChange();

  void processInput(int key);

  [[nodiscard]] size_t getFieldSize() const;

  [[nodiscard]] std::string getFieldString() const;

  void refreshWindow();

  void displayText(const std::string& text);

private:
  std::function<void(std::string)> onTextEntry;

  int parentX   = 0;
  int parentY   = 0;
  int entrySize = 3;

  WINDOW *view     = nullptr;
  WINDOW *entry    = nullptr;
  WINDOW *entrySub = nullptr;

  FIELD *fields[2]  = { nullptr, nullptr };
  FIELD *entryField = nullptr;

  FORM *entryForm = nullptr;
};


ServerWindowImpl::ServerWindowImpl(std::function<void(std::string)> onTextEntry,
                               int updateDelay)
  : onTextEntry{std::move(onTextEntry)} {
  initscr();
  noecho();
  halfdelay(updateDelay);

  getmaxyx(stdscr, parentY, parentX);

  view = newwin(parentY - entrySize, parentX, 0, 0);
  scrollok(view, TRUE);

  entry = newwin(entrySize, parentX, parentY - entrySize, 0);
  wborder(entry, ' ', ' ', '-', ' ', '+', '+', ' ', ' ');
  entrySub = derwin(entry, entrySize - 1, parentX, 1, 0);
  
  entryField = new_field(entrySize - 1, parentX, 0, 0, 0, 0);
  assert(entryField && "Error creating entry field.");
  set_field_buffer(entryField, 0, "");
  set_field_opts(entryField, O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);

  fields[0] = entryField;
  entryForm = new_form(fields);
  assert(entryForm && "Error creating entry form.");
  set_form_win(entryForm, entry);
  set_form_sub(entryForm, entrySub);
  post_form(entryForm);

  refresh();
  wrefresh(entry);
}


ServerWindowImpl::~ServerWindowImpl() {
  unpost_form(entryForm);
  free_form(entryForm);
  free_field(entryField);
  delwin(entry);
  delwin(view);
  endwin();
}


void
ServerWindowImpl::resizeOnShapeChange() {
  int newX, newY;
  getmaxyx(stdscr, newY, newX);

  if (newY != parentY || newX != parentX) {
    parentX = newX;
    parentY = newY;

    wresize(view, parentY - entrySize, parentX);
    wresize(entry, entrySize, parentX);
    mvwin(entry, parentY - entrySize, 0);

    wclear(stdscr);
    wborder(entry, ' ', ' ', '-', ' ', '+', '+', ' ', ' ');
  }
}


void
ServerWindowImpl::processInput(int key) {
  switch(key) {
    case KEY_ENTER:
    case '\n':
      // Requesting validation synchs the seen field & the buffer.
      form_driver(entryForm, REQ_VALIDATION);
      onTextEntry(getFieldString());
      move(1, 1);
      set_field_buffer(entryField, 0, "");
      refresh();
      pos_form_cursor(entryForm);
      break;
    case KEY_BACKSPACE:
    case 127: //ASCII delete
      form_driver(entryForm, REQ_DEL_PREV);
      break;
    case KEY_DC:
      form_driver(entryForm, REQ_DEL_CHAR);
      break;
    case ERR:
      // swallow
      break;
    default:
      form_driver(entryForm, key);
      break;
  }
}


void
ServerWindowImpl::refreshWindow() {
  wrefresh(view);
  wrefresh(entry);
}


void
ServerWindowImpl::displayText(const std::string& text) {
  // This variadic function is part of the curses interface.
  // NOLINTNEXTLINE (cppcoreguidelines-pro-type-vararg)
  wprintw(view, "%s", text.c_str());
}


size_t
ServerWindowImpl::getFieldSize() const {
  size_t x, y;
  getyx(entrySub, y, x);
  return y * parentX + x;
}


std::string
ServerWindowImpl::getFieldString() const {
  return std::string{field_buffer(entryField, 0), getFieldSize()};
}


////////////////////////////////////////////////////////////////////////////////
// ServerWindow API
////////////////////////////////////////////////////////////////////////////////


ServerWindow::ServerWindow(std::function<void(std::string)> onTextEntry,
                       int updateDelay)
  : impl{std::make_unique<ServerWindowImpl>(std::move(onTextEntry), updateDelay)}
    { }


ServerWindow::~ServerWindow() = default;


void
ServerWindow::update() {
  impl->resizeOnShapeChange();
  impl->processInput(getch());
  impl->refreshWindow();
}


void
ServerWindow::displayText(const std::string& text) {
  impl->displayText(text);
}


// PLACEHOLDER IMPLEMENTATION
void
ServerWindow::clearText() {
  impl->displayText(std::string(100, '\n'));
}