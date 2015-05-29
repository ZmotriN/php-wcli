#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "php_main.h"
#include "ext/standard/info.h"
#include "php_wcli.h"



ZEND_DECLARE_MODULE_GLOBALS(wcli)


/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("wcli.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_wcli_globals, wcli_globals)
    STD_PHP_INI_ENTRY("wcli.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_wcli_globals, wcli_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_wcli_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_wcli_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "wcli", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/

/* __function_stubs_here__ */

/* {{{ php_wcli_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_wcli_init_globals(zend_wcli_globals *wcli_globals)
{
	wcli_globals->global_value = 0;
	wcli_globals->global_string = NULL;
}
*/
/* }}} */


static void php_wcli_init_globals(zend_wcli_globals *wcli_globals) {}


/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(wcli)
{
	REGISTER_LONG_CONSTANT("Red", FOREGROUND_RED, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("Green", FOREGROUND_GREEN, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("Blue", FOREGROUND_BLUE, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("Bright", FOREGROUND_INTENSITY, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("Yellow", FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("Purple", FOREGROUND_RED|FOREGROUND_BLUE, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("Aqua", FOREGROUND_GREEN|FOREGROUND_BLUE, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("White", FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("Black", 0x00, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("Grey", FOREGROUND_INTENSITY, CONST_CS|CONST_PERSISTENT);

    ZEND_INIT_MODULE_GLOBALS(wcli, php_wcli_init_globals, NULL);
    //REGISTER_INI_ENTRIES();

    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(wcli)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(wcli)
{
	WCLI_G(chnd) = GetStdHandle(STD_OUTPUT_HANDLE);
	if(WCLI_G(chnd) != NULL && WCLI_G(chnd) != INVALID_HANDLE_VALUE) WCLI_G(console) = TRUE;
	else WCLI_G(console) = FALSE;
	if(WCLI_G(console)){
		WCLI_G(ihnd) = GetStdHandle(STD_INPUT_HANDLE);
		WCLI_G(parent).dwSize = 0;
		WCLI_G(whnd) = NULL;
		WCLI_G(cmdcall) = FALSE;
		WCLI_G(cmdcalli) = FALSE;

		GetConsoleScreenBufferInfo(WCLI_G(chnd),&WCLI_G(screen));
		GetConsoleCursorInfo(WCLI_G(chnd),&WCLI_G(cursor));
		GetCurrentConsoleFont(WCLI_G(chnd),FALSE,&WCLI_G(font));

		flush_input_buffer();
	}
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(wcli)
{
	if(WCLI_G(console)){
		flush_input_buffer();
		SetConsoleTextAttribute(WCLI_G(chnd), WCLI_G(screen).wAttributes);
		SetConsoleCursorInfo(WCLI_G(chnd),&WCLI_G(cursor));
	}
	
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(wcli)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "WCLI support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ wcli_functions[]
 *
 * Every user visible function must have an entry in wcli_functions[].
 */
const zend_function_entry wcli_functions[] = {
	PHP_FE(wcli_get_output_handle,	NULL)
	PHP_FE(wcli_get_input_handle,	NULL)
	PHP_FE(wcli_get_window_handle, NULL)

	PHP_FE(wcli_get_cp, NULL)
	PHP_FE(wcli_set_cp, NULL)

	PHP_FE(wcli_clear, NULL)
	PHP_FE(wcli_clear_line, NULL)

	PHP_FE(wcli_get_console_title, NULL)
	PHP_FE(wcli_set_console_title, NULL)

	PHP_FE(wcli_get_console_size, NULL)
	PHP_FE(wcli_set_console_size, NULL)

	PHP_FE(wcli_get_foreground_color, NULL)
	PHP_FE(wcli_set_foreground_color, NULL)
	PHP_FE(wcli_get_background_color, NULL)
	PHP_FE(wcli_set_background_color, NULL)
	PHP_FE(wcli_get_colors, NULL)
	PHP_FE(wcli_set_colors, NULL)
	PHP_FE(wcli_inverse_colors, NULL)
	PHP_FE(wcli_reset_colors, NULL)
	PHP_FE(wcli_default_colors, NULL)
	
	PHP_FE(wcli_show_cursor, NULL)
	PHP_FE(wcli_hide_cursor, NULL)
	PHP_FE(wcli_get_cursor_visibility, NULL)
	PHP_FE(wcli_set_cursor_visibility, NULL)
	PHP_FE(wcli_get_cursor_size, NULL)
	PHP_FE(wcli_set_cursor_size, NULL)
	PHP_FE(wcli_get_cursor_position, NULL)
	PHP_FE(wcli_set_cursor_position, NULL)
	
	PHP_FE(wcli_echo, NULL)
	PHP_FE(wcli_print, NULL)
	PHP_FE(wcli_get_key, NULL)
	PHP_FE(wcli_get_mouse_click, NULL)
	PHP_FE(wcli_flush_input_buffer, NULL)
	PHP_FALIAS(wcli_getch, wcli_get_key, NULL)

	PHP_FE(wcli_get_parent_pid, NULL)
	PHP_FE(wcli_is_cmd_call, NULL)

	PHP_FE(wcli_is_ontop, NULL)
	PHP_FE(wcli_is_visible, NULL)
	PHP_FE(wcli_get_window_area, NULL)
	PHP_FE(wcli_get_client_area, NULL)
	PHP_FE(wcli_minimize, NULL)
	PHP_FE(wcli_maximize, NULL)
	PHP_FE(wcli_restore, NULL)
	PHP_FE(wcli_activate, NULL)
	PHP_FE(wcli_set_position, NULL)

	PHP_FE(wcli_get_clipboard, NULL)
	PHP_FE(wcli_set_clipboard, NULL)
	PHP_FE(wcli_empty_clipboard, NULL)

	PHP_FE(wcli_test, NULL)

	/* __function_entries_here__ */
	{NULL, NULL, NULL}
};
/* }}} */

/* {{{ wcli_module_entry
 */
zend_module_entry wcli_module_entry = {
	STANDARD_MODULE_HEADER,
	"wcli",
	wcli_functions,
	PHP_MINIT(wcli),
	PHP_MSHUTDOWN(wcli),
	PHP_RINIT(wcli),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(wcli),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(wcli),
	PHP_WCLI_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_WCLI
ZEND_GET_MODULE(wcli)
#endif


// ********************************************************************
// ************************* HANDLE FUNCTIONS *************************
// ********************************************************************


PHP_FUNCTION(wcli_get_output_handle) {
	if(!WCLI_G(console)) RETURN_BOOL(0);
	RETURN_LONG((long)WCLI_G(chnd));
}



PHP_FUNCTION(wcli_get_input_handle) {
	if(!WCLI_G(console)) RETURN_BOOL(0);
	RETURN_LONG((long)WCLI_G(ihnd));
}



PHP_FUNCTION(wcli_get_window_handle) {
	if(!WCLI_G(console)) RETURN_BOOL(0);
	RETURN_LONG((LONG)get_console_window_handle());
}


// ********************************************************************
// ************************* CONSOLE FUNCTIONS ************************
// ********************************************************************


PHP_FUNCTION(wcli_get_console_size) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	if(!WCLI_G(console)) RETURN_BOOL(0);
	if(!GetConsoleScreenBufferInfo(WCLI_G(chnd),&info)) RETURN_BOOL(0);
	array_init(return_value);
	add_index_long(return_value, 0, info.srWindow.Right - info.srWindow.Left + 1);
	add_index_long(return_value, 1, info.srWindow.Bottom - info.srWindow.Top + 1);
}

PHP_FUNCTION(wcli_set_console_size) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	BOOL force = FALSE;
	SMALL_RECT size;
	SHORT w, h, bh;
	COORD bsize;
	COORD buff;
	
	if(!WCLI_G(console)) RETURN_BOOL(0);
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll|b", &w, &h, &force) == FAILURE) RETURN_BOOL(0);
	if(!GetConsoleScreenBufferInfo(WCLI_G(chnd),&info)) RETURN_BOOL(0);
	
	bh = info.dwSize.Y;
	if(force) bh = h;
	
	buff.X = info.dwSize.X;
	buff.Y = info.dwSize.Y;
	if(w > info.dwSize.X) buff.X = w;
	if(h > info.dwSize.Y) buff.Y = h;

	if(buff.X != info.dwSize.X || buff.Y != info.dwSize.Y)
		if(!SetConsoleScreenBufferSize(WCLI_G(chnd),buff))  RETURN_BOOL(0);

	size.Top = 0;
	size.Left = 0;
	size.Right = w-1;
	size.Bottom = h-1;
	if(!SetConsoleWindowInfo(WCLI_G(chnd),TRUE,&size)) RETURN_BOOL(0);

	bsize.X = w;
	bsize.Y = bh;
	if(!SetConsoleScreenBufferSize(WCLI_G(chnd),bsize)) RETURN_BOOL(0);
	RETURN_BOOL(1);
}


// https://msdn.microsoft.com/en-us/library/windows/desktop/dd317756(v=vs.85).aspx
PHP_FUNCTION(wcli_get_cp) {
	UINT cp;
	if(!WCLI_G(console)) RETURN_BOOL(0);
	cp = GetConsoleCP();
	RETURN_LONG(cp);
}


PHP_FUNCTION(wcli_set_cp) {
	UINT cp;
	if(!WCLI_G(console)) RETURN_BOOL(0);
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &cp) == FAILURE) RETURN_BOOL(0);
	//printf("CP: %i\n",cp);
	if(!SetConsoleCP(cp)) RETURN_BOOL(0);
	RETURN_BOOL(1);
}


// ********************************************************************
// ************************* COLORS FUNCTIONS *************************
// ********************************************************************


PHP_FUNCTION(wcli_get_foreground_color) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	if(!WCLI_G(console)) RETURN_BOOL(0);
	if(!GetConsoleScreenBufferInfo(WCLI_G(chnd),&info)) RETURN_BOOL(0);
	RETURN_LONG(info.wAttributes & 0xF);
}


PHP_FUNCTION(wcli_set_foreground_color) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	WORD fore;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &fore) == FAILURE) RETURN_BOOL(0);
	if(!WCLI_G(console)) RETURN_BOOL(0);
	if(!GetConsoleScreenBufferInfo(WCLI_G(chnd),&info)) RETURN_BOOL(0);
	if(!SetConsoleTextAttribute(WCLI_G(chnd), (info.wAttributes & 0xF0)|fore)) RETURN_BOOL(0);
	RETURN_BOOL(1);
}


PHP_FUNCTION(wcli_get_background_color) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	if(!WCLI_G(console)) RETURN_BOOL(0);
	if(!GetConsoleScreenBufferInfo(WCLI_G(chnd),&info)) RETURN_BOOL(0);
	RETURN_LONG(info.wAttributes >> 4);
}


PHP_FUNCTION(wcli_set_background_color) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	WORD back;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &back) == FAILURE) RETURN_BOOL(0);
	if(!WCLI_G(console)) RETURN_BOOL(0);
	if(!GetConsoleScreenBufferInfo(WCLI_G(chnd),&info)) RETURN_BOOL(0);
	if(!SetConsoleTextAttribute(WCLI_G(chnd), (info.wAttributes & 0x0F)|(back << 4))) RETURN_BOOL(0);
	RETURN_BOOL(1);
}


PHP_FUNCTION(wcli_get_colors){
	CONSOLE_SCREEN_BUFFER_INFO info;
	if(!WCLI_G(console)) RETURN_BOOL(0);
	if(!GetConsoleScreenBufferInfo(WCLI_G(chnd),&info)) RETURN_BOOL(0);
	array_init(return_value);
	add_index_long(return_value, 0, info.wAttributes & 0xF);
	add_index_long(return_value, 1, info.wAttributes >> 4);
}



PHP_FUNCTION(wcli_set_colors) {
	WORD fore,back;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &fore, &back) == FAILURE) RETURN_BOOL(0);
	if(!WCLI_G(console)) RETURN_BOOL(0);
	if(!SetConsoleTextAttribute(WCLI_G(chnd), (back << 4) | fore)) RETURN_BOOL(0);
	RETURN_BOOL(1);
}


PHP_FUNCTION(wcli_inverse_colors){
	CONSOLE_SCREEN_BUFFER_INFO info;
	if(!WCLI_G(console)) RETURN_BOOL(0);
	if(!GetConsoleScreenBufferInfo(WCLI_G(chnd),&info)) RETURN_BOOL(0);
	if(!SetConsoleTextAttribute(WCLI_G(chnd), ((info.wAttributes & 0xF) << 4) | (info.wAttributes >> 4))) RETURN_BOOL(0);
	RETURN_BOOL(1);
}


PHP_FUNCTION(wcli_reset_colors) {
	if(!WCLI_G(console)) RETURN_BOOL(0);
	if(!SetConsoleTextAttribute(WCLI_G(chnd), WCLI_G(screen).wAttributes)) RETURN_BOOL(0);
	RETURN_BOOL(1);
}


PHP_FUNCTION(wcli_default_colors) {
	if(!WCLI_G(console)) RETURN_BOOL(0);
	WCLI_G(screen).wAttributes = FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE;
	if(!SetConsoleTextAttribute(WCLI_G(chnd), WCLI_G(screen).wAttributes)) RETURN_BOOL(0);
	RETURN_BOOL(1);
}


// ********************************************************************
// ************************* CURSOR FUNCTIONS *************************
// ********************************************************************

//PHP_FUNCTION(wcli_get_cursor_info){
//	CONSOLE_CURSOR_INFO info;
//	if(!WCLI_G(console)) RETURN_BOOL(0);
//	if(!GetConsoleCursorInfo(WCLI_G(chnd),&info)) RETURN_BOOL(0);
//	array_init(return_value);
//	add_index_long(return_value, 0, info.dwSize);
//	add_index_long(return_value, 1, info.bVisible);
//}


PHP_FUNCTION(wcli_show_cursor){
	CONSOLE_CURSOR_INFO info;
	if(!WCLI_G(console)) RETURN_BOOL(0);
	if(!GetConsoleCursorInfo(WCLI_G(chnd),&info)) RETURN_BOOL(0);
	info.bVisible = TRUE;
	if(!SetConsoleCursorInfo(WCLI_G(chnd),&info)) RETURN_BOOL(0);
	RETURN_BOOL(1);
}


PHP_FUNCTION(wcli_hide_cursor){
	CONSOLE_CURSOR_INFO info;
	if(!WCLI_G(console)) RETURN_BOOL(0);
	if(!GetConsoleCursorInfo(WCLI_G(chnd),&info)) RETURN_BOOL(0);
	info.bVisible = FALSE;
	if(!SetConsoleCursorInfo(WCLI_G(chnd),&info)) RETURN_BOOL(0);
	RETURN_BOOL(1);
}


PHP_FUNCTION(wcli_get_cursor_visibility){
	CONSOLE_CURSOR_INFO info;
	if(!WCLI_G(console)) RETURN_BOOL(0);
	if(!GetConsoleCursorInfo(WCLI_G(chnd),&info)) RETURN_BOOL(0);
	RETURN_BOOL(info.bVisible);
}


PHP_FUNCTION(wcli_set_cursor_visibility){
	CONSOLE_CURSOR_INFO info;
	zend_bool visible;
	if(!WCLI_G(console)) RETURN_BOOL(0);
	if(!GetConsoleCursorInfo(WCLI_G(chnd),&info)) RETURN_BOOL(0);
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &visible) == FAILURE) RETURN_BOOL(0);
	info.bVisible = (BOOL)visible;
	if(!SetConsoleCursorInfo(WCLI_G(chnd),&info)) RETURN_BOOL(0);
	RETURN_BOOL(1);
}


