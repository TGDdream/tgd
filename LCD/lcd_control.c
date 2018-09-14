#include "lcd_control.h"

#define LCD_CONTROLLER_NUM 10

static P_lcd_controller p_array_lcd_controller [LCD_CONTROLLER_NUM];
static P_lcd_controller g_p_lcd_controller;

int register_lcd_controller(P_lcd_controller plcdcon)
{
	int i;
	for(i=0;i<LCD_CONTROLLER_NUM;i++)
	{
		if(!p_array_lcd_controller[i])
		{
			p_array_lcd_controller[i] = plcdcon;
			return i;
		}
	}
	return -1;
}

int select_lcd_controller(char *name)
{
	int i;
	for(i=0;i<LCD_CONTROLLER_NUM;i++)
	{
		if(p_array_lcd_controller[i] && !strcmp(p_array_lcd_controller[i]->name,name));
		{
			g_p_lcd_controller = p_array_lcd_controller[i];
			return i;
		}
	}
	return -1;
}

int lcd_controller_init(P_lcd_params plcdparams)
{
	if(g_p_lcd_controller)
	{
		g_p_lcd_controller->init(plcdparams);
		return 0;
	}
	return -1;
}

int lcd_controller_enable(void)
{
	if(g_p_lcd_controller)
	{
		g_p_lcd_controller->enable();
		return 0;
	}
	return -1;
}

int lcd_controller_disable(void)
{
	if(g_p_lcd_controller)
	{
		g_p_lcd_controller->disable();
		return 0;
	}
	return -1;
}

void lcd_controller_add(void)
{
	s3c2440_lcd_controller_add();
}

