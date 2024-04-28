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




ZEND_FUNCTION(wcli_get_output_handle);
ZEND_FUNCTION(wcli_get_input_handle);
ZEND_FUNCTION(wcli_get_window_handle);

ZEND_FUNCTION(wcli_get_console_size);
ZEND_FUNCTION(wcli_set_console_size);
ZEND_FUNCTION(wcli_get_buffer_size);
ZEND_FUNCTION(wcli_set_buffer_size);
ZEND_FUNCTION(wcli_get_code_page);
ZEND_FUNCTION(wcli_set_code_page);

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









static const zend_function_entry ext_functions[] = {
	ZEND_FE(wcli_get_output_handle, arginfo_wcli_get_output_handle)
	ZEND_FE(wcli_get_input_handle, arginfo_wcli_get_input_handle)
	ZEND_FE(wcli_get_window_handle, arginfo_wcli_get_window_handle)

	ZEND_FE(wcli_get_console_size, arginfo_wcli_get_console_size)
	ZEND_FE(wcli_set_console_size, arginfo_wcli_set_console_size)
	ZEND_FE(wcli_get_buffer_size, arginfo_wcli_get_buffer_size)
	ZEND_FE(wcli_set_buffer_size, arginfo_wcli_set_buffer_size)
	ZEND_FE(wcli_get_code_page, arginfo_wcli_get_code_page)
	ZEND_FE(wcli_set_code_page, arginfo_wcli_set_code_page)

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





	ZEND_FE_END
};