PHP_FUNCTION(wcli_set_cursor_size){
	CONSOLE_CURSOR_INFO info;
	DWORD size;
	if(!WCLI_G(console)) RETURN_BOOL(0);
	if(!GetConsoleCursorInfo(WCLI_G(chnd),&info)) RETURN_BOOL(0);
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &size) == FAILURE) RETURN_BOOL(0);
	if(size < 1) size = 1;
	else if(size > 100) size = 100;
	info.dwSize = size;
	if(!SetConsoleCursorInfo(WCLI_G(chnd),&info)) RETURN_BOOL(0);
	RETURN_BOOL(1);
}


PHP_FUNCTION(wcli_get_cursor_size){
	CONSOLE_CURSOR_INFO info;
	if(!WCLI_G(console)) RETURN_BOOL(0);
	if(!GetConsoleCursorInfo(WCLI_G(chnd),&info)) RETURN_BOOL(0);
	RETURN_LONG(info.dwSize);
}


PHP_FUNCTION(wcli_get_cursor_position){
	CONSOLE_SCREEN_BUFFER_INFO info;
	if(!WCLI_G(console)) RETURN_BOOL(0);
	if(!GetConsoleScreenBufferInfo(WCLI_G(chnd),&info)) RETURN_BOOL(0);
	array_init(return_value);
	add_index_long(return_value, 0, info.dwCursorPosition.X);
	add_index_long(return_value, 1, info.dwCursorPosition.Y);
}


