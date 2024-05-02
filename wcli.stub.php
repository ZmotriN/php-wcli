<?php

/**
 * COLOR CODES
 */
const Red    = 4;  // Red color
const Green  = 2;  // Green color
const Blue   = 1;  // Blue color
const Yellow = 14; // Yellow color
const Purple = 5;  // Purple color
const Aqua   = 3;  // Aqua color
const White  = 7;  // White color
const Black  = 0;  // Black color
const Grey   = 8;  // Grey color
const Bright = 8;  // Bright Flag

/**
 * VIRTUAL KEY CODES
 * see: https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
 */
const VK_LBUTTON             = 0x01; // Left mouse button
const VK_RBUTTON             = 0x02; // Right mouse button
const VK_CANCEL              = 0x03; // Control-break processing
const VK_MBUTTON             = 0x04; // Middle mouse button (three-button mouse)
const VK_XBUTTON1            = 0x05; // X1 mouse button
const VK_XBUTTON2            = 0x06; // X2 mouse button                   
const VK_BACK                = 0x08; // BACKSPACE key
const VK_TAB                 = 0x09; // TAB key
const VK_CLEAR               = 0x0C; // CLEAR key
const VK_RETURN              = 0x0D; // ENTER key
const VK_SHIFT               = 0x10; // SHIFT key
const VK_CONTROL             = 0x11; // CTRL key
const VK_MENU                = 0x12; // ALT key
const VK_PAUSE               = 0x13; // PAUSE key
const VK_CAPITAL             = 0x14; // CAPS LOCK key
const VK_KANA                = 0x15; // IME Kana mode
const VK_HANGUEL             = 0x15; // IME Hanguel mode (maintained for compatibility; use VK_HANGUL)
const VK_HANGUL              = 0x15; // IME Hangul mode
const VK_JUNJA               = 0x17; // IME Junja mode
const VK_FINAL               = 0x18; // IME final mode
const VK_HANJA               = 0x19; // IME Hanja mode
const VK_KANJI               = 0x19; // IME Kanji mode
const VK_ESCAPE              = 0x1B; // ESC key
const VK_CONVERT             = 0x1C; // IME convert
const VK_NONCONVERT          = 0x1D; // IME nonconvert
const VK_ACCEPT              = 0x1E; // IME accept
const VK_MODECHANGE          = 0x1F; // IME mode change request
const VK_SPACE               = 0x20; // SPACEBAR
const VK_PRIOR               = 0x21; // PAGE UP key
const VK_NEXT                = 0x22; // PAGE DOWN key
const VK_END                 = 0x23; // END key
const VK_HOME                = 0x24; // HOME key
const VK_LEFT                = 0x25; // LEFT ARROW key
const VK_UP                  = 0x26; // UP ARROW key
const VK_RIGHT               = 0x27; // RIGHT ARROW key
const VK_DOWN                = 0x28; // DOWN ARROW key
const VK_SELECT              = 0x29; // SELECT key
const VK_PRINT               = 0x2A; // PRINT key
const VK_EXECUTE             = 0x2B; // EXECUTE key
const VK_SNAPSHOT            = 0x2C; // PRINT SCREEN key
const VK_INSERT              = 0x2D; // INS key
const VK_DELETE              = 0x2E; // DEL key
const VK_HELP                = 0x2F; // HELP key
const VK_LWIN                = 0x5B; // Left Windows key (Natural keyboard)
const VK_RWIN                = 0x5C; // Right Windows key (Natural keyboard)
const VK_APPS                = 0x5D; // Applications key (Natural keyboard)
const VK_SLEEP               = 0x5F; // Computer Sleep key
const VK_NUMPAD0             = 0x60; // Numeric keypad 0 key
const VK_NUMPAD1             = 0x61; // Numeric keypad 1 key
const VK_NUMPAD2             = 0x62; // Numeric keypad 2 key
const VK_NUMPAD3             = 0x63; // Numeric keypad 3 key
const VK_NUMPAD4             = 0x64; // Numeric keypad 4 key
const VK_NUMPAD5             = 0x65; // Numeric keypad 5 key
const VK_NUMPAD6             = 0x66; // Numeric keypad 6 key
const VK_NUMPAD7             = 0x67; // Numeric keypad 7 key
const VK_NUMPAD8             = 0x68; // Numeric keypad 8 key
const VK_NUMPAD9             = 0x69; // Numeric keypad 9 key
const VK_MULTIPLY            = 0x6A; // Multiply key
const VK_ADD                 = 0x6B; // Add key
const VK_SEPARATOR           = 0x6C; // Separator key
const VK_SUBTRACT            = 0x6D; // Subtract key
const VK_DECIMAL             = 0x6E; // Decimal key
const VK_DIVIDE              = 0x6F; // Divide key
const VK_F1                  = 0x70; // F1 key
const VK_F2                  = 0x71; // F2 key
const VK_F3                  = 0x72; // F3 key
const VK_F4                  = 0x73; // F4 key
const VK_F5                  = 0x74; // F5 key
const VK_F6                  = 0x75; // F6 key
const VK_F7                  = 0x76; // F7 key
const VK_F8                  = 0x77; // F8 key
const VK_F9                  = 0x78; // F9 key
const VK_F10                 = 0x79; // F10 key
const VK_F11                 = 0x7A; // F11 key
const VK_F12                 = 0x7B; // F12 key
const VK_F13                 = 0x7C; // F13 key
const VK_F14                 = 0x7D; // F14 key
const VK_F15                 = 0x7E; // F15 key
const VK_F16                 = 0x7F; // F16 key
const VK_F17                 = 0x80; // F17 key
const VK_F18                 = 0x81; // F18 key
const VK_F19                 = 0x82; // F19 key
const VK_F20                 = 0x83; // F20 key
const VK_F21                 = 0x84; // F21 key
const VK_F22                 = 0x85; // F22 key
const VK_F23                 = 0x86; // F23 key
const VK_F24                 = 0x87; // F24 key
const VK_NUMLOCK             = 0x90; // NUM LOCK key
const VK_SCROLL              = 0x91; // SCROLL LOCK key
const VK_LSHIFT              = 0xA0; // Left SHIFT key
const VK_RSHIFT              = 0xA1; // Right SHIFT key
const VK_LCONTROL            = 0xA2; // Left CONTROL key
const VK_RCONTROL            = 0xA3; // Right CONTROL key
const VK_LMENU               = 0xA4; // Left MENU key
const VK_RMENU               = 0xA5; // Right MENU key
const VK_BROWSER_BACK        = 0xA6; // Browser Back key
const VK_BROWSER_FORWARD     = 0xA7; // Browser Forward key
const VK_BROWSER_REFRESH     = 0xA8; // Browser Refresh key
const VK_BROWSER_STOP        = 0xA9; // Browser Stop key
const VK_BROWSER_SEARCH      = 0xAA; // Browser Search key
const VK_BROWSER_FAVORITES   = 0xAB; // Browser Favorites key
const VK_BROWSER_HOME        = 0xAC; // Browser Start and Home key
const VK_VOLUME_MUTE         = 0xAD; // Volume Mute key
const VK_VOLUME_DOWN         = 0xAE; // Volume Down key
const VK_VOLUME_UP           = 0xAF; // Volume Up key
const VK_MEDIA_NEXT_TRACK    = 0xB0; // Next Track key
const VK_MEDIA_PREV_TRACK    = 0xB1; // Previous Track key
const VK_MEDIA_STOP          = 0xB2; // Stop Media key
const VK_MEDIA_PLAY_PAUSE    = 0xB3; // Play/Pause Media key
const VK_LAUNCH_MAIL         = 0xB4; // Start Mail key
const VK_LAUNCH_MEDIA_SELECT = 0xB5; // Select Media key
const VK_LAUNCH_APP1         = 0xB6; // Start Application 1 key
const VK_LAUNCH_APP2         = 0xB7; // Start Application 2 key
const VK_OEM_1               = 0xBA; // Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the ';:' key
const VK_OEM_PLUS            = 0xBB; // For any country/region, the '+' key
const VK_OEM_COMMA           = 0xBC; // For any country/region, the ',' key
const VK_OEM_MINUS           = 0xBD; // For any country/region, the '-' key
const VK_OEM_PERIOD          = 0xBE; // For any country/region, the '.' key
const VK_OEM_2               = 0xBF; // Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '/?' key
const VK_OEM_3               = 0xC0; // Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '`~' key
const VK_OEM_4               = 0xDB; // Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '[{' key
const VK_OEM_5               = 0xDC; // Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '\|' key
const VK_OEM_6               = 0xDD; // Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the ']}' key
const VK_OEM_7               = 0xDE; // Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the 'single-quote/double-quote' key
const VK_OEM_8               = 0xDF; // Used for miscellaneous characters; it can vary by keyboard.
const VK_OEM_102             = 0xE2; // Either the angle bracket key or the backslash key on the RT 102-key keyboard
const VK_PROCESSKEY          = 0xE5; // IME PROCESS key
const VK_PACKET              = 0xE7; // Used to pass Unicode characters as if they were keystrokes. The VK_PACKET key is the low word of a 32-bit Virtual Key value used for non-keyboard input methods. For more information, see Remark in KEYBDINPUT, SendInput, WM_KEYDOWN, and WM_KEYUP
const VK_ATTN                = 0xF6; // Attn key
const VK_CRSEL               = 0xF7; // CrSel key
const VK_EXSEL               = 0xF8; // ExSel key
const VK_EREOF               = 0xF9; // Erase EOF key
const VK_PLAY                = 0xFA; // Play key
const VK_ZOOM                = 0xFB; // Zoom key
const VK_NONAME              = 0xFC; // Reserved
const VK_PA1                 = 0xFD; // PA1 key
const VK_OEM_CLEAR           = 0xFE; // Clear key
const VK_0                   = 0x30; // 0 key
const VK_1                   = 0x31; // 1 key
const VK_2                   = 0x32; // 2 key
const VK_3                   = 0x33; // 3 key
const VK_4                   = 0x34; // 4 key
const VK_5                   = 0x35; // 5 key
const VK_6                   = 0x36; // 6 key
const VK_7                   = 0x37; // 7 key
const VK_8                   = 0x38; // 8 key
const VK_9                   = 0x39; // 9 key
const VK_A                   = 0x41; // A key
const VK_B                   = 0x42; // B key
const VK_C                   = 0x43; // C key
const VK_D                   = 0x44; // D key
const VK_E                   = 0x45; // E key
const VK_F                   = 0x46; // F key
const VK_G                   = 0x47; // G key
const VK_H                   = 0x48; // H key
const VK_I                   = 0x49; // I key
const VK_J                   = 0x4A; // J key
const VK_K                   = 0x4B; // K key
const VK_L                   = 0x4C; // L key
const VK_M                   = 0x4D; // M key
const VK_N                   = 0x4E; // N key
const VK_O                   = 0x4F; // O key
const VK_P                   = 0x50; // P key
const VK_Q                   = 0x51; // Q key
const VK_R                   = 0x52; // R key
const VK_S                   = 0x53; // S key
const VK_T                   = 0x54; // T key
const VK_U                   = 0x55; // U key
const VK_V                   = 0x56; // V key
const VK_W                   = 0x57; // W key
const VK_X                   = 0x58; // X key
const VK_Y                   = 0x59; // Y key
const VK_Z                   = 0x5A; // Z key



