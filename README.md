# php-wcli
WCLI - Windows CLI support for PHP

## Constants
Color constants can be use in combination with the Bright flag.\
Ex: wcli_echo("Hello World!", Black, Red|Bright);
```php
const Red = 4; // Red color
const Green = 2; // Green color
const Blue = 1;  // Blue color
const Yellow = 14; // Yellow color
const Purple = 5; // Purple color
const Aqua = 3;  // Aqua color
const White = 7; // White color
const Black = 0; // Black color
const Grey = 8; // Grey color
const Bright = 8; // Bright Flag
```


## Handle functions

### wcli_get_output_handle
```php
/**
 * Get the console output handle.
 *
 * @return int|bool Output handle
 */
function wcli_get_output_handle(): int|bool {}

```

### wcli_get_input_handle
```php
/**
 * Get the console input handle.
 *
 * @return int|bool Input handle
 */
function wcli_get_input_handle(): int|bool {}

```

### wcli_get_window_handle
```php
/**
 * Get the console window handle.
 *
 * @return int|bool Window handle
 */
function wcli_get_window_handle(): int|bool {}

```


## Console functions

### wcli_get_console_title
```php
/**
 * Return the console title.
 *
 * @return string|bool The console title, otherwise false.
 */
function wcli_get_console_title(): string|bool {}

```

### wcli_set_console_title
```php
/**
 * Set the console title.
 *
 * @param string $title The console title
 *
 * @return bool True if success, else false.
 */
function wcli_set_console_title(string $title): bool {}

```

### wcli_get_console_size
```php
/**
 * Retrieve the size and the scrolling in characters of the console.
 * Return an array [w, h, x, y]
 *
 * @return array|bool Return the console size or FALSE.
 */
function wcli_get_console_size(): array|bool {}
```

### wcli_set_console_size
```php
/**
 * Set the console size in characters.
 * Set the $force parameter to true to force the buffer at the same size.
 *
 * @param int $w Width of the console in characters
 * @param int $h Height of the console in characters
 * @param bool $force Default false.
 *
 * @return bool True if success, else false.
 */
function wcli_set_console_size(int $w, int $h, bool $force = false): bool {}
```

### wcli_get_buffer_size
```php
/**
 * Retrieve console buffer size in characters.
 * Return an array [w, h]
 *
 * @return array|bool Return the buffer size or FALSE.
 */
function wcli_get_buffer_size(): array|bool {}
```

### wcli_set_buffer_size
```php
/**
 * Set the console buffer size in characters.
 * The buffer size need to be bigger than the console size.
 * Otherwise, set the console size before the buffer size.
 *
 * @param int $w Width of the buffer in characters
 * @param int $h Height of the buffer in characters
 *
 * @return bool True if success, else false.
 */
function wcli_set_buffer_size(int $w, int $h): bool {}
```

### wcli_get_code_page
```php
/**
 * Retrieves the input code page used by the console.
 * See: https://learn.microsoft.com/en-us/windows/win32/intl/code-page-identifiers
 *
 * @return int Code Page ID
 */
function wcli_get_code_page(): int {}
```

### wcli_set_code_page
```php
/**
 * Set the input code page used by the console.
 * See: https://learn.microsoft.com/en-us/windows/win32/intl/code-page-identifiers
 *
 * @param int $cpID Code Page ID
 *
 * @return bool True if success, else false.
 */
function wcli_set_code_page(int $cpID): bool {}
```

### wcli_get_font_size
```php
/**
 * Retrieve console font size in pixels.
 * Return an array [width, height]
 *
 * @return array|bool The font size, otherwise false.
 */
function wcli_get_font_size(): array|bool {}
```


## Color functions

### wcli_get_foreground_color
```php
/**
 * Get the foreground color.
 *
 * @return int Color Constant
 */
function wcli_get_foreground_color(): int {}
```

### wcli_set_foreground_color
```php
/**
 * Set the foreground color.
 *
 * @param int $color Color Constant
 *
 * @return bool True if success, else false.
 */
function wcli_set_foreground_color(int $color): bool {}
```

