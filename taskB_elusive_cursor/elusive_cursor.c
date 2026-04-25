#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define JITTER_INTERVAL 100
#define JITTER_AMOUNT 30

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

BOOL StopActive = FALSE;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                 LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "ElusiveCursor";
    
    if (!RegisterClass(&wc)) {
        MessageBox(NULL, "RegisterClass failed", "Error", MB_OK);
        return 0;
    }
    
    HWND hwnd = CreateWindowEx(0, "ElusiveCursor", "Elusive Cursor",
                           WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                           400, 200, NULL, NULL, hInstance, NULL);
    
    if (!hwnd) {
        MessageBox(NULL, "CreateWindow failed", "Error", MB_OK);
        return 0;
    }
    
    if (!RegisterHotKey(hwnd, 1, MOD_CONTROL | MOD_SHIFT, VK_X)) {
        MessageBox(NULL, "Failed to register hotkey", "Error", MB_OK);
        return 0;
    }
    
    SetTimer(hwnd, 1, JITTER_INTERVAL, NULL);
    ShowWindow(hwnd, nCmdShow);
    
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) && !StopActive) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static POINT lastPos;
    
    switch (uMsg) {
        case WM_TIMER:
            if (wParam == 1) {
                POINT curPos;
                if (GetCursorPos(&curPos)) {
                    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
                    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
                    
                    int newX = curPos.x + (rand() % (JITTER_AMOUNT * 2) - JITTER_AMOUNT);
                    int newY = curPos.y + (rand() % (JITTER_AMOUNT * 2) - JITTER_AMOUNT);
                    
                    newX = (newX < 0) ? 0 : (newX >= screenWidth) ? screenWidth - 1 : newX;
                    newY = (newY < 0) ? 0 : (newY >= screenHeight) ? screenHeight - 1 : newY;
                    
                    SetCursorPos(newX, newY);
                }
            }
            break;
            
        case WM_HOTKEY:
            if (wParam == 1) {
                StopActive = TRUE;
                KillTimer(hwnd, 1);
                UnregisterHotKey(hwnd, 1);
                MessageBox(hwnd, "Elusive Cursor stopped!", "Success", MB_OK);
                PostQuitMessage(0);
            }
            break;
            
        case WM_DESTROY:
            KillTimer(hwnd, 1);
            UnregisterHotKey(hwnd, 1);
            PostQuitMessage(0);
            break;
            
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