/**
 * Get the console output handle.
 *
 * @return int|bool Output handle
 */
function wcli_get_output_handle(): int|bool {}


/**
 * Get the console input handle.
 *
 * @return int|bool Input handle
 */
function wcli_get_input_handle(): int|bool {}


/**
 * Get the console window handle.
 *
 * @return int|bool Window handle
 */
function wcli_get_window_handle(): int|bool {}


/**
 * Return the console title.
 *
 * @return string|bool The console title, otherwise false.
 */
function wcli_get_console_title(): string|bool {}


/**
 * Set the console title.
 *
 * @param string $title The console title
 *
 * @return bool True if success, else false.
 */
function wcli_set_console_title(string $title): bool {}


/**
 * Retrieve the size and the scrolling in characters of the console.
 * Return an array [w, h, x, y]
 *
 * @return array|bool Return the console size or FALSE.
 */
function wcli_get_console_size(): array|bool {}


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


/**
 * Retrieve console buffer size in characters.
 * Return an array [w, h]
 *
 * @return array|bool Return the buffer size or FALSE.
 */
function wcli_get_buffer_size(): array|bool {}


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


/**
 * Retrieves the input code page used by the console.
 * See: https://learn.microsoft.com/en-us/windows/win32/intl/code-page-identifiers
 *
 * @return int Code Page ID
 */
