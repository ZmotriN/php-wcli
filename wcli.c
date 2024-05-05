/*
Copyright (c) 2024 Maxime Larrivée-Roy

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_wcli.h"
#include "wcli_arginfo.h"
#include <strsafe.h>

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

ZEND_DECLARE_MODULE_GLOBALS(wcli)

static void php_wcli_init_globals(zend_wcli_globals *wcli_globals) {}

static HWND get_console_window_handle();
static BOOL is_cmd_call();
static BOOL get_parent_proc(PROCESSENTRY32 *parent);
static DWORD get_parent_pid();
static HWND get_proc_window(DWORD pid);
static BOOL activate_window(HWND whnd);
static void display_error(LPCTSTR lpszFunction);
static wchar_t *Utf82WideChar(const char *str, int len);
static char *WideChar2Utf8(LPCWCH wcs, int *plen);


PHP_RINIT_FUNCTION(wcli)
{
#if defined(ZTS) && defined(COMPILE_DL_WCLI)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
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
		WCLI_G(ReadConsoleInputExA) = (WCLI_READ)GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "ReadConsoleInputExA");
		FlushConsoleInputBuffer(WCLI_G(ihnd));
	}
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


	// VIRTUAL KEY CODES: https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	REGISTER_LONG_CONSTANT("VK_LBUTTON",             0x01, CONST_CS|CONST_PERSISTENT); // Left mouse button
	REGISTER_LONG_CONSTANT("VK_RBUTTON",             0x02, CONST_CS|CONST_PERSISTENT); // Right mouse button
	REGISTER_LONG_CONSTANT("VK_CANCEL",              0x03, CONST_CS|CONST_PERSISTENT); // Control-break processing
	REGISTER_LONG_CONSTANT("VK_MBUTTON",             0x04, CONST_CS|CONST_PERSISTENT); // Middle mouse button (three-button mouse)
	REGISTER_LONG_CONSTANT("VK_XBUTTON1",            0x05, CONST_CS|CONST_PERSISTENT); // X1 mouse button
	REGISTER_LONG_CONSTANT("VK_XBUTTON2",            0x06, CONST_CS|CONST_PERSISTENT); // X2 mouse button                   
	REGISTER_LONG_CONSTANT("VK_BACK",                0x08, CONST_CS|CONST_PERSISTENT); // BACKSPACE key
	REGISTER_LONG_CONSTANT("VK_TAB",                 0x09, CONST_CS|CONST_PERSISTENT); // TAB key
	REGISTER_LONG_CONSTANT("VK_CLEAR",               0x0C, CONST_CS|CONST_PERSISTENT); // CLEAR key
	REGISTER_LONG_CONSTANT("VK_RETURN",              0x0D, CONST_CS|CONST_PERSISTENT); // ENTER key
	REGISTER_LONG_CONSTANT("VK_SHIFT",               0x10, CONST_CS|CONST_PERSISTENT); // SHIFT key
	REGISTER_LONG_CONSTANT("VK_CONTROL",             0x11, CONST_CS|CONST_PERSISTENT); // CTRL key
	REGISTER_LONG_CONSTANT("VK_MENU",                0x12, CONST_CS|CONST_PERSISTENT); // ALT key
	REGISTER_LONG_CONSTANT("VK_PAUSE",               0x13, CONST_CS|CONST_PERSISTENT); // PAUSE key
	REGISTER_LONG_CONSTANT("VK_CAPITAL",             0x14, CONST_CS|CONST_PERSISTENT); // CAPS LOCK key
	REGISTER_LONG_CONSTANT("VK_KANA",                0x15, CONST_CS|CONST_PERSISTENT); // IME Kana mode
	REGISTER_LONG_CONSTANT("VK_HANGUEL",             0x15, CONST_CS|CONST_PERSISTENT); // IME Hanguel mode (maintained for compatibility; use VK_HANGUL)
	REGISTER_LONG_CONSTANT("VK_HANGUL",              0x15, CONST_CS|CONST_PERSISTENT); // IME Hangul mode
	REGISTER_LONG_CONSTANT("VK_JUNJA",               0x17, CONST_CS|CONST_PERSISTENT); // IME Junja mode
	REGISTER_LONG_CONSTANT("VK_FINAL",               0x18, CONST_CS|CONST_PERSISTENT); // IME final mode
	REGISTER_LONG_CONSTANT("VK_HANJA",               0x19, CONST_CS|CONST_PERSISTENT); // IME Hanja mode
	REGISTER_LONG_CONSTANT("VK_KANJI",               0x19, CONST_CS|CONST_PERSISTENT); // IME Kanji mode
	REGISTER_LONG_CONSTANT("VK_ESCAPE",              0x1B, CONST_CS|CONST_PERSISTENT); // ESC key
	REGISTER_LONG_CONSTANT("VK_CONVERT",             0x1C, CONST_CS|CONST_PERSISTENT); // IME convert
	REGISTER_LONG_CONSTANT("VK_NONCONVERT",          0x1D, CONST_CS|CONST_PERSISTENT); // IME nonconvert
	REGISTER_LONG_CONSTANT("VK_ACCEPT",              0x1E, CONST_CS|CONST_PERSISTENT); // IME accept
	REGISTER_LONG_CONSTANT("VK_MODECHANGE",          0x1F, CONST_CS|CONST_PERSISTENT); // IME mode change request
	REGISTER_LONG_CONSTANT("VK_SPACE",               0x20, CONST_CS|CONST_PERSISTENT); // SPACEBAR
	REGISTER_LONG_CONSTANT("VK_PRIOR",               0x21, CONST_CS|CONST_PERSISTENT); // PAGE UP key
	REGISTER_LONG_CONSTANT("VK_NEXT",                0x22, CONST_CS|CONST_PERSISTENT); // PAGE DOWN key
	REGISTER_LONG_CONSTANT("VK_END",                 0x23, CONST_CS|CONST_PERSISTENT); // END key
	REGISTER_LONG_CONSTANT("VK_HOME",                0x24, CONST_CS|CONST_PERSISTENT); // HOME key
	REGISTER_LONG_CONSTANT("VK_LEFT",                0x25, CONST_CS|CONST_PERSISTENT); // LEFT ARROW key
	REGISTER_LONG_CONSTANT("VK_UP",                  0x26, CONST_CS|CONST_PERSISTENT); // UP ARROW key
	REGISTER_LONG_CONSTANT("VK_RIGHT",               0x27, CONST_CS|CONST_PERSISTENT); // RIGHT ARROW key
	REGISTER_LONG_CONSTANT("VK_DOWN",                0x28, CONST_CS|CONST_PERSISTENT); // DOWN ARROW key
	REGISTER_LONG_CONSTANT("VK_SELECT",              0x29, CONST_CS|CONST_PERSISTENT); // SELECT key
	REGISTER_LONG_CONSTANT("VK_PRINT",               0x2A, CONST_CS|CONST_PERSISTENT); // PRINT key
	REGISTER_LONG_CONSTANT("VK_EXECUTE",             0x2B, CONST_CS|CONST_PERSISTENT); // EXECUTE key
	REGISTER_LONG_CONSTANT("VK_SNAPSHOT",            0x2C, CONST_CS|CONST_PERSISTENT); // PRINT SCREEN key
	REGISTER_LONG_CONSTANT("VK_INSERT",              0x2D, CONST_CS|CONST_PERSISTENT); // INS key
	REGISTER_LONG_CONSTANT("VK_DELETE",              0x2E, CONST_CS|CONST_PERSISTENT); // DEL key
	REGISTER_LONG_CONSTANT("VK_HELP",                0x2F, CONST_CS|CONST_PERSISTENT); // HELP key
	REGISTER_LONG_CONSTANT("VK_LWIN",                0x5B, CONST_CS|CONST_PERSISTENT); // Left Windows key (Natural keyboard)
	REGISTER_LONG_CONSTANT("VK_RWIN",                0x5C, CONST_CS|CONST_PERSISTENT); // Right Windows key (Natural keyboard)
	REGISTER_LONG_CONSTANT("VK_APPS",                0x5D, CONST_CS|CONST_PERSISTENT); // Applications key (Natural keyboard)
	REGISTER_LONG_CONSTANT("VK_SLEEP",               0x5F, CONST_CS|CONST_PERSISTENT); // Computer Sleep key
	REGISTER_LONG_CONSTANT("VK_NUMPAD0",             0x60, CONST_CS|CONST_PERSISTENT); // Numeric keypad 0 key
	REGISTER_LONG_CONSTANT("VK_NUMPAD1",             0x61, CONST_CS|CONST_PERSISTENT); // Numeric keypad 1 key
	REGISTER_LONG_CONSTANT("VK_NUMPAD2",             0x62, CONST_CS|CONST_PERSISTENT); // Numeric keypad 2 key
	REGISTER_LONG_CONSTANT("VK_NUMPAD3",             0x63, CONST_CS|CONST_PERSISTENT); // Numeric keypad 3 key
	REGISTER_LONG_CONSTANT("VK_NUMPAD4",             0x64, CONST_CS|CONST_PERSISTENT); // Numeric keypad 4 key
	REGISTER_LONG_CONSTANT("VK_NUMPAD5",             0x65, CONST_CS|CONST_PERSISTENT); // Numeric keypad 5 key
	REGISTER_LONG_CONSTANT("VK_NUMPAD6",             0x66, CONST_CS|CONST_PERSISTENT); // Numeric keypad 6 key
	REGISTER_LONG_CONSTANT("VK_NUMPAD7",             0x67, CONST_CS|CONST_PERSISTENT); // Numeric keypad 7 key
	REGISTER_LONG_CONSTANT("VK_NUMPAD8",             0x68, CONST_CS|CONST_PERSISTENT); // Numeric keypad 8 key
	REGISTER_LONG_CONSTANT("VK_NUMPAD9",             0x69, CONST_CS|CONST_PERSISTENT); // Numeric keypad 9 key
	REGISTER_LONG_CONSTANT("VK_MULTIPLY",            0x6A, CONST_CS|CONST_PERSISTENT); // Multiply key
	REGISTER_LONG_CONSTANT("VK_ADD",                 0x6B, CONST_CS|CONST_PERSISTENT); // Add key
	REGISTER_LONG_CONSTANT("VK_SEPARATOR",           0x6C, CONST_CS|CONST_PERSISTENT); // Separator key
	REGISTER_LONG_CONSTANT("VK_SUBTRACT",            0x6D, CONST_CS|CONST_PERSISTENT); // Subtract key
	REGISTER_LONG_CONSTANT("VK_DECIMAL",             0x6E, CONST_CS|CONST_PERSISTENT); // Decimal key
	REGISTER_LONG_CONSTANT("VK_DIVIDE",              0x6F, CONST_CS|CONST_PERSISTENT); // Divide key
	REGISTER_LONG_CONSTANT("VK_F1",                  0x70, CONST_CS|CONST_PERSISTENT); // F1 key
	REGISTER_LONG_CONSTANT("VK_F2",                  0x71, CONST_CS|CONST_PERSISTENT); // F2 key
	REGISTER_LONG_CONSTANT("VK_F3",                  0x72, CONST_CS|CONST_PERSISTENT); // F3 key
	REGISTER_LONG_CONSTANT("VK_F4",                  0x73, CONST_CS|CONST_PERSISTENT); // F4 key
	REGISTER_LONG_CONSTANT("VK_F5",                  0x74, CONST_CS|CONST_PERSISTENT); // F5 key
	REGISTER_LONG_CONSTANT("VK_F6",                  0x75, CONST_CS|CONST_PERSISTENT); // F6 key
	REGISTER_LONG_CONSTANT("VK_F7",                  0x76, CONST_CS|CONST_PERSISTENT); // F7 key
	REGISTER_LONG_CONSTANT("VK_F8",                  0x77, CONST_CS|CONST_PERSISTENT); // F8 key
	REGISTER_LONG_CONSTANT("VK_F9",                  0x78, CONST_CS|CONST_PERSISTENT); // F9 key
	REGISTER_LONG_CONSTANT("VK_F10",                 0x79, CONST_CS|CONST_PERSISTENT); // F10 key
	REGISTER_LONG_CONSTANT("VK_F11",                 0x7A, CONST_CS|CONST_PERSISTENT); // F11 key
	REGISTER_LONG_CONSTANT("VK_F12",                 0x7B, CONST_CS|CONST_PERSISTENT); // F12 key
	REGISTER_LONG_CONSTANT("VK_F13",                 0x7C, CONST_CS|CONST_PERSISTENT); // F13 key
	REGISTER_LONG_CONSTANT("VK_F14",                 0x7D, CONST_CS|CONST_PERSISTENT); // F14 key
	REGISTER_LONG_CONSTANT("VK_F15",                 0x7E, CONST_CS|CONST_PERSISTENT); // F15 key
	REGISTER_LONG_CONSTANT("VK_F16",                 0x7F, CONST_CS|CONST_PERSISTENT); // F16 key
	REGISTER_LONG_CONSTANT("VK_F17",                 0x80, CONST_CS|CONST_PERSISTENT); // F17 key
	REGISTER_LONG_CONSTANT("VK_F18",                 0x81, CONST_CS|CONST_PERSISTENT); // F18 key
	REGISTER_LONG_CONSTANT("VK_F19",                 0x82, CONST_CS|CONST_PERSISTENT); // F19 key
	REGISTER_LONG_CONSTANT("VK_F20",                 0x83, CONST_CS|CONST_PERSISTENT); // F20 key
	REGISTER_LONG_CONSTANT("VK_F21",                 0x84, CONST_CS|CONST_PERSISTENT); // F21 key
	REGISTER_LONG_CONSTANT("VK_F22",                 0x85, CONST_CS|CONST_PERSISTENT); // F22 key
	REGISTER_LONG_CONSTANT("VK_F23",                 0x86, CONST_CS|CONST_PERSISTENT); // F23 key
	REGISTER_LONG_CONSTANT("VK_F24",                 0x87, CONST_CS|CONST_PERSISTENT); // F24 key
	REGISTER_LONG_CONSTANT("VK_NUMLOCK",             0x90, CONST_CS|CONST_PERSISTENT); // NUM LOCK key
	REGISTER_LONG_CONSTANT("VK_SCROLL",              0x91, CONST_CS|CONST_PERSISTENT); // SCROLL LOCK key
	REGISTER_LONG_CONSTANT("VK_LSHIFT",              0xA0, CONST_CS|CONST_PERSISTENT); // Left SHIFT key
	REGISTER_LONG_CONSTANT("VK_RSHIFT",              0xA1, CONST_CS|CONST_PERSISTENT); // Right SHIFT key
	REGISTER_LONG_CONSTANT("VK_LCONTROL",            0xA2, CONST_CS|CONST_PERSISTENT); // Left CONTROL key
	REGISTER_LONG_CONSTANT("VK_RCONTROL",            0xA3, CONST_CS|CONST_PERSISTENT); // Right CONTROL key
	REGISTER_LONG_CONSTANT("VK_LMENU",               0xA4, CONST_CS|CONST_PERSISTENT); // Left MENU key
	REGISTER_LONG_CONSTANT("VK_RMENU",               0xA5, CONST_CS|CONST_PERSISTENT); // Right MENU key
	REGISTER_LONG_CONSTANT("VK_BROWSER_BACK",        0xA6, CONST_CS|CONST_PERSISTENT); // Browser Back key
	REGISTER_LONG_CONSTANT("VK_BROWSER_FORWARD",     0xA7, CONST_CS|CONST_PERSISTENT); // Browser Forward key
	REGISTER_LONG_CONSTANT("VK_BROWSER_REFRESH",     0xA8, CONST_CS|CONST_PERSISTENT); // Browser Refresh key
	REGISTER_LONG_CONSTANT("VK_BROWSER_STOP",        0xA9, CONST_CS|CONST_PERSISTENT); // Browser Stop key
	REGISTER_LONG_CONSTANT("VK_BROWSER_SEARCH",      0xAA, CONST_CS|CONST_PERSISTENT); // Browser Search key
	REGISTER_LONG_CONSTANT("VK_BROWSER_FAVORITES",   0xAB, CONST_CS|CONST_PERSISTENT); // Browser Favorites key
	REGISTER_LONG_CONSTANT("VK_BROWSER_HOME",        0xAC, CONST_CS|CONST_PERSISTENT); // Browser Start and Home key
	REGISTER_LONG_CONSTANT("VK_VOLUME_MUTE",         0xAD, CONST_CS|CONST_PERSISTENT); // Volume Mute key
	REGISTER_LONG_CONSTANT("VK_VOLUME_DOWN",         0xAE, CONST_CS|CONST_PERSISTENT); // Volume Down key
	REGISTER_LONG_CONSTANT("VK_VOLUME_UP",           0xAF, CONST_CS|CONST_PERSISTENT); // Volume Up key
	REGISTER_LONG_CONSTANT("VK_MEDIA_NEXT_TRACK",    0xB0, CONST_CS|CONST_PERSISTENT); // Next Track key
	REGISTER_LONG_CONSTANT("VK_MEDIA_PREV_TRACK",    0xB1, CONST_CS|CONST_PERSISTENT); // Previous Track key
	REGISTER_LONG_CONSTANT("VK_MEDIA_STOP",          0xB2, CONST_CS|CONST_PERSISTENT); // Stop Media key
	REGISTER_LONG_CONSTANT("VK_MEDIA_PLAY_PAUSE",    0xB3, CONST_CS|CONST_PERSISTENT); // Play/Pause Media key
	REGISTER_LONG_CONSTANT("VK_LAUNCH_MAIL",         0xB4, CONST_CS|CONST_PERSISTENT); // Start Mail key
	REGISTER_LONG_CONSTANT("VK_LAUNCH_MEDIA_SELECT", 0xB5, CONST_CS|CONST_PERSISTENT); // Select Media key
	REGISTER_LONG_CONSTANT("VK_LAUNCH_APP1",         0xB6, CONST_CS|CONST_PERSISTENT); // Start Application 1 key
	REGISTER_LONG_CONSTANT("VK_LAUNCH_APP2",         0xB7, CONST_CS|CONST_PERSISTENT); // Start Application 2 key
	REGISTER_LONG_CONSTANT("VK_OEM_1",               0xBA, CONST_CS|CONST_PERSISTENT); // Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the ';:' key
	REGISTER_LONG_CONSTANT("VK_OEM_PLUS",            0xBB, CONST_CS|CONST_PERSISTENT); // For any country/region, the '+' key
	REGISTER_LONG_CONSTANT("VK_OEM_COMMA",           0xBC, CONST_CS|CONST_PERSISTENT); // For any country/region, the ',' key
	REGISTER_LONG_CONSTANT("VK_OEM_MINUS",           0xBD, CONST_CS|CONST_PERSISTENT); // For any country/region, the '-' key
	REGISTER_LONG_CONSTANT("VK_OEM_PERIOD",          0xBE, CONST_CS|CONST_PERSISTENT); // For any country/region, the '.' key
	REGISTER_LONG_CONSTANT("VK_OEM_2",               0xBF, CONST_CS|CONST_PERSISTENT); // Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '/?' key
	REGISTER_LONG_CONSTANT("VK_OEM_3",               0xC0, CONST_CS|CONST_PERSISTENT); // Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '`~' key
	REGISTER_LONG_CONSTANT("VK_OEM_4",               0xDB, CONST_CS|CONST_PERSISTENT); // Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '[{' key
	REGISTER_LONG_CONSTANT("VK_OEM_5",               0xDC, CONST_CS|CONST_PERSISTENT); // Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '\|' key
	REGISTER_LONG_CONSTANT("VK_OEM_6",               0xDD, CONST_CS|CONST_PERSISTENT); // Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the ']}' key
	REGISTER_LONG_CONSTANT("VK_OEM_7",               0xDE, CONST_CS|CONST_PERSISTENT); // Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the 'single-quote/double-quote' key
	REGISTER_LONG_CONSTANT("VK_OEM_8",               0xDF, CONST_CS|CONST_PERSISTENT); // Used for miscellaneous characters; it can vary by keyboard.
	REGISTER_LONG_CONSTANT("VK_OEM_102",             0xE2, CONST_CS|CONST_PERSISTENT); // Either the angle bracket key or the backslash key on the RT 102-key keyboard
	REGISTER_LONG_CONSTANT("VK_PROCESSKEY",          0xE5, CONST_CS|CONST_PERSISTENT); // IME PROCESS key
	REGISTER_LONG_CONSTANT("VK_PACKET",              0xE7, CONST_CS|CONST_PERSISTENT); // Used to pass Unicode characters as if they were keystrokes. The VK_PACKET key is the low word of a 32-bit Virtual Key value used for non-keyboard input methods. For more information, see Remark in KEYBDINPUT, SendInput, WM_KEYDOWN, and WM_KEYUP
	REGISTER_LONG_CONSTANT("VK_ATTN",                0xF6, CONST_CS|CONST_PERSISTENT); // Attn key
	REGISTER_LONG_CONSTANT("VK_CRSEL",               0xF7, CONST_CS|CONST_PERSISTENT); // CrSel key
	REGISTER_LONG_CONSTANT("VK_EXSEL",               0xF8, CONST_CS|CONST_PERSISTENT); // ExSel key
	REGISTER_LONG_CONSTANT("VK_EREOF",               0xF9, CONST_CS|CONST_PERSISTENT); // Erase EOF key
	REGISTER_LONG_CONSTANT("VK_PLAY",                0xFA, CONST_CS|CONST_PERSISTENT); // Play key
	REGISTER_LONG_CONSTANT("VK_ZOOM",                0xFB, CONST_CS|CONST_PERSISTENT); // Zoom key
	REGISTER_LONG_CONSTANT("VK_NONAME",              0xFC, CONST_CS|CONST_PERSISTENT); // Reserved
	REGISTER_LONG_CONSTANT("VK_PA1",                 0xFD, CONST_CS|CONST_PERSISTENT); // PA1 key
	REGISTER_LONG_CONSTANT("VK_OEM_CLEAR",           0xFE, CONST_CS|CONST_PERSISTENT); // Clear key
	REGISTER_LONG_CONSTANT("VK_0",                   0x30, CONST_CS|CONST_PERSISTENT); // 0 key
	REGISTER_LONG_CONSTANT("VK_1",                   0x31, CONST_CS|CONST_PERSISTENT); // 1 key
	REGISTER_LONG_CONSTANT("VK_2",                   0x32, CONST_CS|CONST_PERSISTENT); // 2 key
	REGISTER_LONG_CONSTANT("VK_3",                   0x33, CONST_CS|CONST_PERSISTENT); // 3 key
	REGISTER_LONG_CONSTANT("VK_4",                   0x34, CONST_CS|CONST_PERSISTENT); // 4 key
	REGISTER_LONG_CONSTANT("VK_5",                   0x35, CONST_CS|CONST_PERSISTENT); // 5 key
	REGISTER_LONG_CONSTANT("VK_6",                   0x36, CONST_CS|CONST_PERSISTENT); // 6 key
	REGISTER_LONG_CONSTANT("VK_7",                   0x37, CONST_CS|CONST_PERSISTENT); // 7 key
	REGISTER_LONG_CONSTANT("VK_8",                   0x38, CONST_CS|CONST_PERSISTENT); // 8 key
	REGISTER_LONG_CONSTANT("VK_9",                   0x39, CONST_CS|CONST_PERSISTENT); // 9 key
	REGISTER_LONG_CONSTANT("VK_A",                   0x41, CONST_CS|CONST_PERSISTENT); // A key
	REGISTER_LONG_CONSTANT("VK_B",                   0x42, CONST_CS|CONST_PERSISTENT); // B key
	REGISTER_LONG_CONSTANT("VK_C",                   0x43, CONST_CS|CONST_PERSISTENT); // C key
	REGISTER_LONG_CONSTANT("VK_D",                   0x44, CONST_CS|CONST_PERSISTENT); // D key
	REGISTER_LONG_CONSTANT("VK_E",                   0x45, CONST_CS|CONST_PERSISTENT); // E key
	REGISTER_LONG_CONSTANT("VK_F",                   0x46, CONST_CS|CONST_PERSISTENT); // F key
	REGISTER_LONG_CONSTANT("VK_G",                   0x47, CONST_CS|CONST_PERSISTENT); // G key
	REGISTER_LONG_CONSTANT("VK_H",                   0x48, CONST_CS|CONST_PERSISTENT); // H key
	REGISTER_LONG_CONSTANT("VK_I",                   0x49, CONST_CS|CONST_PERSISTENT); // I key
	REGISTER_LONG_CONSTANT("VK_J",                   0x4A, CONST_CS|CONST_PERSISTENT); // J key
	REGISTER_LONG_CONSTANT("VK_K",                   0x4B, CONST_CS|CONST_PERSISTENT); // K key
	REGISTER_LONG_CONSTANT("VK_L",                   0x4C, CONST_CS|CONST_PERSISTENT); // L key
	REGISTER_LONG_CONSTANT("VK_M",                   0x4D, CONST_CS|CONST_PERSISTENT); // M key
	REGISTER_LONG_CONSTANT("VK_N",                   0x4E, CONST_CS|CONST_PERSISTENT); // N key
	REGISTER_LONG_CONSTANT("VK_O",                   0x4F, CONST_CS|CONST_PERSISTENT); // O key
	REGISTER_LONG_CONSTANT("VK_P",                   0x50, CONST_CS|CONST_PERSISTENT); // P key
	REGISTER_LONG_CONSTANT("VK_Q",                   0x51, CONST_CS|CONST_PERSISTENT); // Q key
	REGISTER_LONG_CONSTANT("VK_R",                   0x52, CONST_CS|CONST_PERSISTENT); // R key
	REGISTER_LONG_CONSTANT("VK_S",                   0x53, CONST_CS|CONST_PERSISTENT); // S key
	REGISTER_LONG_CONSTANT("VK_T",                   0x54, CONST_CS|CONST_PERSISTENT); // T key
	REGISTER_LONG_CONSTANT("VK_U",                   0x55, CONST_CS|CONST_PERSISTENT); // U key
	REGISTER_LONG_CONSTANT("VK_V",                   0x56, CONST_CS|CONST_PERSISTENT); // V key
	REGISTER_LONG_CONSTANT("VK_W",                   0x57, CONST_CS|CONST_PERSISTENT); // W key
	REGISTER_LONG_CONSTANT("VK_X",                   0x58, CONST_CS|CONST_PERSISTENT); // X key
	REGISTER_LONG_CONSTANT("VK_Y",                   0x59, CONST_CS|CONST_PERSISTENT); // Y key
	REGISTER_LONG_CONSTANT("VK_Z",                   0x5A, CONST_CS|CONST_PERSISTENT); // Z key

	// INIT GLOBALS
	ZEND_INIT_MODULE_GLOBALS(wcli, php_wcli_init_globals, NULL);
	return SUCCESS;
}


PHP_RSHUTDOWN_FUNCTION(wcli)
{
	if(WCLI_G(console)) {
		FlushConsoleInputBuffer(WCLI_G(ihnd));
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
	PHP_MODULE_GLOBALS(wcli),
	NULL, //PHP_GINIT(wcli),
	NULL,
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
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


ZEND_FUNCTION(wcli_get_console_title)
{
	char title[512];

	ZEND_PARSE_PARAMETERS_NONE();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	if(!GetConsoleTitleA(title, 512)) RETURN_BOOL(FALSE);

	RETURN_STRING(title);
}


ZEND_FUNCTION(wcli_set_console_title)
{
	char *title;
	size_t size;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STRING(title, size)
	ZEND_PARSE_PARAMETERS_END();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	if(!SetConsoleTitle(title)) RETURN_BOOL(FALSE);

	RETURN_BOOL(TRUE);
}


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
	size.Right = w - 1;
	size.Bottom = h - 1;
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


ZEND_FUNCTION(wcli_get_font_size)
{
	CONSOLE_FONT_INFO info;

	ZEND_PARSE_PARAMETERS_NONE();

	if(!WCLI_G(console)) RETURN_BOOL(0);
	GetCurrentConsoleFont(WCLI_G(chnd), FALSE, &info);
	
	array_init(return_value);
	add_index_long(return_value, 0, info.dwFontSize.X);
	add_index_long(return_value, 1, info.dwFontSize.Y);
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


ZEND_FUNCTION(wcli_print)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	DWORD bytes;
	COORD pos;
	char *str;
	size_t size;
	zend_long x, y, fore, back;
	zend_bool x_isnull = 1, y_isnull = 1, fore_isnull = 1, back_isnull = 1;

	ZEND_PARSE_PARAMETERS_START(1, 5)
		Z_PARAM_STRING(str, size)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG_OR_NULL(x, x_isnull)
		Z_PARAM_LONG_OR_NULL(y, y_isnull)
		Z_PARAM_LONG_OR_NULL(fore, fore_isnull)
		Z_PARAM_LONG_OR_NULL(back, back_isnull)
	ZEND_PARSE_PARAMETERS_END();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	if(!GetConsoleScreenBufferInfo(WCLI_G(chnd), &info)) RETURN_BOOL(FALSE);

	if(x_isnull) x = info.dwCursorPosition.X;
	if(y_isnull) y = info.dwCursorPosition.Y;
	if(fore_isnull) fore = info.wAttributes & 0xF;
	if(back_isnull) back = info.wAttributes >> 4;

	pos.X = x;
	pos.Y = y;

	if(!FillConsoleOutputAttribute(WCLI_G(chnd), (back << 4) | fore, size, pos, &bytes))  RETURN_BOOL(FALSE);
	if(!WriteConsoleOutputCharacter(WCLI_G(chnd), str, size, pos, &bytes)) RETURN_BOOL(FALSE);

	RETURN_BOOL(TRUE);
}


ZEND_FUNCTION(wcli_clear)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	COORD pos = { .X = 0, .Y = 0 };
	DWORD nwc;

	ZEND_PARSE_PARAMETERS_NONE();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	if(!GetConsoleScreenBufferInfo(WCLI_G(chnd), &info)) RETURN_BOOL(FALSE);
	if(!FillConsoleOutputAttribute(WCLI_G(chnd), info.wAttributes, info.dwSize.X * info.dwSize.Y, pos, &nwc))  RETURN_BOOL(FALSE);
	if(!FillConsoleOutputCharacter(WCLI_G(chnd), 32, info.dwSize.X * info.dwSize.Y, pos, &nwc)) RETURN_BOOL(FALSE);
	if(!SetConsoleCursorPosition(WCLI_G(chnd), pos)) RETURN_BOOL(FALSE);

	RETURN_BOOL(TRUE);
}


ZEND_FUNCTION(wcli_fill)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	zend_long c, x, y, w, h, fore, back;
	zend_bool fore_isnull = 1, back_isnull = 1;
	WORD color;
	DWORD nwc;
	COORD pos;
	int i;

	ZEND_PARSE_PARAMETERS_START(5, 7)
		Z_PARAM_LONG(c)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG_OR_NULL(fore, fore_isnull)
		Z_PARAM_LONG_OR_NULL(back, back_isnull)
	ZEND_PARSE_PARAMETERS_END();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	if(!GetConsoleScreenBufferInfo(WCLI_G(chnd), &info)) RETURN_BOOL(FALSE);

	if(fore_isnull) fore = info.wAttributes & 0xF;
	if(back_isnull) back = info.wAttributes >> 4;

	if(c < 32 || c > 255) c = 35;
	if(x < 0 || y < 0 || w < 0 || h < 0) RETURN_BOOL(FALSE);
	if((x+w) > info.dwSize.X) w = info.dwSize.X - x;

	pos.X = x;
	color = (back << 4) | fore;

	for(i = 0; i < h && (i + y < info.dwSize.Y); i++) {
		pos.Y = y + i;
		if(!FillConsoleOutputAttribute(WCLI_G(chnd), color, w, pos, &nwc)) RETURN_BOOL(FALSE);
		if(!FillConsoleOutputCharacter(WCLI_G(chnd), c, w, pos, &nwc)) RETURN_BOOL(FALSE);
	}

	RETURN_BOOL(TRUE);
}



// ********************************************************************
// ************************* INPUT FUNCTIONS **************************
// ********************************************************************


ZEND_FUNCTION(wcli_get_key)
{
	INPUT_RECORD buffer;
	DWORD numberOfEventsRead;

	ZEND_PARSE_PARAMETERS_NONE();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	if(!FlushConsoleInputBuffer(WCLI_G(ihnd))) RETURN_BOOL(FALSE);

	do {
		do {
			if(!WCLI_G(ReadConsoleInputExA)(WCLI_G(ihnd), &buffer, 1, &numberOfEventsRead, 0)) RETURN_BOOL(FALSE);
			if(!numberOfEventsRead) RETURN_BOOL(FALSE);
		} while(buffer.EventType != KEY_EVENT);
	} while(!buffer.Event.KeyEvent.bKeyDown);

	RETURN_LONG(buffer.Event.KeyEvent.wVirtualKeyCode);
}


ZEND_FUNCTION(wcli_get_key_async)
{
	INPUT_RECORD buffer;
	DWORD numberOfEventsRead;
	DWORD cNumberOfEvents;

	ZEND_PARSE_PARAMETERS_NONE();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);

	if(!GetNumberOfConsoleInputEvents(WCLI_G(ihnd), &cNumberOfEvents)) RETURN_BOOL(FALSE);
	if(!cNumberOfEvents) RETURN_BOOL(FALSE);

	do {
		do {
			if(!WCLI_G(ReadConsoleInputExA)(WCLI_G(ihnd), &buffer, 1, &numberOfEventsRead, CONSOLE_READ_NOWAIT)) RETURN_BOOL(FALSE);
			if(!numberOfEventsRead) RETURN_BOOL(FALSE);
		} while(buffer.EventType != KEY_EVENT);
	} while(!buffer.Event.KeyEvent.bKeyDown);

	RETURN_LONG(buffer.Event.KeyEvent.wVirtualKeyCode);
}


ZEND_FUNCTION(wcli_flush_input_buffer)
{
	ZEND_PARSE_PARAMETERS_NONE();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	if(!FlushConsoleInputBuffer(WCLI_G(ihnd))) RETURN_BOOL(FALSE);

	RETURN_BOOL(TRUE);
}



// ********************************************************************
// ************************* WINDOW FUNCTIONS *************************
// ********************************************************************


ZEND_FUNCTION(wcli_is_on_top)
{
	ZEND_PARSE_PARAMETERS_NONE();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	if(get_console_window_handle() != GetForegroundWindow()) RETURN_BOOL(FALSE);
	
	RETURN_BOOL(TRUE);
}


ZEND_FUNCTION(wcli_is_visible)
{
	HWND whnd;

	ZEND_PARSE_PARAMETERS_NONE();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	whnd = get_console_window_handle();

	if(!whnd) RETURN_BOOL(FALSE);
	if(!IsWindowVisible(whnd)) RETURN_BOOL(FALSE);
	if(IsIconic(whnd)) RETURN_BOOL(FALSE);

	RETURN_BOOL(TRUE);
}


ZEND_FUNCTION(wcli_get_window_area)
{
	HWND whnd;
	RECT area;

	ZEND_PARSE_PARAMETERS_NONE();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	whnd = get_console_window_handle();
	
	if(!whnd) RETURN_BOOL(FALSE);
	if(!GetWindowRect(whnd, &area)) RETURN_BOOL(FALSE);

	array_init(return_value);
	add_index_long(return_value, 0, area.left);
	add_index_long(return_value, 1, area.top);
	add_index_long(return_value, 2, area.right - area.left);
	add_index_long(return_value, 3, area.bottom - area.top);
}


ZEND_FUNCTION(wcli_get_client_area)
{
	HWND whnd;
	RECT area;
	POINT pos;

	ZEND_PARSE_PARAMETERS_NONE();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	whnd = get_console_window_handle();

	if(!whnd) RETURN_BOOL(FALSE);
	if(!GetClientRect(whnd, &area)) RETURN_BOOL(FALSE);
	
	pos.x = area.left;
	pos.y = area.top;
	if(!ClientToScreen(whnd, &pos)) RETURN_BOOL(FALSE);

	array_init(return_value);
	add_index_long(return_value, 0, pos.x);
	add_index_long(return_value, 1, pos.y);
	add_index_long(return_value, 2, area.right - area.left);
	add_index_long(return_value, 3, area.bottom - area.top);
}


ZEND_FUNCTION(wcli_minimize)
{
	HWND whnd;

	ZEND_PARSE_PARAMETERS_NONE();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	whnd = get_console_window_handle();

	if(!whnd) RETURN_BOOL(FALSE);
	if(!IsWindowVisible(whnd)) RETURN_BOOL(FALSE);
	if(IsIconic(whnd)) RETURN_BOOL(TRUE);
	if(!ShowWindow(whnd, SW_MINIMIZE)) RETURN_BOOL(FALSE);

	RETURN_BOOL(TRUE);
}


ZEND_FUNCTION(wcli_maximize)
{
	HWND whnd;

	ZEND_PARSE_PARAMETERS_NONE();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	whnd = get_console_window_handle();

	if(!whnd) RETURN_BOOL(FALSE);
	if(!IsWindowVisible(whnd)) RETURN_BOOL(FALSE);
	if(!ShowWindow(whnd, SW_MAXIMIZE)) RETURN_BOOL(FALSE);
	
	RETURN_BOOL(TRUE);
}


ZEND_FUNCTION(wcli_restore)
{
	HWND whnd;

	ZEND_PARSE_PARAMETERS_NONE();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	whnd = get_console_window_handle();
	
	if(!whnd) RETURN_BOOL(FALSE);
	if(!IsWindowVisible(whnd)) RETURN_BOOL(FALSE);
	if(!ShowWindow(whnd, SW_RESTORE)) RETURN_BOOL(FALSE);

	RETURN_BOOL(TRUE);
}


ZEND_FUNCTION(wcli_activate)
{
	HWND whnd;

	ZEND_PARSE_PARAMETERS_NONE();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	whnd = get_console_window_handle();
	if(!whnd) RETURN_BOOL(FALSE);

	RETURN_BOOL(activate_window(whnd));
}


ZEND_FUNCTION(wcli_flash)
{
	zend_bool invert = FALSE;
	HWND whnd;

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(invert)
	ZEND_PARSE_PARAMETERS_END();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	whnd = get_console_window_handle();
	if(!whnd) RETURN_BOOL(FALSE);

	RETURN_BOOL(FlashWindow(whnd, invert));
}


ZEND_FUNCTION(wcli_bring_to_front)
{
	HWND whnd;

	ZEND_PARSE_PARAMETERS_NONE();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	whnd = get_console_window_handle();
	
	if(!whnd) RETURN_BOOL(FALSE);
	if(!IsWindowVisible(whnd)) RETURN_BOOL(FALSE);
	if(IsIconic(whnd) && !ShowWindow(whnd, SW_RESTORE)) RETURN_BOOL(FALSE);
	if(!SetWindowPos(whnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW)) RETURN_BOOL(FALSE);
	if(!SetWindowPos(whnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW)) RETURN_BOOL(FALSE);
	
	RETURN_BOOL(BringWindowToTop(whnd));
}


ZEND_FUNCTION(wcli_set_position)
{
	HWND whnd;
	zend_long x, y;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
	ZEND_PARSE_PARAMETERS_END();

	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	whnd = get_console_window_handle();

	if(!whnd) RETURN_BOOL(FALSE);
	if(!activate_window(whnd)) RETURN_BOOL(FALSE);
	if(!SetWindowPos(whnd, HWND_TOP, x, y, 0, 0, SWP_NOSIZE)) RETURN_BOOL(FALSE);

	RETURN_BOOL(TRUE);
}



// ********************************************************************
// ************************** MISC FUNCTIONS **************************
// ********************************************************************


ZEND_FUNCTION(wcli_get_module_path)
{
	unsigned char path[4096];
	unsigned char *rpath;
	DWORD pathsize;

	ZEND_PARSE_PARAMETERS_NONE();

	pathsize = GetModuleFileName(NULL, path, 4096);
	rpath = emalloc(pathsize + 1);
	memcpy(rpath, path, pathsize);
	rpath[pathsize] = 0;
	
	RETURN_STRING(rpath);
}


ZEND_FUNCTION(wcli_get_parent_pid)
{
	DWORD pid;

	ZEND_PARSE_PARAMETERS_NONE();

	pid = get_parent_pid();
	if(pid == 0) RETURN_BOOL(FALSE);

	RETURN_LONG(pid);
}


ZEND_FUNCTION(wcli_is_cmd_call)
{
	ZEND_PARSE_PARAMETERS_NONE();
	
	if(!WCLI_G(console)) RETURN_BOOL(FALSE);
	if(!is_cmd_call()) RETURN_BOOL(FALSE);

	RETURN_BOOL(TRUE);
}


ZEND_FUNCTION(wcli_where)
{
	char *file;
	size_t file_size;
	char *buffer;
	int buffer_size;
	wchar_t *wext;
	wchar_t *wfile;
	wchar_t wbuffer[MAXPATHLEN];
	wchar_t realfile[MAXPATHLEN];

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STRING(file, file_size)
	ZEND_PARSE_PARAMETERS_END();

	wfile = Utf82WideChar(file, file_size);
	wext = PathFindExtensionW(wfile);

	if(wcscmp(wext, L"")) wcscpy(realfile, wfile);
	else swprintf(realfile, MAXPATHLEN, L"%s.exe", wfile);
		
	ZeroMemory(wbuffer, sizeof(wchar_t) * MAXPATHLEN);
	if(!SearchPathW(NULL, realfile, NULL, MAXPATHLEN-1, wbuffer, NULL)) RETURN_BOOL(FALSE);

	buffer = WideChar2Utf8(wbuffer, &buffer_size);
	RETURN_STRING(buffer);
}



// ********************************************************************
// *********************** INTERNAL FUNCTIONS *************************
// ********************************************************************


// Get Current Console Window Handle
static HWND get_console_window_handle()
{
	DWORD pid;

	if(WCLI_G(whnd) != NULL) return WCLI_G(whnd);
	else WCLI_G(whnd) = GetConsoleWindow();

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
	if(_stricmp(proc.szExeFile, (const char *)"cmd.exe") && _stricmp(proc.szExeFile, (const char *)"powershell.exe")) {
		WCLI_G(cmdcall) = FALSE;
		WCLI_G(cmdcalli) = TRUE;
		return FALSE;
	} else {
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
	for(ctn = Process32First(hsnap, &proc); ctn == TRUE; ctn = Process32Next(hsnap, &proc)) {
		if(proc.th32ProcessID == pid){
			break;
		}
	}

	// Get parent process info
	parent->dwSize = sizeof(PROCESSENTRY32);
	for(ctn = Process32First(hsnap, parent); ctn == TRUE; ctn = Process32Next(hsnap, parent)) {
		if(parent->th32ProcessID == proc.th32ParentProcessID) {
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

	for(whnd = FindWindow(NULL, NULL); whnd != NULL; whnd = GetWindow(whnd, GW_HWNDNEXT)) {
		parent = GetParent(whnd);
		GetWindowThreadProcessId(whnd, &wpid);
		if(wpid == pid && !parent) {
			owner = GetWindow(whnd, GW_OWNER);
			if(!owner && IsWindowVisible(whnd)) return whnd;
		}
	}

	return 0;
}


// Activate a window
static BOOL activate_window(HWND whnd)
{
	if(!IsWindowVisible(whnd)) return FALSE;
	if(get_console_window_handle() == GetForegroundWindow()) return TRUE;
	if(!ShowWindow(whnd, SW_MINIMIZE)) return FALSE;
	if(!ShowWindow(whnd, SW_RESTORE)) return FALSE;
	if(!SetWindowPos(whnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE)) return FALSE;
	if(!BringWindowToTop(whnd)) return FALSE;
	return TRUE;
}


// Display the last error. For debuging purpose.
static void display_error(LPCTSTR lpszFunction)
{ 
    // Retrieve the system error message for the last-error code

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    // Display the error message and exit the process

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR)); 
    StringCchPrintf((LPTSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"), 
        lpszFunction, dw, lpMsgBuf); 
    // MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 
	printf("%s\r\n", (LPCTSTR)lpDisplayBuf);

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
}


// Convert UTF-8 to WideChar
static wchar_t *Utf82WideChar(const char *str, int len)
{
	wchar_t *wstr;
	int wlen = 0;
	
	if (!str) return NULL;
	if (len <= 0) len = strlen(str);
	
	wlen = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	wstr = emalloc(sizeof(TCHAR) * (wlen));
	
	if (len > 0) MultiByteToWideChar(CP_UTF8, 0, str, len, wstr, wlen);
	wstr[wlen - 1] = '\0';
	
	return wstr;
}


// Convert WideChar to UTF-8
static char *WideChar2Utf8(LPCWCH wcs, int *plen)
{
	char *str = NULL;
	int str_len = 0;

	if (!wcs) return NULL;

    str_len = WideCharToMultiByte(CP_UTF8, 0, wcs, -1, NULL, 0, NULL, NULL);
    if (str_len == 0) return NULL;

	str = emalloc(str_len);
	int size = WideCharToMultiByte(CP_UTF8, 0, wcs, -1, str, str_len, NULL, NULL);
	str[str_len - 1] = '\0';
	
	if (plen) {
		if (size > 0) size--;
		*plen = size;
	}

	return str;
}