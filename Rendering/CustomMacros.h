#pragma once

#define SHOW_INIT_ERROR_IN_HWND(OBJ_NAME) MessageBox(hwnd, L"Could not initialize the " OBJ_NAME " ... ", L"Error", MB_OK)