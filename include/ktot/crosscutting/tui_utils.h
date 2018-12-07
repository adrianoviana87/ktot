#pragma once
namespace ktot {
namespace tui {
void set_cursor_position(int column, int row);
void clear();
void set_cursor_up(int line_count);
void erase_til_end();
void clear_last_line();
}  // namespace tui
}  // namespace ktot