function wcli_get_code_page(): int {}


/**
 * Set the input code page used by the console.
 * See: https://learn.microsoft.com/en-us/windows/win32/intl/code-page-identifiers
 *
 * @param int $cpID Code Page ID
 *
 * @return bool True if success, else false.
 */
function wcli_set_code_page(int $cpID): bool {}


/**
 * Retrieve console font size in pixels.
 * Return an array [width, height]
 *
 * @return array|bool The font size, otherwise false.
 */
function wcli_get_font_size(): array|bool {}


/**
 * Get the foreground color.
 *
 * @return int Color Constant
 */
function wcli_get_foreground_color(): int {}


/**
 * Set the foreground color.
 *
 * @param int $color Color Constant
 *
 * @return bool True if success, else false.
 */
function wcli_set_foreground_color(int $color): bool {}


/**
 * Get the background color.
 *
 * @return int Color Constant
 */
function wcli_get_background_color(): int {}


/**
 * Set the background color.
 *
 * @param int $color Color constant
 *
 * @return bool True if success, else false.
 */
function wcli_set_background_color(int $color): bool {}


/**
 * Retrieve console foreground and background colors.
 * Return an array [foreColor, backColor]
 *
 * @return array|bool The array of colors or False
 */
function wcli_get_colors(): array|bool {}


/**
 * Set the foreground and background color at once.
 *
 * @param int $fore Foreground color constant
 * @param int $back Background color constant
 *
 * @return bool True if success, else false.
 */