PHP_FUNCTION(wcli_set_cursor_position){
	COORD pos;
	SHORT x,y;
	if(!WCLI_G(console)) RETURN_BOOL(0);
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &x,&y) == FAILURE) RETURN_BOOL(0)
	
	// TODO: VERIFY WINDOW SIZE
	pos.X = x;
	pos.Y = y;
	if(!SetConsoleCursorPosition(WCLI_G(chnd),pos)) RETURN_BOOL(0);
	RETURN_BOOL(1);
}


// ********************************************************************
// ************************* INPUT FUNCTIONS **************************
// ********************************************************************
// https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

PHP_FUNCTION(wcli_flush_input_buffer) {
	if(!WCLI_G(console)) RETURN_BOOL(0);
	flush_input_buffer();
	RETURN_BOOL(1);
}


// add timeout
PHP_FUNCTION(wcli_get_key) {
	if(!WCLI_G(console)) RETURN_BOOL(0);
	RETURN_LONG(get_key());
}



// print output characters with [colors] to the cursor position
PHP_FUNCTION(wcli_echo) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	WORD fore,back;
	char *str;
	DWORD size;
	DWORD bytes;

	if(!WCLI_G(console)) RETURN_BOOL(0);
	if(!GetConsoleScreenBufferInfo(WCLI_G(chnd),&info)) RETURN_BOOL(0);
	
	fore = info.wAttributes & 0xF;
	back = info.wAttributes >> 4;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|ll", &str,&size,&fore,&back) == FAILURE) RETURN_BOOL(0)
	if(!WriteConsole(WCLI_G(chnd),str,size,&bytes,NULL)) RETURN_BOOL(0);
	if(!FillConsoleOutputAttribute(WCLI_G(chnd),(back<<4)|fore,size,info.dwCursorPosition,&bytes))  RETURN_BOOL(0);
	
	RETURN_BOOL(1);
}



