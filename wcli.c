
// ********************************************************************
// ************************ EXTENSION POUTINE *************************
// ********************************************************************


#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_wcli.h"
#include "wcli_arginfo.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

ZEND_DECLARE_MODULE_GLOBALS(wcli)

static void php_wcli_init_globals(zend_wcli_globals *wcli_globals) {}


PHP_RINIT_FUNCTION(wcli)
{
	WCLI_G(chnd) = GetStdHandle(STD_OUTPUT_HANDLE);
	if(WCLI_G(chnd) != NULL && WCLI_G(chnd) != INVALID_HANDLE_VALUE) WCLI_G(console) = TRUE;
	else WCLI_G(console) = FALSE;
	if(WCLI_G(console)) {
		WCLI_G(ihnd) = GetStdHandle(STD_INPUT_HANDLE);
		WCLI_G(parent).dwSize = 0;
		WCLI_G(whnd) = NULL;
		WCLI_G(cmdcall) = FALSE;
		WCLI_G(cmdcalli) = FALSE;
		GetConsoleScreenBufferInfo(WCLI_G(chnd), &WCLI_G(screen));
		GetConsoleCursorInfo(WCLI_G(chnd), &WCLI_G(cursor));
		GetCurrentConsoleFont(WCLI_G(chnd), FALSE, &WCLI_G(font));
		flush_input_buffer();
	}

#if defined(ZTS) && defined(COMPILE_DL_WCLI)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}


PHP_MINFO_FUNCTION(wcli)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "wcli support", "enabled");
	php_info_print_table_end();
}