function wcli_set_colors(int $fore, int $back): bool {}


/**
 * Swap foreground and background colors.
 *
 * @return bool True if success, else false.
 */
function wcli_inverse_colors(): bool {}


/**
 * Reset console colors to default.
 *
 * @return bool True if success, else false.
 */
function wcli_reset_colors(): bool {}


/**
 * Hide console cursor.
 *
 * @return bool True if success, else false.
 */
function wcli_hide_cursor(): bool {}


/**
 * Show console cursor.
 *
 * @return bool True if success, else false.
 */
function wcli_show_cursor(): bool {}


/**
 * Retrieve cursor visibility.
 *
 * @return bool True if visible, else false.
 */
function wcli_get_cursor_visibility(): bool {}


/**
 * Set cursor visibility.
 *
 * @param bool $visible True to show, false to hide.
 *
 * @return bool True if success, else false.
 */
function wcli_set_cursor_visibility(bool $visible): bool {}


/**
 * Retrieve cursor size.
 * The size value is between 0 and 100.
 *
 * @return int|bool The cursor size if success, else false.
 */
function wcli_get_cursor_size(): int|bool {}


/**
 * Set cursor size.
 *
 * @param int $size Cursor size between 0 and 100.
 *
 * @return bool True if success, else false.
 */
function wcli_set_cursor_size(int $size): bool {}


/**
 * Retrieve cursor position.
 * Return an array [x, y]
 *
 * @return array|bool The cursor position or false.
 */
function wcli_get_cursor_position(): array|bool {}


/**
 * Set cursor position.
 *
 * @param int $x X position in characters
 * @param int $y Y position in characters
 *
 * @return bool True if success, else false.
 */
function wcli_set_cursor_position(int $x, int $y): bool {}


/**
 * Move cursor position relatively to the current cursor position.
 *
 * @param int $x X move in characters
 * @param int $y Y move in characters
 *
 * @return bool True if success, else false.
 */
function wcli_move_cursor(int $x, int $y): bool {}


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


/**
 * Clear the console.
 *
 * @return bool True if success, else false.
 */
function wcli_clear(): bool {}


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


/**
 * Pause process and wait for a keyboard input.
 *
 * @return int|bool The input character otherwise false.
 */
function wcli_get_key(): int|bool {}


/**
 * Get an async keyboard input.
 *
 * @return int|bool The input character otherwise false.
 */
function wcli_get_key_async(): int|bool {}


/**
 * Flush console input buffer.
 *
 * @return bool True if success, else false.
 */
function wcli_flush_input_buffer(): bool {}


/**
 * Verify if console window is on top.
 *
 * @return bool True if window is on top, otherwise false.
 */
function wcli_is_on_top(): bool {}


/**
 * Verify if console window is visible.
 *
 * @return bool True if window is visible, otherwise false.
 */
function wcli_is_visible(): bool {}


/**
 * Retrieve console window area.
 * Return an array [x, y, width, height]
 *
 * @return array|bool The console window area array, otherwise false.
 */
function wcli_get_window_area(): array|bool {}


/**
 * Retrieve console window inner area.
 * Return an array [x, y, width, height]
 *
 * @return array|bool The console window inner area array, otherwise false.
 */
function wcli_get_client_area(): array|bool {}


/**
 * Minimize console window.
 *
 * @return bool True if success, else false.
 */
function wcli_minimize(): bool {}


/**
 * Maximize console window.
 *
 * @return bool True if success, else false.
 */
function wcli_maximize(): bool {}


/**
 * Restore console window.
 *
 * @return bool True if success, else false.
 */
function wcli_restore(): bool {}


/**
 * Force console window to activate.
 *
 * @return bool True if success, else false.
 */
function wcli_activate(): bool {}


/**
 * Flash console window.
 *
 * @param bool $invert If TRUE, the window is flashed from one state to the other.
 *
 * @return bool True if success, else false.
 */
function wcli_flash(bool $invert = false): bool {}


/**
 * Bring console window to front.
 *
 * @return bool True if success, else false.
 */
function wcli_bring_to_front(): bool {}


/**
 * Set console window position.
 *
 * @param int $x X position in pixels
 * @param int $y Y position in pixels
 *
 * @return bool True if success, else false.
 */
function wcli_set_position(int $x, int $y): bool {}


/**
 * Return module/executable full path.
 * Usefull for SAPI.
 *
 * @return string Module full path
 */
function wcli_get_module_path(): string {}


/**
 * Get parent process ID.
 *
 * @return int|bool Parent process ID, otherwise false.
 */
function wcli_get_parent_pid(): int|bool {}


/**
 * Know if the process was lunch by a terminal.
 *
 * @return bool True if yes, otherwise false.
 */
function wcli_is_cmd_call(): bool {}