/* wcli extension for PHP */

#include "TlHelp32.h"

#ifndef PHP_WCLI_H
# define PHP_WCLI_H

extern zend_module_entry wcli_module_entry;
# define phpext_wcli_ptr &wcli_module_entry

# define PHP_WCLI_VERSION "1.0.0"

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

#endif	/* PHP_WCLI_H */
