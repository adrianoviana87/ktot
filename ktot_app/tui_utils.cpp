#include "ktot/crosscutting/tui_utils.h"
#include <cstdio>

namespace ktot {
namespace tui {
void set_cursor_position(int column, int row) {
  printf("\033[%d;%dH", column + 1, row + 1);
}

void clear() { printf("\033[2J"); }

void set_cursor_up(int line_count) { printf("\033[%dA", line_count); }

void erase_til_end() { printf("\033[K"); }

void clear_last_line() {
  set_cursor_up(1);
  erase_til_end();
}

}  // namespace tui
}  // namespace ktot
