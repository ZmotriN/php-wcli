
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_wcli_get_output_handle, 0, 0, MAY_BE_BOOL|MAY_BE_LONG)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_wcli_get_input_handle, 0, 0, MAY_BE_BOOL|MAY_BE_LONG)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_wcli_get_window_handle, 0, 0, MAY_BE_BOOL|MAY_BE_LONG)
ZEND_END_ARG_INFO()






ZEND_FUNCTION(wcli_get_output_handle);
ZEND_FUNCTION(wcli_get_input_handle);
ZEND_FUNCTION(wcli_get_window_handle);


static const zend_function_entry ext_functions[] = {
	ZEND_FE(wcli_get_output_handle, arginfo_wcli_get_output_handle)
	ZEND_FE(wcli_get_input_handle, arginfo_wcli_get_input_handle)
	ZEND_FE(wcli_get_window_handle, arginfo_wcli_get_window_handle)
	ZEND_FE_END
};
