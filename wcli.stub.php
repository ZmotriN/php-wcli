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
 * Retrieve the size and the scrolling of the console.
 * Return an array [w, h, x, y]
 *
 * @return array|bool
 */
function wcli_get_console_size(): array|bool {}