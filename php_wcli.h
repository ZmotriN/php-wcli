/* __header_here__ */

#include "Windows.h"
#include "TlHelp32.h"


#ifndef PHP_WCLI_H
#define PHP_WCLI_H

extern zend_module_entry wcli_module_entry;
#define phpext_wcli_ptr &wcli_module_entry

#define PHP_WCLI_VERSION "0.1.0" /* Replace with version number for your extension */

/*
ZEND_BEGIN_MODULE_GLOBALS(wcli)
HANDLE chnd;
HANDLE ihnd;
ZEND_END_MODULE_GLOBALS(wcli)
*/

#ifdef PHP_WIN32
#	define PHP_WCLI_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_WCLI_API __attribute__ ((visibility("default")))
#else
#	define PHP_WCLI_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif


ZEND_BEGIN_MODULE_GLOBALS(wcli)
    BOOL console;
	BOOL cmdcall;
	BOOL cmdcalli;
	HANDLE chnd;
	HANDLE ihnd;
	HWND whnd;
	PROCESSENTRY32 parent;
	CONSOLE_SCREEN_BUFFER_INFO screen;
	CONSOLE_CURSOR_INFO cursor;
	CONSOLE_FONT_INFO font;
ZEND_END_MODULE_GLOBALS(wcli)

#ifdef ZTS
#define WCLI_G(v) TSRMG(wcli_globals_id, zend_wcli_globals *, v)
#else
#define WCLI_G(v) (WCLI_globals.v)
#endif

void flush_input_buffer();
HWND  get_proc_window(DWORD pid);
BOOL  get_parent_proc(PROCESSENTRY32 *parent);
BOOL  get_parent_procname(char *procname);
DWORD get_parent_pid();
HWND  get_console_window_handle();
BOOL  is_cmd_call();
unsigned char get_key();
BOOL  UTF8ToUnicode16(CHAR *in_Src, WCHAR *out_Dst, INT in_MaxLen);
BOOL activate_window(HWND whnd);

PHP_FUNCTION(wcli_get_output_handle);
PHP_FUNCTION(wcli_get_input_handle);
PHP_FUNCTION(wcli_get_window_handle);

PHP_FUNCTION(wcli_get_cp);
PHP_FUNCTION(wcli_set_cp);

PHP_FUNCTION(wcli_get_console_title);
PHP_FUNCTION(wcli_set_console_title);

PHP_FUNCTION(wcli_get_console_size);
PHP_FUNCTION(wcli_set_console_size);

PHP_FUNCTION(wcli_clear);
PHP_FUNCTION(wcli_clear_line);

PHP_FUNCTION(wcli_get_foreground_color);
PHP_FUNCTION(wcli_set_foreground_color);
PHP_FUNCTION(wcli_get_background_color);
PHP_FUNCTION(wcli_set_background_color);
PHP_FUNCTION(wcli_get_colors);
PHP_FUNCTION(wcli_set_colors);
PHP_FUNCTION(wcli_inverse_colors);
PHP_FUNCTION(wcli_reset_colors);
PHP_FUNCTION(wcli_default_colors);

PHP_FUNCTION(wcli_show_cursor);
PHP_FUNCTION(wcli_hide_cursor);
PHP_FUNCTION(wcli_get_cursor_visibility);
PHP_FUNCTION(wcli_set_cursor_visibility);
PHP_FUNCTION(wcli_get_cursor_size);
PHP_FUNCTION(wcli_set_cursor_size);
PHP_FUNCTION(wcli_get_cursor_position);
PHP_FUNCTION(wcli_set_cursor_position);

PHP_FUNCTION(wcli_echo);
PHP_FUNCTION(wcli_print);
PHP_FUNCTION(wcli_get_key);
PHP_FUNCTION(wcli_get_mouse_click);
PHP_FUNCTION(wcli_flush_input_buffer);

PHP_FUNCTION(wcli_get_parent_pid);
PHP_FUNCTION(wcli_is_cmd_call);

PHP_FUNCTION(wcli_is_ontop);
PHP_FUNCTION(wcli_is_visible);
PHP_FUNCTION(wcli_get_window_area);
PHP_FUNCTION(wcli_get_client_area);
PHP_FUNCTION(wcli_minimize);
PHP_FUNCTION(wcli_maximize);
PHP_FUNCTION(wcli_restore);
PHP_FUNCTION(wcli_activate);
PHP_FUNCTION(wcli_set_position);

PHP_FUNCTION(wcli_get_clipboard);
PHP_FUNCTION(wcli_set_clipboard);
PHP_FUNCTION(wcli_empty_clipboard);

PHP_FUNCTION(wcli_test);



/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(wcli)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(wcli)
*/

/* In every utility function you add that needs to use variables 
   in php_wcli_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as wcli_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define WCLI_G(v) TSRMG(wcli_globals_id, zend_wcli_globals *, v)
#else
#define WCLI_G(v) (wcli_globals.v)
#endif



#endif	/* PHP_wcli_H */

/* __footer_here__ */
