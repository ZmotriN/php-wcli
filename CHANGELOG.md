# Change Log

## [Unreleased] - yyyy-mm-dd

### Added

### Changed

### Fixed
- Optimize wcli_get_key_async()


## [1.0.2] - 2024-05-03

### Added
- Virtual Key Codes constants VK_*

### Fixed
- Optimise wcli_get_key & wcli_get_key_async
- wcli_get_key: check numberOfEventsRead in loop


## [1.0.1] - 2024-05-02

### Changed
- Change licence to MIT
- wcli_get_key() use ReadConsoleInputExA instead of GetKeyState
- wcli_get_key_async() use ReadConsoleInputExA instead of GetAsyncKeyState

### Fixed
- Detect Powershell console
- Simplify get_console_window_handle()
- Fix input on virtual terminal like VS Code

## [1.0.0] - 2024-04-30

Initial release


