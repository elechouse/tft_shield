/**
 * @file    tft_hx8352_rotation.ino
 * @author  www.elechouse.com
 * @brief   example of ELECHOUSE TFTShield.
 * 
 * 
 * Rotation function demo.
 * 
 * @section  HISTORY
 * 
 * 2013-06-26  V1.0 initial version
 * 
 * Copyright (c) 2013 www.elechouse.com  All right reserved.
 */

#include <Adafruit_GFX.h>    // Core graphics library
#include <tftlib.h>          // Hardware-specific library

/** colors */
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


TFTLCD myTFT;
unsigned long last_time;
uint8_t rotation;

void setup(void)
{
  myTFT.begin();

  myTFT.setRotation(0);
  myTFT.fillScreen(BLACK);
  myTFT.setCursor(0, 0);
  myTFT.setTextColor(WHITE, BLUE);
  myTFT.println("Elechouse TFT shield Demo");
  myTFT.println("-------------------------");
  myTFT.println("-------2013-06-26--------");
  myTFT.println("-------------------------");
  myTFT.print("Rotation: ");
  myTFT.print(0);
  myTFT.println("--------------");
  myTFT.println("-------------------------");

  last_time = millis();
  rotation = 1;
}

void loop(void)
{
  if(millis() - last_time > 3500){
    last_time = millis();
    
    myTFT.setRotation(rotation);
    myTFT.fillScreen(BLACK);
    myTFT.setCursor(0, 0);
    myTFT.setTextColor(WHITE, BLUE);
    myTFT.println("Elechouse TFT shield Demo");
    myTFT.println("-------------------------");
    myTFT.println("-------2013-06-26--------");
    myTFT.println("-------------------------");
    myTFT.print("Rotation: ");
    myTFT.print(rotation);
    myTFT.println("--------------");
    myTFT.println("-------------------------");
    rotation++;
    if(rotation == 4){
      rotation = 0;
    }
  }
}

