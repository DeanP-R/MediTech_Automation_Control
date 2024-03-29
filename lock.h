/*
  Declarations for lock.cpp
*/
#pragma once
#define RFID_H

#include <SPI.h>
#include <MFRC522.h>
#include <Keypad.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "multiplexer.h"
#include "speakers.h"

#define SS_PIN 53       //SDA pin of RFID
#define RST_PIN 8      //RST pin of RFID

extern bool authorised;

const byte ROWS = 4;
const byte COLS = 4;
extern char keys[ROWS][COLS];
extern byte rowPins[ROWS];
extern byte colPins[COLS];
extern Keypad keypad;
extern Servo myServo;
extern LiquidCrystal_I2C lcd;

void lockSetup();
String lock_op();
String readKeypad();