// print output characters with [colors] to the specified position
PHP_FUNCTION(wcli_print) {
	COORD pos;
	SHORT x,y;
	char *str;
	DWORD size;
	WORD fore = 0x00;//FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE;
	WORD back = 0X00;
	DWORD bytes;

	if(!WCLI_G(console)) RETURN_BOOL(0);
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lls|ll", &x,&y,&str,&size,&fore,&back) == FAILURE) RETURN_BOOL(0)
	
	pos.X = x;
	pos.Y = y;

	if((fore + back) > 0){
		if(!FillConsoleOutputAttribute(WCLI_G(chnd),(back<<4)|fore,size,pos,&bytes))  RETURN_BOOL(0);
	}
	
	if(!WriteConsoleOutputCharacter(WCLI_G(chnd),str,size,pos,&bytes)) RETURN_BOOL(0);
	RETURN_BOOL(1);
}




// add timeout
// return array(key,x,y) (x&y )
PHP_FUNCTION(wcli_get_mouse_click) {
	HWND whnd;
	POINT mouse;
	POINT client;
	SHORT mx,my;
	SHORT cx,cy;
	int i;
	
	if(!WCLI_G(console)) RETURN_BOOL(0);
	whnd = get_console_window_handle();

	if(!whnd) RETURN_BOOL(0);
	for(flush_input_buffer();;){
		if(whnd == GetForegroundWindow()){
			for(i=1; i <= 6; i++){
				if(i != 3 && GetAsyncKeyState(i) & 0x7FFF){
					client.x = 0;
					client.y = 0;
					GetCursorPos(&mouse);
					ClientToScreen(whnd,&client);
					mx = ((SHORT)mouse.x) - ((SHORT)client.x);
					my = (SHORT)(mouse.y - client.y);
					if(mx > 0 && my > 0){
						cx = (SHORT)floor((float)mx / WCLI_G(font).dwFontSize.X);
						cy = (SHORT)floor((float)my / WCLI_G(font).dwFontSize.Y);
						array_init(return_value);
						add_assoc_long(return_value, "key",i);
						add_assoc_long(return_value, "px",mx);
						add_assoc_long(return_value, "py",my);
						add_assoc_long(return_value, "cx",cx);
						add_assoc_long(return_value, "cy",cy);
						FlushConsoleInputBuffer(WCLI_G(ihnd));
						return;
					}
				}
			}
		}
		FlushConsoleInputBuffer(WCLI_G(ihnd));
		Sleep(1);
	}
}


