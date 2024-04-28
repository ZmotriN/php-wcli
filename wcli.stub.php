<?php

/**
 * Red color
 */
const Red = 4;

/**
 * Green color
 */
const Green = 2;

/**
 * Blue color
 */
const Blue = 1; 

/**
 * Yellow color
 */
const Yellow = 14;

/**
 * Purple color
 */
const Purple = 5;

/**
 * Aqua color
 */
const Aqua = 3; 

/**
 * White color
 */
const White = 7;

/**
 * Black color
 */
const Black = 0;

/**
 * Grey color
 */
const Grey = 8;

/**
 * Bright Flag
 */
const Bright = 8;


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
 * Set cursor visibility
 *
 * @param bool $visible True to show, false to hide.
 *
 * @return bool True if success, else false.
 */
function wcli_set_cursor_visibility(bool $visible): bool {}


/**
 * Method wcli_get_cursor_size
 *
 * @return int|bool The cursor size if success, else false.
 */
function wcli_get_cursor_size(): int|bool {}