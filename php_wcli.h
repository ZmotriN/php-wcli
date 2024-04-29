/* wcli extension for PHP */

#include "TlHelp32.h"

#ifndef PHP_WCLI_H
# define PHP_WCLI_H

extern zend_module_entry wcli_module_entry;
# define phpext_wcli_ptr &wcli_module_entry

# define PHP_WCLI_VERSION "0.1.0"

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

ZEND_EXTERN_MODULE_GLOBALS(wcli)

#define WCLI_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(wcli, v)

# if defined(ZTS) && defined(COMPILE_DL_WCLI)
ZEND_TSRMLS_CACHE_EXTERN()
# endif


static void flush_input_buffer();
static HWND get_console_window_handle();
static BOOL is_cmd_call();
static BOOL get_parent_proc(PROCESSENTRY32 *parent);
static DWORD get_parent_pid();
static HWND get_proc_window(DWORD pid);
static unsigned char get_key();
static unsigned char get_key_async();


#endif	/* PHP_WCLI_H */