// PAS RAPPORT, JUSTE UNE COPIE <--- to complete, maybe
PHP_FUNCTION(wcli_get_key_async) {
	int i;
	HWND whnd;
	if(!WCLI_G(console)) RETURN_BOOL(0);
	
	// verify whnd
	whnd = get_console_window_handle();
	if(!whnd) RETURN_BOOL(0);

	for(flush_input_buffer();;){
		for(i=8; i <= 256; i++){
			if((GetAsyncKeyState(i) & 0x7FFF) && whnd == GetForegroundWindow()){
				FlushConsoleInputBuffer(WCLI_G(ihnd));
				RETURN_LONG(i);
			}
		}
		Sleep(1);
	}
}



// ********************************************************************
// ************************** MISC FUNCTIONS **************************
// ********************************************************************

PHP_FUNCTION(wcli_clear) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	DWORD nwc;
	COORD pos;
	pos.X = 0;
	pos.Y = 0;


	// à revoir, pas sur pour les set cursor position


	if(!WCLI_G(console)) RETURN_BOOL(0);
	if(!GetConsoleScreenBufferInfo(WCLI_G(chnd),&info)) RETURN_BOOL(0);
	if(!SetConsoleCursorPosition(WCLI_G(chnd),pos)) RETURN_BOOL(0);
	if(!FillConsoleOutputAttribute(WCLI_G(chnd),info.wAttributes,info.dwSize.X*info.dwSize.Y,pos,&nwc))  RETURN_BOOL(0);
	if(!FillConsoleOutputCharacter(WCLI_G(chnd),32,info.dwSize.X*info.dwSize.Y,pos,&nwc)) RETURN_BOOL(0);
	if(!SetConsoleCursorPosition(WCLI_G(chnd),pos)) RETURN_BOOL(0);
	if(!SetConsoleTextAttribute(WCLI_G(chnd), info.wAttributes)) RETURN_BOOL(0); // pas sur de celle là
	RETURN_BOOL(1);
}


PHP_FUNCTION(wcli_clear_line) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	HWND whnd;
	DWORD nwc;
	COORD pos;
	
	int x,y;
	int ls;
	int ln = 1;
	if(!WCLI_G(console)) RETURN_BOOL(0);
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l|l", &ls,&ln) == FAILURE) RETURN_BOOL(0);
	if(!GetConsoleScreenBufferInfo(WCLI_G(chnd),&info)) RETURN_BOOL(0);
	
	
	pos.X = 0;
	pos.Y = ls;


	
	if(!FillConsoleOutputAttribute(WCLI_G(chnd),info.wAttributes,info.dwSize.X*ln,pos,&nwc))  RETURN_BOOL(0);
	if(!FillConsoleOutputCharacter(WCLI_G(chnd),32,info.dwSize.X*ln,pos,&nwc)) RETURN_BOOL(0);
	
	


}



