#ifndef _LCD_CONTROL_H
#define _LCD_CONTROL_H

#include "lcd.h"

typedef struct lcd_controller{
	char *name;
	void (*init)(P_lcd_params plcdparams);
	void (*enable)(void);
	void (*disable)(void);
}lcd_controller,*P_lcd_controller;

#endif
