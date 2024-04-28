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
 * @return array|bool
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