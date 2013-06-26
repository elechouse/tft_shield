/**
  @file    tft_hx8352_sd.ino
  @author  www.elechouse.com
  @brief   example of ELECHOUSE TFTShield.
  
  
    For this demo, just read bmp files(only support for 16bits pic) from SD card 
    and paint it to TFT LCD. Send '0', '1', '2' '3' to change picture.
  
  @section  HISTORY
  
  V1.0 initial version
  
    Copyright (c) 2013 www.elechouse.com  All right reserved.
*/
#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <tftlib.h>          // Hardware-specific librar

/** specify the name of the bmp file */
#define PIC_BMP0             "star0.bmp"
#define PIC_BMP1             "star1.bmp"
#define PIC_BMP2             "star2.bmp"
#define PIC_BMP3             "star3.bmp"

File bmp;                    // bmp file
int sd_cs = 42;              // TFTShield sd card chip select pin is Arduino digital pin 42
TFTLCD myTFT;                // TFT class

void setup(void)
{
  Serial.begin(115200);
  
  /** SD card initial */
  if (!SD.begin(sd_cs)) {
    Serial.println("SD initialization failed!");
    while(1);  // trap here
  }
  
  /** TFT initial */
  myTFT.begin();
  myTFT.fillScreen(0x001F);
  
  /** try to paint picture0 */
  bmp = SD.open(PIC_BMP2);
  drawPic(&bmp, 0, 0);
  bmp.close();
  
  Serial.println();
}

void loop(void)
{
  if(Serial.available()){
    switch(Serial.read()){
      case '0':
        Serial.print("Cmd: 0\t");
        bmp = SD.open(PIC_BMP0);
        drawPic(&bmp, 0, 0);
        bmp.close();
        Serial.print("\tFile: ");
        Serial.println(PIC_BMP0);
        break;
      case '1':
        Serial.print("Cmd: 1\t");
        bmp = SD.open(PIC_BMP1);
        drawPic(&bmp, 0, 0);
        bmp.close();
        Serial.print("\tFile: ");
        Serial.println(PIC_BMP1);
        break;
      case '2':
        Serial.print("Cmd: 2\t");
        bmp = SD.open(PIC_BMP2);
        drawPic(&bmp, 20, 20);
        bmp.close();
        Serial.print("\tFile: ");
        Serial.println(PIC_BMP2);
        break;
      case '3':
        Serial.print("Cmd: 3\t");
        bmp = SD.open(PIC_BMP3);
        drawPic(&bmp, 0, 0);
        bmp.close();
        Serial.print("\tFile: ");
        Serial.println(PIC_BMP3);
        break;
    }
  }

}