// ********************************************************************
// ************************ PROCESS FUNCTIONS *************************
// ********************************************************************


PHP_FUNCTION(wcli_get_parent_pid) {
	DWORD pid;
	pid = get_parent_pid();
	if(pid == 0) RETURN_BOOL(0);
	RETURN_LONG(pid);
}


PHP_FUNCTION(wcli_is_cmd_call) {
	if(!WCLI_G(console)) RETURN_BOOL(0);
	if(is_cmd_call()) RETURN_BOOL(1);
	RETURN_BOOL(0);
}


PHP_FUNCTION(wcli_test) {

	printf("KEY: %u\n",get_key());
}




// ********************************************************************
// ************************* WINDOW FUNCTIONS *************************
// ********************************************************************


// Return TRUE if console window is on top of other window otherwise return FALSE;
PHP_FUNCTION(wcli_is_ontop) {
	if(!WCLI_G(console)) RETURN_BOOL(0);
	if(get_console_window_handle() == GetForegroundWindow()) RETURN_BOOL(1)
	RETURN_BOOL(0);
}


// Return TRUE/FALSE if console window is visible or not.
PHP_FUNCTION(wcli_is_visible) {
	HWND whnd;
	if(!WCLI_G(console)) RETURN_BOOL(0);
	whnd = get_console_window_handle();
	if(!whnd) RETURN_BOOL(0);
	if(!IsWindowVisible(whnd)) RETURN_BOOL(0);
	if(IsIconic(whnd)) RETURN_BOOL(0);
	RETURN_BOOL(1);
}



// Return console window area
PHP_FUNCTION(wcli_get_window_area) {
	HWND whnd;
	RECT area;
	if(!WCLI_G(console)) RETURN_BOOL(0);
	whnd = get_console_window_handle();
	
	if(!GetWindowRect(whnd,&area)) RETURN_BOOL(0);
	array_init(return_value);
	add_assoc_long(return_value, "l",area.left);
	add_assoc_long(return_value, "t",area.top);
	add_assoc_long(return_value, "r",area.right);
	add_assoc_long(return_value, "b",area.bottom);

	add_assoc_long(return_value, "x",area.left);
	add_assoc_long(return_value, "y",area.top);
	add_assoc_long(return_value, "w",area.right-area.left);
	add_assoc_long(return_value, "h",area.bottom-area.top);
	
}


// Return console window inner area
PHP_FUNCTION(wcli_get_client_area) {
	HWND whnd;
	RECT area;
	POINT pos;
	if(!WCLI_G(console)) RETURN_BOOL(0);
	whnd = get_console_window_handle();

	if(!GetClientRect(whnd,&area)) RETURN_BOOL(0);
	if(!ClientToScreen(whnd,&pos)) RETURN_BOOL(0);

	array_init(return_value);
	add_assoc_long(return_value, "l",(SHORT)pos.x);
	add_assoc_long(return_value, "t",(SHORT)pos.y);
	add_assoc_long(return_value, "r",((SHORT)pos.x)+area.right);
	add_assoc_long(return_value, "b",((SHORT)pos.y)+area.bottom);
	add_assoc_long(return_value, "x",(SHORT)pos.x);
	add_assoc_long(return_value, "y",(SHORT)pos.y);
	add_assoc_long(return_value, "w",area.right-area.left);
	add_assoc_long(return_value, "h",area.bottom-area.top);
}


// Minize console window
PHP_FUNCTION(wcli_minimize) {
	HWND whnd;
	if(!WCLI_G(console)) RETURN_BOOL(0);
	whnd = get_console_window_handle();
	if(!whnd) RETURN_BOOL(0);
	if(!IsWindowVisible(whnd)) RETURN_BOOL(0);
	if(IsIconic(whnd)) RETURN_BOOL(1);
	if(!ShowWindow(whnd,SW_MINIMIZE)) RETURN_BOOL(0);
	RETURN_BOOL(1);
}


PHP_FUNCTION(wcli_maximize) {
	HWND whnd;
	if(!WCLI_G(console)) RETURN_BOOL(0);
	whnd = get_console_window_handle();
	if(!whnd) RETURN_BOOL(0);
	if(!IsWindowVisible(whnd)) RETURN_BOOL(0);
	if(!ShowWindow(whnd,SW_MAXIMIZE)) RETURN_BOOL(0);
	RETURN_BOOL(1);
}



PHP_FUNCTION(wcli_restore) {
	HWND whnd;
	if(!WCLI_G(console)) RETURN_BOOL(0);
	whnd = get_console_window_handle();
	if(!whnd) RETURN_BOOL(0);
	if(!IsWindowVisible(whnd)) RETURN_BOOL(0);
	if(!ShowWindow(whnd,SW_RESTORE)) RETURN_BOOL(0);
	RETURN_BOOL(1);
}


PHP_FUNCTION(wcli_activate) {
	HWND whnd;
	if(!WCLI_G(console)) RETURN_BOOL(0);
	whnd = get_console_window_handle();
	if(!whnd) RETURN_BOOL(0);
	if(!activate_window(whnd)) RETURN_BOOL(0);
	RETURN_BOOL(1);
}


