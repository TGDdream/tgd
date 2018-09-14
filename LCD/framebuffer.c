#include "lcd.h"

static unsigned int fb_base;
static int xres,yres,bpp;

void fb_get_lcd_params(void)
{
	get_lcd_params(&fb_base, &xres, &yres, &bpp);
}

unsigned short convert32bppto16bpp(unsigned int rgb)
{
	int r = (rgb>>16)&0xff;
	int g = (rgb>>8)&0xff;
	int b = rgb&0xff;

	/* rgb565 */
	r = r>>3;
	g = g>>2;
	b = b>>3;

	return ((r<<11) | (g<<5) | (b));
}

void fb_put_pixel(int x,int y,unsigned int color)
{
	unsigned char *p_char;/* 8bpp */
	unsigned short *p_word;/* 16bpp */
	unsigned int *p_doubleword;/* 32bpp */

	unsigned int pixel_base = fb_base+(xres*bpp/8)*y+x*bpp/8;

	switch(bpp)
	{
		case 8:
			p_char = (unsigned char *)pixel_base;
			*p_char = color;
			break;
		case 16:
			p_word = (unsigned short *)pixel_base;
			*p_word = convert32bppto16bpp(color);
			break;
		case 32:
			p_doubleword = (unsigned int *)pixel_base;
			*p_doubleword = color;
			break;
	}
}

