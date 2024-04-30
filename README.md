# php-wcli
WCLI - Windows CLI support for PHP

## Constants
Color constants can be use in combination with the Bright flag.\
Ex: wcli_echo("Hello World!", Black, Red|Bright);
```php
<?php

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