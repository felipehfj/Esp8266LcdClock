/*
 * Displays text sent over the serial port (e.g. from the Serial Monitor) on
 * an attached LCD.
 * YWROBOT
 *Compatible with the Arduino IDE 1.0
 *Library version:1.1
 */
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "utils.h"

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

WiFiUDP ntpUDP;
#define offset -10800 // UTC -1 = -3600,UTC +1 = 3600, UTC +2 = 7200 (FOR EVERY +1 HOUR ADD 3600,SUBTRACT 3600 FOR -1 HOUR)
NTPClient timeClient(ntpUDP, "pool.ntp.org");

void setup()
{
  Serial.begin(115200); // initialize serial communication at 115200 bits per second:
  while (!Serial)
    ; // Wait until Serial is ready

  WiFi.begin(ssid, password);
  timeClient.begin();
  timeClient.setTimeOffset(offset);
  lcd.init();
  lcd.backlight();
  lcd.blink_on();
  lcd.clear();
}

void loop()
{
  timeClient.update();
  time_t epochTime = timeClient.getEpochTime();
  String formattedTime = timeClient.getFormattedTime();
  struct tm *ptm = gmtime((time_t *)&epochTime);

  int monthDay = ptm->tm_mday;
  int currentMonth = ptm->tm_mon + 1;
  int currentYear = ptm->tm_year + 1900;
  String currentDate = String(monthDay) + "/" + String(currentMonth) + "/" + String(currentYear);

  lcd.setCursor(0, 0);
  lcd.print("DATE:" + currentDate);
  lcd.setCursor(0, 1);
  lcd.print("TIME:" + formattedTime);
  lcd.setCursor(15, 1);
  delay(500);
}