### wcli_get_background_color
```php
/**
 * Get the background color.
 *
 * @return int Color Constant
 */
function wcli_get_background_color(): int {}
```

### wcli_set_background_color
```php
/**
 * Set the background color.
 *
 * @param int $color Color constant
 *
 * @return bool True if success, else false.
 */
function wcli_set_background_color(int $color): bool {}
```

### wcli_get_colors
```php
/**
 * Retrieve console foreground and background colors.
 * Return an array [foreColor, backColor]
 *
 * @return array|bool The array of colors or False
 */
function wcli_get_colors(): array|bool {}
```

### wcli_set_colors
```php
/**
 * Set the foreground and background color at once.
 *
 * @param int $fore Foreground color constant
 * @param int $back Background color constant
 *
 * @return bool True if success, else false.
 */
function wcli_set_colors(int $fore, int $back): bool {}
```

### wcli_inverse_colors
```php
/**
 * Swap foreground and background colors.
 *
 * @return bool True if success, else false.
 */
function wcli_inverse_colors(): bool {}
```

### wcli_reset_colors
```php
/**
 * Reset console colors to default.
 *
 * @return bool True if success, else false.
 */
function wcli_reset_colors(): bool {}
```


## Cursor functions

### wcli_hide_cursor
```php
/**
 * Hide console cursor.
 *
 * @return bool True if success, else false.
 */
function wcli_hide_cursor(): bool {}
```

### wcli_show_cursor
```php
/**
 * Show console cursor.
 *
 * @return bool True if success, else false.
 */
function wcli_show_cursor(): bool {}
```

### wcli_get_cursor_visibility
```php
/**
 * Retrieve cursor visibility.
 *
 * @return bool True if visible, else false.
 */
function wcli_get_cursor_visibility(): bool {}
```

### wcli_set_cursor_visibility
```php
/**
 * Set cursor visibility.
 *
 * @param bool $visible True to show, false to hide.
 *
 * @return bool True if success, else false.
 */
function wcli_set_cursor_visibility(bool $visible): bool {}
```

### wcli_get_cursor_size
```php
/**
 * Retrieve cursor size.
 * The size value is between 0 and 100.
 *
 * @return int|bool The cursor size if success, else false.
 */
function wcli_get_cursor_size(): int|bool {}
```

### wcli_set_cursor_size
```php
/**
 * Set cursor size.
 *
 * @param int $size Cursor size between 0 and 100.
 *
 * @return bool True if success, else false.
 */
function wcli_set_cursor_size(int $size): bool {}
```

### wcli_get_cursor_position
```php
/**
 * Retrieve cursor position.
 * Return an array [x, y]
 *
 * @return array|bool The cursor position or false.
 */
function wcli_get_cursor_position(): array|bool {}
```

### wcli_set_cursor_position
```php
/**
 * Set cursor position.
 *
 * @param int $x X position in characters
 * @param int $y Y position in characters
 *
 * @return bool True if success, else false.
 */
function wcli_set_cursor_position(int $x, int $y): bool {}
```

### wcli_move_cursor
```php
/**
 * Move cursor position relatively to the current cursor position.
 *
 * @param int $x X move in characters
 * @param int $y Y move in characters
 *
 * @return bool True if success, else false.
 */
function wcli_move_cursor(int $x, int $y): bool {}
```


## Output functions

### wcli_echo
```php
/**
 * Echo string with colors. Foreground and background colors are optionals.
 *
 * @param string $str String to be echo.
 * @param int $fore Foreground color constant
 * @param int $back Background color constant
 *
 * @return bool True if success, else false.
 */
function wcli_echo(string $str, int $fore = null, int $back = null): bool {}
```

### wcli_print
```php
/**
 * Print string with colors at the x-y position without changing cursor position.
 *
 * @param string $str String to be print
 * @param int $x X position in characters
 * @param int $y Y position in characters
 * @param int $fore Foreground color constant
 * @param int $back Background color constant
 *
 * @return bool True if success, else false.
 */
function wcli_print(string $str, int $x = null, int $y = null, int $fore = null, int $back = null): bool {}
```

