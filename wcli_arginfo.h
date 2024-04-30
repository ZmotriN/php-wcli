// ********************************************************************
// ************************* HANDLE FUNCTIONS *************************
// ********************************************************************

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_wcli_get_output_handle, 0, 0, MAY_BE_BOOL|MAY_BE_LONG)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_wcli_get_input_handle, 0, 0, MAY_BE_BOOL|MAY_BE_LONG)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_wcli_get_window_handle, 0, 0, MAY_BE_BOOL|MAY_BE_LONG)
ZEND_END_ARG_INFO()


// ********************************************************************
// ************************* CONSOLE FUNCTIONS ************************
// ********************************************************************

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_wcli_get_console_title, 0, 0, MAY_BE_BOOL|MAY_BE_STRING)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wcli_set_console_title, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, title, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_wcli_get_console_size, 0, 0, MAY_BE_BOOL|MAY_BE_ARRAY)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wcli_set_console_size, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, force, _IS_BOOL, 0, "false")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_wcli_get_buffer_size, 0, 0, MAY_BE_BOOL|MAY_BE_ARRAY)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wcli_set_buffer_size, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wcli_get_code_page, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wcli_set_code_page, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, cp, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_wcli_get_font_size, 0, 0, MAY_BE_BOOL|MAY_BE_ARRAY)
ZEND_END_ARG_INFO()


// ********************************************************************
// ************************* COLORS FUNCTIONS *************************
// ********************************************************************

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_wcli_get_foreground_color, 0, 0, MAY_BE_BOOL|MAY_BE_LONG)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wcli_set_foreground_color, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, fore, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_wcli_get_background_color, 0, 0, MAY_BE_BOOL|MAY_BE_LONG)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wcli_set_background_color, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, back, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_wcli_get_colors, 0, 0, MAY_BE_BOOL|MAY_BE_ARRAY)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wcli_set_colors, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, fore, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, back, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wcli_inverse_colors, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wcli_reset_colors, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()


// ********************************************************************
// ************************* CURSOR FUNCTIONS *************************
// ********************************************************************

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wcli_hide_cursor, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wcli_show_cursor, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wcli_get_cursor_visibility, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wcli_set_cursor_visibility, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, visible, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_wcli_get_cursor_size, 0, 0, MAY_BE_BOOL|MAY_BE_LONG)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wcli_set_cursor_size, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, size, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_wcli_get_cursor_position, 0, 0, MAY_BE_BOOL|MAY_BE_ARRAY)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wcli_move_cursor, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wcli_set_cursor_position, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
ZEND_END_ARG_INFO()


// ********************************************************************
// ************************* OUTPUT FUNCTIONS *************************
// ********************************************************************

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wcli_echo, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, str, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, fore, IS_LONG, 1, "null")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, back, IS_LONG, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wcli_print, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, str, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, x, IS_LONG, 1, "null")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, y, IS_LONG, 1, "null")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, fore, IS_LONG, 1, "null")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, back, IS_LONG, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wcli_clear, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wcli_fill, 0, 5, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, c, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, fore, IS_LONG, 1, "null")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, back, IS_LONG, 1, "null")
ZEND_END_ARG_INFO()


// ********************************************************************
// ************************* INPUT FUNCTIONS **************************
// ********************************************************************

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_wcli_get_key, 0, 0, MAY_BE_BOOL|MAY_BE_LONG)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_wcli_get_key_async, 0, 0, MAY_BE_BOOL|MAY_BE_LONG)
ZEND_END_ARG_INFO()


// ********************************************************************
// ************************* WINDOW FUNCTIONS *************************
// ********************************************************************

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wcli_is_on_top, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wcli_is_visible, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_wcli_get_window_area, 0, 0, MAY_BE_BOOL|MAY_BE_ARRAY)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_wcli_get_client_area, 0, 0, MAY_BE_BOOL|MAY_BE_ARRAY)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wcli_minimize, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wcli_maximize, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wcli_restore, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wcli_activate, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wcli_flash, 0, 0, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, invert, _IS_BOOL, 1, "false")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wcli_bring_to_front, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()




// ********************************************************************
// *************************** DECLARATIONS ***************************
// ********************************************************************

ZEND_FUNCTION(wcli_get_output_handle);
ZEND_FUNCTION(wcli_get_input_handle);
ZEND_FUNCTION(wcli_get_window_handle);

ZEND_FUNCTION(wcli_get_console_title);
ZEND_FUNCTION(wcli_set_console_title);
ZEND_FUNCTION(wcli_get_console_size);
ZEND_FUNCTION(wcli_set_console_size);
ZEND_FUNCTION(wcli_get_buffer_size);
ZEND_FUNCTION(wcli_set_buffer_size);
ZEND_FUNCTION(wcli_get_code_page);
ZEND_FUNCTION(wcli_set_code_page);
ZEND_FUNCTION(wcli_get_font_size);

ZEND_FUNCTION(wcli_get_foreground_color);
ZEND_FUNCTION(wcli_set_foreground_color);
ZEND_FUNCTION(wcli_get_background_color);
ZEND_FUNCTION(wcli_set_background_color);
ZEND_FUNCTION(wcli_get_colors);
ZEND_FUNCTION(wcli_set_colors);
ZEND_FUNCTION(wcli_inverse_colors);
ZEND_FUNCTION(wcli_reset_colors);

