#include <windows.h>
#include <string>
#include <iostream>
#define WIDTH 400
#define HEIGHT 200

HANDLE hSerial;

// Open serial port
bool initSerial(const std::wstring& portName) {
    hSerial = CreateFileW(portName.c_str(), GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr);
    if (hSerial == INVALID_HANDLE_VALUE) return false;

    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) return false;

    dcbSerialParams.BaudRate = CBR_115200;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    return SetCommState(hSerial, &dcbSerialParams);
}

// Send string over serial
void sendSerial(const std::string& data) {
    if (hSerial == INVALID_HANDLE_VALUE) return;
    DWORD bytesWritten;
    WriteFile(hSerial, data.c_str(), data.length(), &bytesWritten, nullptr);
}

// Timer IDs for each direction
enum {
    TIMER_UP = 1,
    TIMER_DOWN,
    TIMER_LEFT,
    TIMER_RIGHT
};

// Window procedure
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_KEYDOWN:
        if (!(lParam & 0x40000000)) { // prevent autorepeat from holding key
            switch (wParam) {
            case VK_UP:    SetTimer(hWnd, TIMER_UP, 100, nullptr); break;
            case VK_DOWN:  SetTimer(hWnd, TIMER_DOWN, 100, nullptr); break;
            case VK_LEFT:  SetTimer(hWnd, TIMER_LEFT, 100, nullptr); break;
            case VK_RIGHT: SetTimer(hWnd, TIMER_RIGHT, 100, nullptr); break;
            }
        }
        break;

    case WM_KEYUP:
        switch (wParam) {
        case VK_UP:    KillTimer(hWnd, TIMER_UP); break;
        case VK_DOWN:  KillTimer(hWnd, TIMER_DOWN); break;
        case VK_LEFT:  KillTimer(hWnd, TIMER_LEFT); break;
        case VK_RIGHT: KillTimer(hWnd, TIMER_RIGHT); break;
        }
        break;

    case WM_TIMER:
        switch (wParam) {
        case TIMER_UP:    sendSerial("UP\n"); break;
        case TIMER_DOWN:  sendSerial("DOWN\n"); break;
        case TIMER_LEFT:  sendSerial("LEFT\n"); break;
        case TIMER_RIGHT: sendSerial("RIGHT\n"); break;
        }
        break;

    case WM_DESTROY:
        if (hSerial != INVALID_HANDLE_VALUE) CloseHandle(hSerial);
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}

// Entry point
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR, int nCmdShow) {
    if (!initSerial(L"COM5")) {
        MessageBoxW(nullptr, L"Failed to open COM5", L"Error", MB_OK);
        return 1;
    }

    WNDCLASSW wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"SerialSenderClass";
    RegisterClassW(&wc);

    HWND hWnd = CreateWindowW(wc.lpszClassName, L"Serial Key Sender", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT, nullptr, nullptr, hInstance, nullptr);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