### wcli_fill
```php
/**
 * Method fill rect with character and colors.
 *
 * @param int $c Character to fill
 * @param int $x X position of the rect
 * @param int $y Y position of the rect
 * @param int $w Width of the rect
 * @param int $h Height of the rect
 * @param int $fore Foreground color constant
 * @param int $back Background color constant
 *
 * @return bool True if success, else false.
 */
function wcli_fill(int $c, int $x, int $y, int $w, int $h, int $fore = null, int $back = null): bool {}
```

### wcli_clear
```php
/**
 * Clear the console.
 *
 * @return bool True if success, else false.
 */
function wcli_clear(): bool {}
```


## Input functions

### wcli_get_key
```php
/**
 * Pause process and wait for a keyboard input.
 *
 * @return int|bool The input character otherwise false.
 */
function wcli_get_key(): int|bool {}
```

### wcli_get_key_async
```php
/**
 * Get an async keyboard input.
 *
 * @return int|bool The input character otherwise false.
 */
function wcli_get_key_async(): int|bool {}
```

### wcli_flush_input_buffer
```php
/**
 * Flush console input buffer.
 *
 * @return bool True if success, else false.
 */
function wcli_flush_input_buffer(): bool {}
```

## Window functions

### wcli_is_on_top
```php
/**
 * Verify if console window is on top.
 *
 * @return bool True if window is on top, otherwise false.
 */
function wcli_is_on_top(): bool {}
```

### wcli_is_visible
```php
/**
 * Verify if console window is visible.
 *
 * @return bool True if window is visible, otherwise false.
 */
function wcli_is_visible(): bool {}
```

### wcli_get_window_area
```php
/**
 * Retrieve console window area.
 * Return an array [x, y, width, height]
 *
 * @return array|bool The console window area array, otherwise false.
 */
function wcli_get_window_area(): array|bool {}
```


### wcli_get_client_area
```php
/**
 * Retrieve console window inner area.
 * Return an array [x, y, width, height]
 *
 * @return array|bool The console window inner area array, otherwise false.
 */
function wcli_get_client_area(): array|bool {}
```

### wcli_minimize
```php
/**
 * Minimize console window.
 *
 * @return bool True if success, else false.
 */
function wcli_minimize(): bool {}
```

### wcli_maximize
```php
/**
 * Maximize console window.
 *
 * @return bool True if success, else false.
 */
function wcli_maximize(): bool {}
```

### wcli_restore
```php
/**
 * Restore console window.
 *
 * @return bool True if success, else false.
 */
function wcli_restore(): bool {}
```

### wcli_activate
```php
/**
 * Force console window to activate.
 *
 * @return bool True if success, else false.
 */
function wcli_activate(): bool {}
```

### wcli_flash
```php
/**
 * Flash console window.
 *
 * @param bool $invert If TRUE, the window is flashed from one state to the other.
 *
 * @return bool True if success, else false.
 */
function wcli_flash(bool $invert = false): bool {}
```

### wcli_bring_to_front
```php
/**
 * Bring console window to front.
 *
 * @return bool True if success, else false.
 */
function wcli_bring_to_front(): bool {}
```

### wcli_set_position
```php
/**
 * Set console window position.
 *
 * @param int $x X position in pixels
 * @param int $y Y position in pixels
 *
 * @return bool True if success, else false.
 */
function wcli_set_position(int $x, int $y): bool {}
```


## Misc functions

### wcli_get_module_path
```php
/**
 * Return module/executable full path.
 * Usefull for SAPI.
 *
 * @return string Module full path
 */
function wcli_get_module_path(): string {}
```

### wcli_get_parent_pid
```php
/**
 * Get parent process ID.
 *
 * @return int|bool Parent process ID, otherwise false.
 */
function wcli_get_parent_pid(): int|bool {}
```

### wcli_is_cmd_call
```php
/**
 * Know if the process was lunch by a terminal.
 *
 * @return bool True if yes, otherwise false.
 */
function wcli_is_cmd_call(): bool {}
```