/*****************************************************************************/
/*!
    	@brief  draw pic to the specified area
      	@param  bmp - pointer to the picture file
    	@param  x, y - coordinate of starting position
    	@return NONE
*/
/*****************************************************************************/
void drawPic(File *bmp, uint16_t x, uint16_t y)
{
  uint8_t header[14 + 124]; // maximum length of bmp file header
  uint16_t color[240];     
  uint8_t color_l, color_h, color_tmp_l, color_tmp_h;
  uint32_t i,j,k;
    uint32_t width;
  uint32_t height;
  uint16_t bits;
  uint32_t compression;
  uint32_t alpha_mask = 0;
  uint32_t pic_offset, dib_size;
  
  /** read header of the bmp file */
  i=0;
  while (bmp->available()) {
    header[i] = bmp->read();
    i++;
    if(i==14){
      break;
    }
  }
  
  /** compare signature */
  if(header[0] != 'B' || header[1] != 'M'){
    Serial.println("Not a bmp picture");
    return;
  }
  
  pic_offset = (((uint32_t)header[0x0A+3])<<24) + (((uint32_t)header[0x0A+2])<<16) + (((uint32_t)header[0x0A+1])<<8)+(uint32_t)header[0x0A];
  while (bmp->available()) {
    header[i] = bmp->read();
    i++;
    if(i==pic_offset){
      break;
    }
  }
//  Serial.print("Offset: ");
//  Serial.println(i, DEC);
//  Serial.write(header, pic_offset);
  
  /** calculate picture width ,length and bit numbers of color */
  width = (((uint32_t)header[0x12+3])<<24) + (((uint32_t)header[0x12+2])<<16) + (((uint32_t)header[0x12+1])<<8)+(uint32_t)header[0x12];
  height = (((uint32_t)header[0x16+3])<<24) + (((uint32_t)header[0x16+2])<<16) + (((uint32_t)header[0x16+1])<<8)+(uint32_t)header[0x16];
  compression = (((uint32_t)header[0x1E + 3])<<24) + (((uint32_t)header[0x1E + 2])<<16) + (((uint32_t)header[0x1E + 1])<<8)+(uint32_t)header[0x1E];
  bits = (((uint16_t)header[0x1C+1])<<8) + (uint16_t)header[0x1C];
  if(pic_offset>0x42){
    alpha_mask = (((uint32_t)header[0x42 + 3])<<24) + (((uint32_t)header[0x42 + 2])<<16) + (((uint32_t)header[0x42 + 1])<<8)+(uint32_t)header[0x42];
  }
  
  /** print picture info */
  Serial.print("Width: ");
  Serial.print(width, DEC);
  Serial.print(",\tHeight: ");
  Serial.print(height, DEC);
  Serial.print(",\tColor: ");
  Serial.print(bits, DEC);
  Serial.print("Bits,\t");
  
  if(width>240 || height > 400){
    Serial.println("File size out of range.");
    return;
  }else if( (width+x)>240 || (height+y) > 400 ){
    Serial.println("File size out of range because of the start coordinate.");
  }
  
  switch(bits){
    case 16:
      /** set position to pixel table */
      bmp->seek(pic_offset);
      
      /** check picture format */
      if(pic_offset == 70 && alpha_mask == 0){
        /** 565 format */
        Serial.print("Format: 565");
        
        /** write from bottom left to top right, through bottom right */
        myTFT.setRotation(0);
        
        /** set work area */
//        myTFT.setAddrWindow(x, y, x+width-1, y+height-1);
        
        /** read from SD card, write to TFT LCD */
        for(j=height; j>0; j--){
          for(k=0;k<width; k++){
            color_l = bmp->read();
            color_h = bmp->read();
            color[k]=0;
            color[k] += color_h;
            color[k] <<= 8;
            color[k] += color_l;
          }
          myTFT.setAddrWindow(x+0, y+j-1, x+width-1, y+j-1);
          myTFT.pushColors(color, width, true);
          
          /** dummy read twice to align for 4 */
          if(width%2){
            bmp->read();bmp->read();
          }
        }
      }else{
        /** 555 format */
        Serial.print("Format: 555");
        
        /** write from bottom left to top right, through bottom right */
        myTFT.setRotation(0);
        
        /** write from bottom left to top right, through bottom right */
//        myTFT.setAddrWindow(x, y, x+width-1, y+height-1);
        
        /** read from SD card, write to TFT LCD */
        for(j=height; j>0; j--){
          for(k=0; k<width;k++){
            color_l = bmp->read();
            color_h = bmp->read();
            color_tmp_h = color_h<<1;
            color_tmp_h |= color_l>>7;
            color_tmp_l = color_l << 1;
            color_tmp_l &= 0xc0;
            color_tmp_l |= (color_l&0x1F);
            
            if(color_l&0x20){
              color_tmp_l += 0x20;
            }
            
            color[k]=0;
            color[k] += color_h;
            color[k] <<= 9;
            color[k] += color_l;
          }
          myTFT.setAddrWindow(x+0, y+j-1, x+width-1, y+j-1);
          myTFT.pushColors(color, width, true);
          
          /** dummy read to align for 4 */
          if(width%2){
            bmp->read();bmp->read();
          }
        }
      }
      break;
    case 24:
    case 32:
    default:
      Serial.print("Unknown file format, support bmp 16bits");
      break;
  }
  
}
