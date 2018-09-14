#ifndef _LCD_H
#define _LCD_H

enum{
	NORMAL = 0,
	INVERT = 1,
};

typedef struct pins_polarity{
	int de;
	int vsync;
	int hsync;
	int rgb;
	int vclk;
	int pwren;
}pins_polarity,*p_pins_polarity;

typedef struct time_sequence{
	int tvp;
	int tvb;
	int tvf;
	int thp;
	int thb;
	int thf;
	int vclk;
}time_sequence,*p_time_sequence;

typedef struct lcd_params{
	char *name;
	pins_polarity pins_pol;
	time_sequence time_seq;
	int xres;
	int yres;
	int bpp;
	unsigned int fb_base;
}lcd_params,*P_lcd_params;

#endif