ZEND_FUNCTION(wcli_hide_cursor);
ZEND_FUNCTION(wcli_show_cursor);
ZEND_FUNCTION(wcli_get_cursor_visibility);
ZEND_FUNCTION(wcli_set_cursor_visibility);
ZEND_FUNCTION(wcli_get_cursor_size);
ZEND_FUNCTION(wcli_set_cursor_size);
ZEND_FUNCTION(wcli_get_cursor_position);
ZEND_FUNCTION(wcli_set_cursor_position);
ZEND_FUNCTION(wcli_move_cursor);

ZEND_FUNCTION(wcli_echo);
ZEND_FUNCTION(wcli_print);
ZEND_FUNCTION(wcli_clear);
ZEND_FUNCTION(wcli_fill);

ZEND_FUNCTION(wcli_get_key);
ZEND_FUNCTION(wcli_get_key_async);

ZEND_FUNCTION(wcli_is_on_top);
ZEND_FUNCTION(wcli_is_visible);
ZEND_FUNCTION(wcli_get_window_area);
ZEND_FUNCTION(wcli_get_client_area);
ZEND_FUNCTION(wcli_minimize);
ZEND_FUNCTION(wcli_maximize);
ZEND_FUNCTION(wcli_restore);
ZEND_FUNCTION(wcli_activate);
ZEND_FUNCTION(wcli_flash);
ZEND_FUNCTION(wcli_bring_to_front);






// ********************************************************************
// *************************** ENTRY POINTS ***************************
// ********************************************************************

static const zend_function_entry ext_functions[] = {
	ZEND_FE(wcli_get_output_handle, arginfo_wcli_get_output_handle)
	ZEND_FE(wcli_get_input_handle, arginfo_wcli_get_input_handle)
	ZEND_FE(wcli_get_window_handle, arginfo_wcli_get_window_handle)

	ZEND_FE(wcli_get_console_title, arginfo_wcli_get_console_title)
	ZEND_FE(wcli_set_console_title, arginfo_wcli_set_console_title)
	ZEND_FE(wcli_get_console_size, arginfo_wcli_get_console_size)
	ZEND_FE(wcli_set_console_size, arginfo_wcli_set_console_size)
	ZEND_FE(wcli_get_buffer_size, arginfo_wcli_get_buffer_size)
	ZEND_FE(wcli_set_buffer_size, arginfo_wcli_set_buffer_size)
	ZEND_FE(wcli_get_code_page, arginfo_wcli_get_code_page)
	ZEND_FE(wcli_set_code_page, arginfo_wcli_set_code_page)
	ZEND_FE(wcli_get_font_size, arginfo_wcli_get_font_size)

	ZEND_FE(wcli_get_foreground_color, arginfo_wcli_get_foreground_color)
	ZEND_FE(wcli_set_foreground_color, arginfo_wcli_set_foreground_color)
	ZEND_FE(wcli_get_background_color, arginfo_wcli_get_background_color)
	ZEND_FE(wcli_set_background_color, arginfo_wcli_set_background_color)
	ZEND_FE(wcli_get_colors, arginfo_wcli_get_colors)
	ZEND_FE(wcli_set_colors, arginfo_wcli_set_colors)
	ZEND_FE(wcli_inverse_colors, arginfo_wcli_inverse_colors)
	ZEND_FE(wcli_reset_colors, arginfo_wcli_reset_colors)

	ZEND_FE(wcli_hide_cursor, arginfo_wcli_hide_cursor)
	ZEND_FE(wcli_show_cursor, arginfo_wcli_show_cursor)
	ZEND_FE(wcli_get_cursor_visibility, arginfo_wcli_get_cursor_visibility)
	ZEND_FE(wcli_set_cursor_visibility, arginfo_wcli_set_cursor_visibility)
	ZEND_FE(wcli_get_cursor_size, arginfo_wcli_get_cursor_size)
	ZEND_FE(wcli_set_cursor_size, arginfo_wcli_set_cursor_size)
	ZEND_FE(wcli_get_cursor_position, arginfo_wcli_get_cursor_position)
	ZEND_FE(wcli_set_cursor_position, arginfo_wcli_set_cursor_position)
	ZEND_FE(wcli_move_cursor, arginfo_wcli_move_cursor)

	ZEND_FE(wcli_echo, arginfo_wcli_echo)
	ZEND_FE(wcli_print, arginfo_wcli_print)
	ZEND_FE(wcli_clear, arginfo_wcli_clear)
	ZEND_FE(wcli_fill, arginfo_wcli_fill)

	ZEND_FE(wcli_get_key, arginfo_wcli_get_key)
	ZEND_FE(wcli_get_key_async, arginfo_wcli_get_key_async)

	ZEND_FE(wcli_is_on_top, arginfo_wcli_is_on_top)
	ZEND_FE(wcli_is_visible, arginfo_wcli_is_visible)
	ZEND_FE(wcli_get_window_area, arginfo_wcli_get_window_area)
	ZEND_FE(wcli_get_client_area, arginfo_wcli_get_client_area)
	ZEND_FE(wcli_minimize, arginfo_wcli_minimize)
	ZEND_FE(wcli_maximize, arginfo_wcli_maximize)
	ZEND_FE(wcli_restore, arginfo_wcli_restore)
	ZEND_FE(wcli_activate, arginfo_wcli_activate)
	ZEND_FE(wcli_flash, arginfo_wcli_flash)
	ZEND_FE(wcli_bring_to_front, arginfo_wcli_bring_to_front)

	
	

	ZEND_FE_END
};
