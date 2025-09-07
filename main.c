/* File Name: Dashboard_Gui(Window Procedure)
    Functions: This File Handles the Window Message (Button Click, Timers, Paint event)
    
    Header:

    Parameters:
    hwnd - Windows Handle(It is unique indentifier which is used for allowing an application to interact with it.)
    msg - Type of message(holds informaation about a message used for communication between Window and application)
    wParam - Extra Info (button IDs )
    lparam - Extra Info
    
    Returns:
        LRESULT - Result the message handling
*/






#include <windows.h>
#include <stdio.h>
#include "dashboard.h"
#include <time.h> 

HINSTANCE g_hInstance;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            CreateWindow("BUTTON", "Accelerate", WS_VISIBLE | WS_CHILD,
                         20, 260, 100, 30, hwnd, (HMENU)1, g_hInstance, NULL);
            CreateWindow("BUTTON", "Brake", WS_VISIBLE | WS_CHILD,
                         140, 260, 100, 30, hwnd, (HMENU)2, g_hInstance, NULL);
            CreateWindow("BUTTON", "Neutral", WS_VISIBLE | WS_CHILD,
                         260, 260, 100, 30, hwnd, (HMENU)3, g_hInstance, NULL);

            SetTimer(hwnd, 1, 1000, NULL);
            srand((unsigned)time(NULL));
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case 1:
                    car.speed += 10;
                    if (car.speed > 120) car.speed = 120;
                    break;
                case 2:
                    car.speed -= 10;
                    if (car.speed < 0) car.speed = 0;
                    break;
                case 3:
                    car.speed = 0;
                    break;
            }
            break;

        case WM_TIMER:
            UpdateCarStatus();
            InvalidateRect(hwnd, NULL, TRUE);
            break;

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            DrawDashboard(hdc);
            EndPaint(hwnd, &ps);
        } break;

        case WM_DESTROY: {
            FILE *log = fopen("car_log.txt", "a");
            if (log) {
                fprintf(log, "Speed: %d, RPM: %d, Fuel: %.1f%%, Temp: %.1f°C, Distance: %d km, Fuel Used: %.1f%%, Remaining: %.1f%%\n",
                        car.speed, car.rpm, car.fuel, car.enginetemp,
                        car.totalDistance, car.fuelused, car.fuel);
                fclose(log);
            }
            KillTimer(hwnd, 1);
            PostQuitMessage(0);
        } break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    g_hInstance = hInstance;
    const char CLASS_NAME[] = "CarDashboard";
    WNDCLASS wc = {0};

    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Car Dashboard",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 350,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
