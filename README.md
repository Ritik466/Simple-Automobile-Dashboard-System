# Simple Automobile DashBoard System (C and win32 API in c)

This project is a simple Car Dashboard with built in pure c using the window 32 API. It display the car status like speed, RPM, fuel, engine temperature and distance. The dashboard updates every second and allows user interaction with Acceleration, Brakes and Nuetral Buttons.

## Features 
    - Speed & RPM simulation
    - Fuel Tracking 
    - Engine Temperature simualation 
    - Distance calculation 
    - Warning of Overheating and Low Fuel 
    - Interactive Buttons like - 
        Accleration(increase the speed).
        Brakes(Decrease the speed).
        Nuetral - reset the speed to 0.
    Tripped data is logged into 'car_status.txt' when you exit.

## File Structure of the Project

    Simple Automobile DashBoard System-
    |--- Dashboard_Gui.c   
    |--- Dasboard.c
    |--- Dashboard.h
    |--- main.c
    |--- LICENSE.md
    |--- Readme.md

# Compilation and Running
    Make sure that you have installed (MINGW) as Win32 api is part of [(MINGW) - GCC for Window]

    Then compile with:

    gcc main.c dashboard.c -o Dashboard_Gui.exe -lgdi32 -luser32

    Run the program:

    Dashboard_Gui.exe

# Usage

    When the program starts, you’ll see a dashboard window with car stats.

    Use the buttons:

    Accelerate → increases speed and fuel usage.

    Brake → decreases speed.

    Neutral → stops the car.

    The dashboard updates every 1 second automatically.

    When you close the program, a trip log is saved in car_log.txt.

**All the GUI with WIN32 API is maded by the ChatGPT except C Logic.**
