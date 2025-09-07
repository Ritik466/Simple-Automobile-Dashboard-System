/* File Name: Dashboard_Gui(Window Procedure)
    Description:
    This Defines the main entry point (WinMain) and the window procedure (WndProc) for the car Dashoard Gui application.
    It creates the main application window, intialize child controls (such as speed and fuel labels), and handles Windows messages (paint,destroy, etc.).

    Function:
    WNdProc - Handles Window Messages.(Painting the Windows, Quit Events)
    WinMain - Application entry point, registers the window class, creates the main
    Window, child controls, and runs the message
    
    Parameters:
    hwnd - Windows Handle(It is unique indentifier which is used for allowing an application to interact with it.)
    msg - Type of message(holds informaation about a message used for communication between Window and application)
    wParam - Extra Info (button IDs )
    lparam - Extra Info
    
    Returns:
        LRESULT - Result the message handling
*/
#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lparam) {
    switch(msg){
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc =BeginPaint(hwnd, &ps);
            
            TextOut(hdc, 20, 20, "Hello, Win32 GUI!", 18);

            EndPaint(hwnd, &ps);
        } break;

        case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
  
    return DefWindowProc(hwnd, msg, wParam, lparam);

}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const char CLASS_NAME[] = "SimpleWin32App";
    WNDCLASS wc = {0};

    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
         
        CLASS_NAME,
        "Test Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 200,
        NULL, NULL, hInstance, NULL
    );

    CreateWindowEx(
        0,"STATIC","Speed: 0 km/h",
        WS_VISIBLE | WS_CHILD,
        20,50,150,25,
        hwnd, NULL, hInstance, NULL
    );

    CreateWindowEx(
        0,"STATIC","Fuel: 100%",
        WS_VISIBLE | WS_CHILD,
        20,80,150,25,
        hwnd, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}