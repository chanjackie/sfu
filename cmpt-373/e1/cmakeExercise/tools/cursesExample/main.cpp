#include <ncurses.h>

int
main() {   
  initscr();
  if(has_colors() == FALSE) {
    endwin();
    printf("Your terminal does not support color\n");
    return 1;
  }
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);

  attron(COLOR_PAIR(1));
  attron(A_BOLD);
  printw("Hello World !!!");
  attroff(A_BOLD);
  attroff(COLOR_PAIR(1));

  refresh();
  getch();
  endwin();

  return 0;
}