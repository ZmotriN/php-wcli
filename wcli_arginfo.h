/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 54b0ffc3af871b189435266df516f7575c1b9675 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wcli_test1, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wcli_test2, 0, 0, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, str, IS_STRING, 0, "\"\"")
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_wcli_get_output_handle, 0, 0, MAY_BE_BOOL|MAY_BE_LONG)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_wcli_get_input_handle, 0, 0, MAY_BE_BOOL|MAY_BE_LONG)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_wcli_get_window_handle, 0, 0, MAY_BE_BOOL|MAY_BE_LONG)
ZEND_END_ARG_INFO()






ZEND_FUNCTION(wcli_test1);
ZEND_FUNCTION(wcli_test2);
ZEND_FUNCTION(wcli_get_output_handle);
ZEND_FUNCTION(wcli_get_input_handle);
ZEND_FUNCTION(wcli_get_window_handle);


static const zend_function_entry ext_functions[] = {
	ZEND_FE(wcli_test1, arginfo_wcli_test1)
	ZEND_FE(wcli_test2, arginfo_wcli_test2)
	ZEND_FE(wcli_get_output_handle, arginfo_wcli_get_output_handle)
	ZEND_FE(wcli_get_input_handle, arginfo_wcli_get_input_handle)
	ZEND_FE(wcli_get_window_handle, arginfo_wcli_get_window_handle)
	ZEND_FE_END
};
