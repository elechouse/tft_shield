/**
  @file    tft_hx8352_touch.ino
  @author  www.elechouse.com
  @brief   example of ELECHOUSE TFTShield.
  
  
    For this demo, write random color to the TFT LCD with touch screen.
  
  @section  HISTORY
  
  V1.0 initial version
  
    Copyright (c) 2013 www.elechouse.com  All right reserved.
*/

#include <ads7843.h>
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

/** ADS7843 pin map */
#ifdef ELECFREAKS_TFT_SHIELD_V2
#define DCLK     6
#define CS       5  
#define DIN      4 
#define DOUT     3
#define IRQ      2 
#elif defined ELECHOUSE_DUE_TFT_SHIELD_V1
/** elechouse TFT shield pin map */
#define DCLK     25
#define CS       26 
#define DIN      27 
#define DOUT     29
#define IRQ      30
#endif

/** global variable */
ADS7843 touch(CS, DCLK, DIN, DOUT, IRQ);
TFTLCD myTFT;
Point p;
uint16_t color[]={
  BLUE, RED, GREEN, CYAN, MAGENTA, YELLOW, WHITE
};


void setup(void)
{
  Serial.begin(115200);
  
  /** ADS7843 initial */
  touch.begin();
    
  myTFT.begin();
  myTFT.fillScreen(BLACK);
  
  myTFT.setTextColor(WHITE, BLUE);
  myTFT.println("Elechouse TFT shield Demo");
  myTFT.println("-------------------------");
  myTFT.println("-------2013-3-18---------");
  myTFT.println("-------------------------");
  myTFT.drawCircle(50,50,10,0x51F);
}

void loop(void)
{
  uint8_t flag;
  int lx, ly;
  
  /** get random number */   
  int pacy=random(0, 7);  

  p=touch.getpos(&flag) ;

  while(flag){
    /** send position through serial */
    Serial.print(p.x, DEC);
    Serial.print("   ");
    Serial.print(p.y, DEC);
    Serial.println();
    
    /** write to TFT LCD */
    lx=(p.x- 310)/14;
    ly=(p.y- 150)/9;
    myTFT.setAddrWindow(lx,ly,lx+2,ly+2);
    myTFT.flood(color[pacy], 9);
    
    /** get next position */
    p=touch.getpos(&flag) ;
  }
  
}