PHP_FUNCTION(wcli_set_position) {
	HWND whnd;
	int x,y;
	if(!WCLI_G(console)) RETURN_BOOL(0);
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &x, &y) == FAILURE) RETURN_BOOL(0);
	whnd = get_console_window_handle();
	if(!whnd) RETURN_BOOL(0);
	if(!activate_window(whnd)) RETURN_BOOL(0);
	if(!SetWindowPos(whnd,HWND_TOP,x,y,0,0,SWP_NOSIZE)) RETURN_BOOL(0);
	RETURN_BOOL(1);
}







// ********************************************************************
// *********************** CLIPBOARD FUNCTIONS ************************
// ********************************************************************


PHP_FUNCTION(wcli_get_clipboard) {
	HANDLE hdata;
	char *pszText;

	BOOL success = FALSE;

	if(OpenClipboard(NULL)){
		hdata = GetClipboardData(CF_TEXT);
		if(hdata != NULL){
			pszText = (char *)(GlobalLock(hdata));
			GlobalUnlock(hdata);
			CloseClipboard();
			if(pszText == NULL){
				RETURN_NULL();
			}else{
				RETURN_STRING(pszText,1);
			}
		}
	}
	if(!success) RETURN_NULL();
}



PHP_FUNCTION(wcli_set_clipboard) {
	char *clip;
	WCHAR *wclip;
	int size;
	BOOL success = FALSE;

	HGLOBAL hdata;
	HGLOBAL hwdata;
	LPTSTR clipcopy;
	LPTSTR wclipcopy;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &clip, &size) == FAILURE) RETURN_BOOL(0);
	
	if(OpenClipboard(NULL)){
		hdata = GlobalAlloc(GMEM_MOVEABLE, size+1); 
		clipcopy = (LPTSTR)GlobalLock(hdata); 
		memcpy(clipcopy, clip, size); 
		GlobalUnlock(hdata);
		if(SetClipboardData(CF_TEXT,hdata)){
			size = size * 2;
			wclip = (WCHAR *)emalloc(size+1);
			if(!UTF8ToUnicode16(clip,wclip,size+2)) printf("Conversion failed\n");
			hwdata = GlobalAlloc(GMEM_MOVEABLE, size+2); 
			wclipcopy = (LPTSTR)GlobalLock(hwdata); 
			memcpy(wclipcopy, wclip, size); 
			GlobalUnlock(hwdata);
			SetClipboardData(CF_UNICODETEXT,hwdata);
			GlobalFree(hwdata);
			efree(wclip);
			success = TRUE;
		}
		GlobalFree(hdata);
		CloseClipboard();
	}
	RETURN_BOOL(success);
}


PHP_FUNCTION(wcli_empty_clipboard) {
	BOOL success = FALSE;
	if(OpenClipboard(NULL)){
		if(EmptyClipboard())
			success = TRUE;
		CloseClipboard();
	}
	RETURN_BOOL(success);
}



// ********************************************************************
// ************************* TITLE FUNCTIONS **************************
// ********************************************************************


PHP_FUNCTION(wcli_get_console_title) {
	char * title[512];
	if(!WCLI_G(console)) RETURN_NULL();
	if(!GetConsoleTitle(title,512)) RETURN_NULL();
	RETURN_STRING(title,1);
}


PHP_FUNCTION(wcli_set_console_title) {
	char *title;
	int size;
	if(!WCLI_G(console)) RETURN_BOOL(0);
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &title, &size) == FAILURE) RETURN_BOOL(0);
	if(!SetConsoleTitle(title)) RETURN_BOOL(0);
	RETURN_BOOL(1);
}


// ********************************************************************
// *********************** INTERNAL FUNCTIONS *************************
// ********************************************************************

BOOL UTF8ToUnicode16(CHAR *in_Src, WCHAR *out_Dst, INT in_MaxLen){
	INT lv_Len;

	if (in_MaxLen <= 0) return FALSE;
	lv_Len = MultiByteToWideChar(CP_UTF8, 0, in_Src, -1, out_Dst, in_MaxLen);
	if (lv_Len < 0) lv_Len = 0;

	if (lv_Len < in_MaxLen) out_Dst[lv_Len] = 0;
	else if (out_Dst[in_MaxLen-1]) out_Dst[0] = 0;

	return TRUE;
}



// Flush Input Console Buffer
void flush_input_buffer(){
	TSRMLS_FETCH();
	int i,k;
	for(k=1; k;){
		for(i=1; i <= 256; i++){
			if(k = GetAsyncKeyState(i)&0x7FFF){
				break;
			}
		}
	}
	FlushConsoleInputBuffer(WCLI_G(ihnd));
}