PHP_MINIT_FUNCTION(wcli)
{
	// COLORS
	REGISTER_LONG_CONSTANT("Red",    FOREGROUND_RED, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("Green",  FOREGROUND_GREEN, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("Blue",   FOREGROUND_BLUE, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("Yellow", FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("Purple", FOREGROUND_RED|FOREGROUND_BLUE, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("Aqua",   FOREGROUND_GREEN|FOREGROUND_BLUE, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("White",  FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("Black",  0x00, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("Grey",   FOREGROUND_INTENSITY, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("Bright", FOREGROUND_INTENSITY, CONST_CS|CONST_PERSISTENT);

	// INIT GLOBALS
	ZEND_INIT_MODULE_GLOBALS(wcli, php_wcli_init_globals, NULL);
	return SUCCESS;
}


PHP_RSHUTDOWN_FUNCTION(wcli)
{
	if(WCLI_G(console)) {
		flush_input_buffer();
		SetConsoleTextAttribute(WCLI_G(chnd), WCLI_G(screen).wAttributes);
		SetConsoleCursorInfo(WCLI_G(chnd), &WCLI_G(cursor));
	}
	return SUCCESS;
}


zend_module_entry wcli_module_entry = {
	STANDARD_MODULE_HEADER,
	"wcli",                 /* Extension name */
	ext_functions,          /* zend_function_entry */
	PHP_MINIT(wcli),        /* PHP_MINIT - Module initialization */
	NULL,                   /* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(wcli),        /* PHP_RINIT - Request initialization */
	PHP_RSHUTDOWN(wcli),    /* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(wcli),        /* PHP_MINFO - Module info */
	PHP_WCLI_VERSION,       /* Version */
	STANDARD_MODULE_PROPERTIES
};


#ifdef COMPILE_DL_WCLI
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(wcli)
#endif



// ********************************************************************
// ************************* HANDLE FUNCTIONS *************************
// ********************************************************************


ZEND_FUNCTION(wcli_get_output_handle)
{
	ZEND_PARSE_PARAMETERS_NONE();
	
	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	
	RETURN_LONG((zend_long)WCLI_G(chnd));
}


ZEND_FUNCTION(wcli_get_input_handle)
{
	ZEND_PARSE_PARAMETERS_NONE();
	
	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	
	RETURN_LONG((zend_long)WCLI_G(ihnd));
}


ZEND_FUNCTION(wcli_get_window_handle)
{
	ZEND_PARSE_PARAMETERS_NONE();
	
	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	
	RETURN_LONG((zend_long)get_console_window_handle());
}



// ********************************************************************
// ************************* CONSOLE FUNCTIONS ************************
// ********************************************************************


ZEND_FUNCTION(wcli_get_console_size)
{
	HWND whnd;
	int sx,sy;
	CONSOLE_SCREEN_BUFFER_INFO info;

	ZEND_PARSE_PARAMETERS_NONE();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	if(!GetConsoleScreenBufferInfo(WCLI_G(chnd), &info)) RETURN_BOOL(FALSE);

	whnd = get_console_window_handle();
	sx = GetScrollPos(whnd, SB_HORZ);
	sy = GetScrollPos(whnd, SB_VERT);
	
	array_init(return_value);
	add_index_long(return_value, 0, info.srWindow.Right - info.srWindow.Left + 1);
	add_index_long(return_value, 1, info.srWindow.Bottom - info.srWindow.Top + 1);
	add_index_long(return_value, 2, sx);
	add_index_long(return_value, 3, sy);
}


ZEND_FUNCTION(wcli_set_console_size)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	zend_bool force = FALSE;
	SMALL_RECT size;
	zend_long w, h, bh;
	COORD bsize;
	COORD buff;

	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(force)
	ZEND_PARSE_PARAMETERS_END();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	if(!GetConsoleScreenBufferInfo(WCLI_G(chnd), &info)) RETURN_BOOL(FALSE);

	bh = info.dwSize.Y;
	if(force) bh = h;

	buff.X = info.dwSize.X;
	buff.Y = info.dwSize.Y;
	if(w > info.dwSize.X) buff.X = w;
	if(h > info.dwSize.Y) buff.Y = h;

	if(buff.X != info.dwSize.X || buff.Y != info.dwSize.Y)
		if(!SetConsoleScreenBufferSize(WCLI_G(chnd), buff))
			RETURN_BOOL(FALSE);

	size.Top = 0;
	size.Left = 0;
	size.Right = w-1;
	size.Bottom = h-1;
	if(!SetConsoleWindowInfo(WCLI_G(chnd), TRUE, &size)) RETURN_BOOL(FALSE);

	bsize.X = w;
	bsize.Y = bh;
	if(!SetConsoleScreenBufferSize(WCLI_G(chnd), bsize)) RETURN_BOOL(FALSE);

	RETURN_BOOL(TRUE);
}


ZEND_FUNCTION(wcli_get_buffer_size)
{
	CONSOLE_SCREEN_BUFFER_INFO info;

	ZEND_PARSE_PARAMETERS_NONE();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	if(!GetConsoleScreenBufferInfo(WCLI_G(chnd), &info)) RETURN_BOOL(FALSE);
	
	array_init(return_value);
	add_index_long(return_value, 0, info.dwSize.X);
	add_index_long(return_value, 1, info.dwSize.Y);
}


ZEND_FUNCTION(wcli_set_buffer_size)
{
	zend_long w, h;
	COORD bsize;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
	ZEND_PARSE_PARAMETERS_END();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	
	bsize.X = w;
	bsize.Y = h;
	if(!SetConsoleScreenBufferSize(WCLI_G(chnd), bsize)) RETURN_BOOL(FALSE);

	RETURN_BOOL(TRUE);
}


ZEND_FUNCTION(wcli_get_code_page)
{
	ZEND_PARSE_PARAMETERS_NONE();

	RETURN_LONG(GetConsoleCP());
}


ZEND_FUNCTION(wcli_set_code_page)
{
	zend_long cp;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(cp)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_BOOL(SetConsoleCP(cp));
}



// ********************************************************************
// ************************* COLORS FUNCTIONS *************************
// ********************************************************************


ZEND_FUNCTION(wcli_get_foreground_color)
{
	CONSOLE_SCREEN_BUFFER_INFO info;

	ZEND_PARSE_PARAMETERS_NONE();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	if(!GetConsoleScreenBufferInfo(WCLI_G(chnd), &info)) RETURN_BOOL(FALSE);
	
	RETURN_LONG(info.wAttributes & 0xF);
}


ZEND_FUNCTION(wcli_set_foreground_color)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	zend_long fore;
	
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(fore)
	ZEND_PARSE_PARAMETERS_END();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	if(!GetConsoleScreenBufferInfo(WCLI_G(chnd), &info)) RETURN_BOOL(FALSE);
	if(!SetConsoleTextAttribute(WCLI_G(chnd), (info.wAttributes & 0xF0) | fore)) RETURN_BOOL(FALSE);
	
	RETURN_BOOL(true);
}


ZEND_FUNCTION(wcli_get_background_color)
{
	CONSOLE_SCREEN_BUFFER_INFO info;

	ZEND_PARSE_PARAMETERS_NONE();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	if(!GetConsoleScreenBufferInfo(WCLI_G(chnd), &info)) RETURN_BOOL(FALSE);
	
	RETURN_LONG(info.wAttributes >> 4);
}


ZEND_FUNCTION(wcli_set_background_color)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	zend_long back;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(back)
	ZEND_PARSE_PARAMETERS_END();
	
	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	if(!GetConsoleScreenBufferInfo(WCLI_G(chnd), &info)) RETURN_BOOL(FALSE);
	if(!SetConsoleTextAttribute(WCLI_G(chnd), (info.wAttributes & 0x0F) | (back << 4))) RETURN_BOOL(FALSE);

	RETURN_BOOL(TRUE);
}


ZEND_FUNCTION(wcli_get_colors)
{
	CONSOLE_SCREEN_BUFFER_INFO info;

	ZEND_PARSE_PARAMETERS_NONE();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	if(!GetConsoleScreenBufferInfo(WCLI_G(chnd), &info)) RETURN_BOOL(FALSE);

	array_init(return_value);
	add_index_long(return_value, 0, info.wAttributes & 0xF);
	add_index_long(return_value, 1, info.wAttributes >> 4);
}


ZEND_FUNCTION(wcli_set_colors)
{
	zend_long fore, back;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(fore)
		Z_PARAM_LONG(back)
	ZEND_PARSE_PARAMETERS_END();
	
	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	if(!SetConsoleTextAttribute(WCLI_G(chnd), (back << 4) | fore)) RETURN_BOOL(FALSE);
	
	RETURN_BOOL(TRUE);
}


ZEND_FUNCTION(wcli_inverse_colors)
{
	CONSOLE_SCREEN_BUFFER_INFO info;

	ZEND_PARSE_PARAMETERS_NONE();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	if(!GetConsoleScreenBufferInfo(WCLI_G(chnd), &info)) RETURN_BOOL(FALSE);
	if(!SetConsoleTextAttribute(WCLI_G(chnd), ((info.wAttributes & 0xF) << 4) | (info.wAttributes >> 4))) RETURN_BOOL(FALSE);

	RETURN_BOOL(TRUE);
}


ZEND_FUNCTION(wcli_reset_colors)
{
	ZEND_PARSE_PARAMETERS_NONE();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	if(!SetConsoleTextAttribute(WCLI_G(chnd), WCLI_G(screen).wAttributes)) RETURN_BOOL(FALSE);

	RETURN_BOOL(TRUE);
}



// ********************************************************************
// ************************* CURSOR FUNCTIONS *************************
// ********************************************************************


ZEND_FUNCTION(wcli_hide_cursor)
{
	CONSOLE_CURSOR_INFO info;

	ZEND_PARSE_PARAMETERS_NONE();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	if(!GetConsoleCursorInfo(WCLI_G(chnd), &info)) RETURN_BOOL(FALSE);
	
	info.bVisible = FALSE;
	if(!SetConsoleCursorInfo(WCLI_G(chnd), &info)) RETURN_BOOL(FALSE);
	
	RETURN_BOOL(TRUE);
}


ZEND_FUNCTION(wcli_show_cursor)
{
	CONSOLE_CURSOR_INFO info;
	
	ZEND_PARSE_PARAMETERS_NONE();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	if(!GetConsoleCursorInfo(WCLI_G(chnd), &info)) RETURN_BOOL(FALSE);
	
	info.bVisible = TRUE;
	if(!SetConsoleCursorInfo(WCLI_G(chnd), &info)) RETURN_BOOL(FALSE);
	
	RETURN_BOOL(TRUE);
}


ZEND_FUNCTION(wcli_get_cursor_visibility)
{
	CONSOLE_CURSOR_INFO info;

	ZEND_PARSE_PARAMETERS_NONE();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	if(!GetConsoleCursorInfo(WCLI_G(chnd), &info)) RETURN_BOOL(FALSE);

	RETURN_BOOL(info.bVisible);
}


ZEND_FUNCTION(wcli_set_cursor_visibility)
{
	CONSOLE_CURSOR_INFO info;
	zend_bool visible;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_BOOL(visible)
	ZEND_PARSE_PARAMETERS_END();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	if(!GetConsoleCursorInfo(WCLI_G(chnd), &info)) RETURN_BOOL(FALSE);
	
	info.bVisible = (BOOL)visible;
	if(!SetConsoleCursorInfo(WCLI_G(chnd), &info)) RETURN_BOOL(FALSE);
	
	RETURN_BOOL(TRUE);
}


ZEND_FUNCTION(wcli_get_cursor_size)
{
	CONSOLE_CURSOR_INFO info;
	
	ZEND_PARSE_PARAMETERS_NONE();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	if(!GetConsoleCursorInfo(WCLI_G(chnd), &info)) RETURN_BOOL(FALSE);
	
	RETURN_LONG(info.dwSize);
}


ZEND_FUNCTION(wcli_set_cursor_size)
{
	CONSOLE_CURSOR_INFO info;
	zend_long size;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(size)
	ZEND_PARSE_PARAMETERS_END();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	if(!GetConsoleCursorInfo(WCLI_G(chnd), &info)) RETURN_BOOL(FALSE);
	
	if(size < 1) size = 1;
	else if(size > 100) size = 100;
	info.dwSize = size;
	if(!SetConsoleCursorInfo(WCLI_G(chnd), &info)) RETURN_BOOL(FALSE);
	
	RETURN_BOOL(TRUE);
}


ZEND_FUNCTION(wcli_get_cursor_position)
{
	CONSOLE_SCREEN_BUFFER_INFO info;

	ZEND_PARSE_PARAMETERS_NONE();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	if(!GetConsoleScreenBufferInfo(WCLI_G(chnd), &info)) RETURN_BOOL(FALSE);
	
	array_init(return_value);
	add_index_long(return_value, 0, info.dwCursorPosition.X);
	add_index_long(return_value, 1, info.dwCursorPosition.Y);
}


ZEND_FUNCTION(wcli_set_cursor_position)
{
	COORD pos;
	zend_long x, y;
	CONSOLE_SCREEN_BUFFER_INFO info;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
	ZEND_PARSE_PARAMETERS_END();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	if(!GetConsoleScreenBufferInfo(WCLI_G(chnd), &info)) RETURN_BOOL(FALSE);

	pos.X = x;
	pos.Y = y;
	if(pos.X < 0) pos.X = 0;
	if(pos.Y < 0) pos.Y = 0;
	if(!SetConsoleCursorPosition(WCLI_G(chnd), pos)) RETURN_BOOL(FALSE);

	RETURN_BOOL(TRUE);
}


ZEND_FUNCTION(wcli_move_cursor)
{
	COORD pos;
	zend_long x, y;
	CONSOLE_SCREEN_BUFFER_INFO info;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
	ZEND_PARSE_PARAMETERS_END();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	if(!GetConsoleScreenBufferInfo(WCLI_G(chnd), &info)) RETURN_BOOL(FALSE);
	
	pos.X = x + info.dwCursorPosition.X;
	pos.Y = y + info.dwCursorPosition.Y;
	if(pos.X < 0) pos.X = 0;
	if(pos.Y < 0) pos.Y = 0;
	if(pos.X >= (info.srWindow.Right - info.srWindow.Left + 1)) pos.X = info.srWindow.Right - info.srWindow.Left;
	if(pos.Y >= (info.srWindow.Bottom - info.srWindow.Top + 1)) pos.Y = info.srWindow.Bottom - info.srWindow.Top;
	if(!SetConsoleCursorPosition(WCLI_G(chnd), pos)) RETURN_BOOL(FALSE);

	RETURN_BOOL(TRUE);
}



// ********************************************************************
// ************************* OUTPUT FUNCTIONS *************************
// ********************************************************************


ZEND_FUNCTION(wcli_echo)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	zend_long fore, back;
	zend_bool fore_isnull = 1, back_isnull = 1;
	char *str;
	size_t size;
	DWORD bytes;

	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_STRING(str, size)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG_OR_NULL(fore, fore_isnull)
		Z_PARAM_LONG_OR_NULL(back, back_isnull)
	ZEND_PARSE_PARAMETERS_END();
	
	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	if(!GetConsoleScreenBufferInfo(WCLI_G(chnd), &info)) RETURN_BOOL(FALSE);
	
	if(fore_isnull) fore = info.wAttributes & 0xF;
	if(back_isnull) back = info.wAttributes >> 4;

	if(!SetConsoleTextAttribute(WCLI_G(chnd), (back << 4) | fore)) RETURN_BOOL(FALSE);
	if(!WriteConsole(WCLI_G(chnd), str, size, &bytes, NULL)) RETURN_BOOL(FALSE);
	if(!SetConsoleTextAttribute(WCLI_G(chnd), info.wAttributes)) RETURN_BOOL(FALSE);
	
	RETURN_BOOL(TRUE);
}






// ********************************************************************
// *********************** INTERNAL FUNCTIONS *************************
// ********************************************************************


// Flush Input Console Buffer
static void flush_input_buffer()
{
	int i, k;
	for(k = 1; k;) {
		for(i = 1; i <= 256; i++) {
			if(k = GetAsyncKeyState(i) & 0x7FFF) {
				break;
			}
		}
	}
	FlushConsoleInputBuffer(WCLI_G(ihnd));
}


// Get Current Console Window Handle
static HWND get_console_window_handle()
{
	DWORD pid;

	// Lazy stuff
	if(WCLI_G(whnd) != NULL) return WCLI_G(whnd);

	// The rest of processssss...
	if(is_cmd_call()) pid = get_parent_pid();
	else pid = GetCurrentProcessId();
	WCLI_G(whnd) = get_proc_window(pid);
	return WCLI_G(whnd);
}


// Get if it is a command line call or an explorer call;
static BOOL is_cmd_call()
{
	PROCESSENTRY32 proc;

	// Lazy stuff
	if(WCLI_G(cmdcalli)) return WCLI_G(cmdcall);

	// Determine if CMD call or not
	if(!get_parent_proc(&proc)) return FALSE;
	if(_stricmp(proc.szExeFile, (const char *)"cmd.exe")) {
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


// Get Parent Process Info
static BOOL get_parent_proc(PROCESSENTRY32 *parent)
{
	HANDLE hsnap;
	BOOL ctn;
	DWORD pid;
	PROCESSENTRY32 proc;

	// Lazy stuff
	if(WCLI_G(parent).dwSize != 0) {
		memcpy(parent, &WCLI_G(parent), sizeof(PROCESSENTRY32));
		return TRUE;
	}

	// Get parent processID
	pid = GetCurrentProcessId();
	hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(hsnap == INVALID_HANDLE_VALUE) return FALSE;
	proc.dwSize = sizeof(PROCESSENTRY32);
	for(ctn = Process32First(hsnap, &proc); ctn == TRUE; ctn = Process32Next(hsnap, &proc)){
		if(proc.th32ProcessID == pid){
			break;
		}
	}

	// Get parent process info
	parent->dwSize = sizeof(PROCESSENTRY32);
	for(ctn = Process32First(hsnap, parent); ctn == TRUE; ctn = Process32Next(hsnap, parent)){
		if(parent->th32ProcessID == proc.th32ParentProcessID){
			CloseHandle(hsnap);
			memcpy(&WCLI_G(parent), parent, sizeof(PROCESSENTRY32));
			return TRUE;
		}
	}

	CloseHandle(hsnap);
	return FALSE;
}


// Get Parent Process PID
static DWORD get_parent_pid()
{
	PROCESSENTRY32 proc;
	if(!get_parent_proc(&proc)) return 0;
	else return proc.th32ProcessID;
}


// Get Process Main Window Handle
static HWND get_proc_window(DWORD pid)
{
	HWND whnd, parent, owner;
	DWORD wpid;

	for(whnd = FindWindow(NULL, NULL); whnd != NULL; whnd = GetWindow(whnd, GW_HWNDNEXT)){
		parent = GetParent(whnd);
		GetWindowThreadProcessId(whnd, &wpid);
		if(wpid == pid && !parent){
			owner = GetWindow(whnd, GW_OWNER);
			if(!owner && IsWindowVisible(whnd)) return whnd;
		}
	}

	return 0;
}