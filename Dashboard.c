/* File Name: Dashboard.c
    Description:
    This File Implements the core logic and drawing functions for the car dashboard GUI
    It Contains:
    - A global Carstatus struct instances representing the current state of car.
    - UpdateCarStatus(): updates speed, RPM, Fuel consumption, engine temperature,
    total distance, and fuel used based on simple Logic.
    - DrawDashboard(): uses Win32 GDI functions to display car status information (speed, fuel, rpm, enginetemp) on application window  
    
    Functions:
    void updatecarstatus()
    updates the car's status each cycle (timer)
    
    void drawstatus()
    draw the car's status onto the given device context (wm_paint)
    
    global variables:
    struct Carstatus car
    holds the current values for speed, rpm, fuel, temperature, distance
    
*/
    


#include <windows.h>
#include <stdio.h>
#include <time.h>      
#include "dashboard.h"

struct CarStatus car = {0, 0, 100.0, 40.0, 0.0, 0, 100.0};

void UpdateCarStatus() {
    //---- Update RPM ----
    if (car.speed == 0)
        car.rpm = 1000 + rand() % 1200;
    else if (car.speed <= 20)
        car.rpm = 1000 + rand() % 1500;
    else if (car.speed <= 40)
        car.rpm = 1500 + rand() % 3500;
    else if (car.speed <= 80)
        car.rpm = 3500 + rand() % 5500;
    else if (car.speed <= 120)
        car.rpm = 5500 + rand() % 7000;
    else
        car.rpm = 0;

    //-- Fuel Consumption --
    if (car.speed <= 60 && car.speed > 0)
        car.fuel -= 0.2;   // slower usage
    else if (car.speed > 60)
        car.fuel -= 0.5;   // faster usage
    if (car.fuel < 0) car.fuel = 0;

    // -- Engine Temperature --
    if (car.speed > 0 && car.enginetemp < 120) {
        car.enginetemp += 0.5;  // heats up gradually
    } else if (car.speed == 0 && car.enginetemp > 40) {
        car.enginetemp -= 0.5;  // cools down
    }

    // ---- Distance ----
    car.totalDistance += (car.speed / 60.0);

    // ---- Fuel Used ----
    car.fuelused = car.initialFuel - car.fuel;
}


void DrawDashboard(HDC hdc) {
    char buffer[128];

    wsprintf(buffer, "Speed: %d km/h", car.speed);
    TextOut(hdc, 20, 20, buffer, lstrlen(buffer));

    wsprintf(buffer, "RPM: %d", car.rpm);
    TextOut(hdc, 20, 50, buffer, lstrlen(buffer));

    wsprintf(buffer, "Fuel Level: %.1f%%", car.fuel);
    TextOut(hdc, 20, 80, buffer, lstrlen(buffer));

    wsprintf(buffer, "Engine Temp: %.1f C", car.enginetemp);
    TextOut(hdc, 20, 110, buffer, lstrlen(buffer));

    wsprintf(buffer, "Total Distance: %d km", car.totalDistance);
    TextOut(hdc, 20, 140, buffer, lstrlen(buffer));

    wsprintf(buffer, "Fuel Used: %.1f%%", car.fuelused);
    TextOut(hdc, 20, 170, buffer, lstrlen(buffer));

    if (car.fuel < 10.0)
        TextOut(hdc, 20, 200, "Warning: Low Fuel!", 19);
    if (car.enginetemp > 100.0)
        TextOut(hdc, 20, 220, "Warning: Overheating!", 24);
}