// Get Current Console Window Handle
HWND get_console_window_handle(){
	DWORD pid;
	TSRMLS_FETCH();

	// Lazy stuff
	if(WCLI_G(whnd) != NULL) return WCLI_G(whnd);

	// The rest of processssss...
	if(is_cmd_call()) pid = get_parent_pid();
	else pid = GetCurrentProcessId();
	WCLI_G(whnd) = get_proc_window(pid);
	return WCLI_G(whnd);
}




// Get Process Main Window Handle
HWND get_proc_window(DWORD pid){
	HWND whnd, parent, owner;
	DWORD wpid;
	
	for(whnd = FindWindow(NULL,NULL); whnd != NULL; whnd = GetWindow(whnd,GW_HWNDNEXT)){
		parent = GetParent(whnd);
		GetWindowThreadProcessId(whnd,&wpid);
		if(wpid == pid && !parent){
			owner = GetWindow(whnd,GW_OWNER);
			if(!owner && IsWindowVisible(whnd)) return whnd;
		}
	}

	return 0;
}


// Get Parent Process
BOOL get_parent_procname(char *procname){
	PROCESSENTRY32 proc;
	TSRMLS_FETCH();
	if(!get_parent_proc(&proc)) return FALSE;
	strcpy(procname,proc.szExeFile);
	return TRUE;
}


// Get Parent Process PID
DWORD get_parent_pid(){
	PROCESSENTRY32 proc;
	TSRMLS_FETCH();
	if(!get_parent_proc(&proc)) return 0;
	else return proc.th32ProcessID;
}


// Get Parent Process Info
BOOL get_parent_proc(PROCESSENTRY32 *parent){
	HANDLE hsnap;
	BOOL ctn;
	DWORD pid;
	PROCESSENTRY32 proc;
	TSRMLS_FETCH();
	
	// Lazy stuff
	if(WCLI_G(parent).dwSize != 0) {
		memcpy(parent,&WCLI_G(parent),sizeof(PROCESSENTRY32));
		return TRUE;
	}

	// Get parent processID
	pid = GetCurrentProcessId();
	hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if(hsnap == INVALID_HANDLE_VALUE) return FALSE;
	proc.dwSize = sizeof(PROCESSENTRY32);
	for(ctn = Process32First(hsnap,&proc); ctn == TRUE; ctn = Process32Next(hsnap,&proc)){
		if(proc.th32ProcessID == pid){
			break;
		}
	}

	// Get parent process info
	parent->dwSize = sizeof(PROCESSENTRY32);
	for(ctn = Process32First(hsnap,parent); ctn == TRUE; ctn = Process32Next(hsnap,parent)){
		if(parent->th32ProcessID == proc.th32ParentProcessID){
			CloseHandle(hsnap);
			memcpy(&WCLI_G(parent),parent,sizeof(PROCESSENTRY32));
			return TRUE;
		}
	}

	CloseHandle(hsnap);
	return FALSE;
}



// Get if it is a command line call or an explorer call;
BOOL is_cmd_call(){
	PROCESSENTRY32 proc;

	TSRMLS_FETCH();
	
	// Lazy stuff
	if(WCLI_G(cmdcalli)) return WCLI_G(cmdcall);

	// Determine if CMD call or not
	if(!get_parent_proc(&proc)) return FALSE;
	//printf("Parent: %s\n",proc.szExeFile);
	//if(strcasecmp(proc.szExeFile,(const char *)"cmd.exe")) {
	//printf("Comp: %i\n",_stricmp(proc.szExeFile,(const char *)"cmd.exe"));
	if(_stricmp(proc.szExeFile,(const char *)"cmd.exe")) {
		WCLI_G(cmdcall) = FALSE;
		WCLI_G(cmdcalli) = TRUE;
		return FALSE;
	}
	else {
		WCLI_G(cmdcall) = TRUE;
		WCLI_G(cmdcalli) = TRUE;
		return TRUE;
	}
}


// Get Keyboard Key
unsigned char get_key(){
	unsigned int i;
	HWND whnd;

	TSRMLS_FETCH();
	whnd = get_console_window_handle();
	if(!whnd) {
		printf("Can't get whnd.\n");
		return 0;
	}

	for(flush_input_buffer();;){
		if(whnd == GetForegroundWindow()){
			for(i=8; i <= 256; i++){
				if(GetAsyncKeyState(i) & 0x7FFF){
					FlushConsoleInputBuffer(WCLI_G(ihnd));
					return i;
				}
			}
		}
		Sleep(1);
	}
}


BOOL activate_window(HWND whnd){
	if(!IsWindowVisible(whnd)) return FALSE;
	if(get_console_window_handle() == GetForegroundWindow()) return TRUE;
	if(!ShowWindow(whnd,SW_MINIMIZE)) return FALSE;
	if(!ShowWindow(whnd,SW_RESTORE)) return FALSE;
	if(!SetWindowPos(whnd,HWND_TOP,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE)) return FALSE;
	if(!BringWindowToTop(whnd)) return FALSE;
	return TRUE;
}



/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */


