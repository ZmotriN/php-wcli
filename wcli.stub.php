<?php

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