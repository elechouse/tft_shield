#ifndef __PIN_MAGIC_H
#define __PIN_MAGIC_H


#define BB(addr, bit_num) (*(RwReg*)(0x42000000 + ((addr)-0x40000000)*32 + (bit_num)*4))



#if defined(__SAM3X8E__)
	#ifdef ELECFREAKS_TFT_SHIELD_V2
		#define RD_ACTIVE  //->PIO_SODR 
		#define RD_IDLE    //*rdPort |=  rdPinSet
		#define WR_ACTIVE  PIOC->PIO_CODR = PIO_PC7
		#define WR_IDLE    PIOC->PIO_SODR = PIO_PC7
		#define CD_COMMAND PIOC->PIO_CODR = PIO_PC6
		#define CD_DATA    PIOC->PIO_SODR = PIO_PC6
		#define CS_ACTIVE  PIOC->PIO_CODR = PIO_PC8
		#define CS_IDLE    PIOC->PIO_SODR = PIO_PC8
		#define RST_ACTIVE	PIOC->PIO_CODR = PIO_PC9
		#define RST_IDLE	PIOC->PIO_SODR = PIO_PC9
		
		#define WR_STROBE { WR_ACTIVE; WR_IDLE; }
		#define RD_STROBE { RD_ACTIVE, RD_IDLE;}
		
		#define write16(a)	{ DB0=(a);\
							DB1=(a>>1);\
							DB2=(a>>2);\
							DB3=(a>>3);\
							DB4=(a>>4);\
							DB5=(a>>5);\
							DB6=(a>>6);\
							DB7=(a>>7);\
							DB8=(a>>8);\
							DB9=(a>>9);\
							DB10=(a>>10);\
							DB11=(a>>11);\
							DB12=(a>>12);\
							DB13=(a>>13);\
							DB14=(a>>14);\
							DB15=(a>>15);\
							WR_STROBE;}
		
		/** PIO_ODSR output data status register*/
		/** 0x400E0E38 (PIOA), 
			0x400E1038 (PIOB), 
			0x400E1238 (PIOC), 
			0x400E1438 (PIOD), 
			0x400E1638 (PIOE),
			0x400E1838 (PIOF) */
		#define DB0			BB(0x400E1238, 5)		//PC5	37
		#define DB1			BB(0x400E1238, 4)		//PC4	36
		#define DB2			BB(0x400E1238, 3)		//PC3	35
		#define DB3			BB(0x400E1238, 2)		//PC2	34
		#define DB4			BB(0x400E1238, 1)		//PC1	33
		#define DB5			BB(0x400E1438, 10)		//PD10	32
		#define DB6			BB(0x400E0E38, 7)		//PA7	31
		#define DB7			BB(0x400E1438, 9)		//PD9	30
		#define DB8			BB(0x400E1038, 26)		//PB26	22
		#define DB9			BB(0x400E0E38, 14)		//PA14	23
		#define DB10		BB(0x400E0E38, 15)		//PA15	24
		#define DB11		BB(0x400E1438, 0)		//PD0	25
		#define DB12		BB(0x400E1438, 1)		//PD1	26
		#define DB13		BB(0x400E1438, 2)		//PD2	27
		#define DB14		BB(0x400E1438, 3)		//PD3	28
		#define DB15		BB(0x400E1438, 6)		//PD6	29
		
		/** 0x400E0EA0 (PIOA), 0x400E10A0 (PIOB), 
			0x400E12A0 (PIOC), 0x400E14A0 (PIOD), 
			0x400E16A0 (PIOE), 0x400E18A0 (PIOF) */
		#define DB0_WR_EN	BB(0x400E12A0, 5)		//PC5	37
		#define DB1_WR_EN	BB(0x400E12A0, 4)		//PC4	36
		#define DB2_WR_EN	BB(0x400E12A0, 3)		//PC3	35
		#define DB3_WR_EN	BB(0x400E12A0, 2)		//PC2	34
		#define DB4_WR_EN	BB(0x400E12A0, 1)		//PC1	33
		#define DB5_WR_EN	BB(0x400E14A0, 10)		//PD10	32
		#define DB6_WR_EN	BB(0x400E0EA0, 7)		//PA7	31
		#define DB7_WR_EN	BB(0x400E14A0, 9)		//PD9	30
		#define DB8_WR_EN	BB(0x400E10A0, 26)		//PB26	22
		#define DB9_WR_EN	BB(0x400E0EA0, 14)		//PA14	23
		#define DB10_WR_EN	BB(0x400E0EA0, 15)		//PA15	24
		#define DB11_WR_EN	BB(0x400E14A0, 0)		//PD0	25
		#define DB12_WR_EN	BB(0x400E14A0, 1)		//PD1	26
		#define DB13_WR_EN	BB(0x400E14A0, 2)		//PD2	27
		#define DB14_WR_EN	BB(0x400E14A0, 3)		//PD3	28
		#define DB15_WR_EN	BB(0x400E14A0, 6)		//PD6	29
		#define DB_WR_EN()			{DB0_WR_EN=1, DB1_WR_EN=1, DB2_WR_EN=1,DB3_WR_EN=1,\
									DB4_WR_EN=1, DB5_WR_EN=1, DB6_WR_EN=1,DB7_WR_EN=1,\
									DB8_WR_EN=1, DB9_WR_EN=1, DB10_WR_EN=1,DB11_WR_EN=1,\
									DB12_WR_EN=1, DB13_WR_EN=1, DB14_WR_EN=1,DB15_WR_EN=1;}
		
	#elif defined ELECHOUSE_DUE_TFT_SHIELD_V1
		
	#else
		#error "Unknown TFT Shield type."
	#endif

#else
	#error "Board type unsupported / not recognized"
#endif

#endif