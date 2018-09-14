#include "lcd.h"
#include "lcd_control.h"

#define LCD_NUM 10

static P_lcd_params p_array_lcd[LCD_NUM];
static P_lcd_params p_lcd_select;

int register_lcd(P_lcd_params plcd)
{
	int i;
	for(i=0;i<LCD_NUM;i++)
	{
		if(!p_array_lcd[i])
		{
			p_array_lcd[i] = plcd;
			return i;
		}
	}
	return -1;
}


int select_lcd(char *name)
{
	int i;
	for(i=0;i<LCD_NUM;i++)
	{
		if(p_array_lcd[i] && !strcmp(p_array_lcd[i]->name, name))
		{
			p_lcd_select = p_array_lcd[i];
			return i;
		}		
	}
	return -1;
}

void get_lcd_params(unsigned int *fb_base,int *xres,int *yres,int *bpp)
{
	*fb_base = p_lcd_select->fb_base;
	*xres = p_lcd_select->xres;
	*yres = p_lcd_select->yres;
	*bpp = p_lcd_select->bpp;
}

void lcd_enable(void)
{
	if(p_lcd_select)
	{
		lcd_controller_enable();
	}
}

void lcd_disable(void)
{
	if(p_lcd_select)
		{
			lcd_controller_disable();
		}
}

void lcd_init(void)
{
	/* 注册LCD */
	lcd_4_3_add();

	/* 注册LCD控制器 */
	lcd_controller_add();

	/* 选择一个LCD */
	select_lcd("lcd_4_3");

	/* 选择LCD控制器 */
	select_lcd_controller("s3c2440");

	/* 使用LCD的参数，初始化LCD控制器 */
	lcd_controller_init(p_lcd_select);

	fb_get_lcd_params();

	font_get_lcd_params();
}


