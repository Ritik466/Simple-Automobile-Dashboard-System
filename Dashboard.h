/*
   File Name: dashboard.h
  
    Description:
    This header file defines the CarStatus structure and declares functions
    for updating and rendering the car dashboard in the Win32 GUI application.
  
    Contents:
    - struct CarStatus: Holds car-related data (speed, RPM, fuel, engine temperature,distance, etc).
    - extern struct CarStatus car: A global instance of CarStatus shared across files.
    - UpdateCarStatus(): Updates car parameters such as speed, RPM, fuel, and temperature.
    - DrawDashboard(HDC hdc): Renders car status on the GUI window using Win32 GDI.
  
    Usage:
    Include this file in both main.c and dashboard.c to access the car state and functions.
 */

#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <windows.h>

struct CarStatus {
    int speed;
    int rpm;
    float fuel;
    float enginetemp;
    float fuelused;
    int totalDistance;
    float initialFuel;
};

extern struct CarStatus car;

void UpdateCarStatus();
void DrawDashboard(HDC hdc);

#endif
