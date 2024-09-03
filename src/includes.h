#ifndef INCLUDES_H
#define INCLUDES_H
#include <Arduino.h>

#include <stdio.h>
#include "matrix.h"
#include "figure.h"
#include "figures.cpp"
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

#define EEPROM_SIZE 8

#define TICKRATE_LEVEL_1 35
#define TICKRATE_LEVEL_2 25
#define TICKRATE_LEVEL_3 17
#define TICKRATE_LEVEL_KILLZONE 5


#define TIME 0
#define BOUNCE_TIME  140
#define BOUNCE_TIME_DOWN 100

#define DATAPIN1 2
#define LATCHPIN1 0
#define CLOCKPIN1 4
#define LEFTBTN 16

#define RIGHTBTN 19


#define ROTATEBTN 23
#define DOWNBTN 5
#define PAUSEBTN 3
#define SPEAKER 17
#define TOPBTN 
#define DATAPIN2 1
#define LATCHPIN2 
//#define CLOCKPIN2 18



#endif