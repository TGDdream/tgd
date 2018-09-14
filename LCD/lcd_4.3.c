#include "lcd.h"

#define LCD_FB_BASE 0x33c00000

lcd_params lcd_4_3_params = {
	.name = "lcd_4_3",
	.pins_pol = {
		.de = NORMAL,
		.pwren = NORMAL,
		.vclk = NORMAL,
		.rgb = NORMAL,
		.hsync = INVERT,
		.vsync = INVERT,
	},
	.time_seq = {
		.tvp = 10,
		.tvb = 2,
		.tvf = 2,
		.thp = 41,
		.thb = 2,
		.thf = 2,
		.vclk = 9,
	},
	.xres = 480,
	.yres = 272,
	.bpp = 16,
	.fb_base = LCD_FB_BASE,
};

void lcd_4_3_add(void)
{
	register_lcd(&lcd_4_3_params);
}
