/* wcli extension for PHP */

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
	ZEND_INIT_MODULE_GLOBALS(wcli, php_wcli_init_globals, NULL);
	return SUCCESS;
}


PHP_RSHUTDOWN_FUNCTION(wcli)
{
	if(WCLI_G(console)){
		flush_input_buffer();
		SetConsoleTextAttribute(WCLI_G(chnd), WCLI_G(screen).wAttributes);
		SetConsoleCursorInfo(WCLI_G(chnd),&WCLI_G(cursor));
	}
	return SUCCESS;
}


zend_module_entry wcli_module_entry = {
	STANDARD_MODULE_HEADER,
	"wcli",					/* Extension name */
	ext_functions,			/* zend_function_entry */
	PHP_MINIT(wcli),		/* PHP_MINIT - Module initialization */
	NULL,					/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(wcli),		/* PHP_RINIT - Request initialization */
	PHP_RSHUTDOWN(wcli),	/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(wcli),		/* PHP_MINFO - Module info */
	PHP_WCLI_VERSION,		/* Version */
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


ZEND_FUNCTION(wcli_get_output_handle) {
	ZEND_PARSE_PARAMETERS_NONE();
	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	RETURN_LONG((zend_long)WCLI_G(chnd));
}


ZEND_FUNCTION(wcli_get_input_handle) {
	ZEND_PARSE_PARAMETERS_NONE();
	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	RETURN_LONG((zend_long)WCLI_G(ihnd));
}


ZEND_FUNCTION(wcli_get_window_handle) {
	ZEND_PARSE_PARAMETERS_NONE();
	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	RETURN_LONG((zend_long)get_console_window_handle());
}










// ********************************************************************
// *********************** INTERNAL FUNCTIONS *************************
// ********************************************************************


// Flush Input Console Buffer
void flush_input_buffer()
{
	int i, k;
	for(k = 1; k;){
		for(i = 1; i <= 256; i++){
			if(k = GetAsyncKeyState(i) & 0x7FFF){
				break;
			}
		}
	}
	FlushConsoleInputBuffer(WCLI_G(ihnd));
}


// Get Current Console Window Handle
HWND get_console_window_handle()
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
BOOL is_cmd_call()
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
BOOL get_parent_proc(PROCESSENTRY32 *parent)
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
DWORD get_parent_pid()
{
	PROCESSENTRY32 proc;
	if(!get_parent_proc(&proc)) return 0;
	else return proc.th32ProcessID;
}


// Get Process Main Window Handle
HWND get_proc_window(DWORD pid)
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