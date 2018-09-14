#include "geometry.h"
#include "font.h"

void lcd_test(void)
{
	unsigned int fb_base;
	int xres,yres,bpp;
	int x,y;
	unsigned short *p;
	unsigned int *p2;

	lcd_init();
	lcd_enable();

	get_lcd_params(&fb_base, &xres, &yres, &bpp);

	if(bpp==16)
	{
		p = (unsigned short *)fb_base;
		for(y=0;y<yres;y++)
			for(x=0;x<xres;x++)
				*p++ = 0xf800;
		p = (unsigned short *)fb_base;
		for(y=0;y<yres;y++)
			for(x=0;x<xres;x++)
				*p++ = 0x7e0;
		p = (unsigned short *)fb_base;	
		for(y=0;y<yres;y++)
			for(x=0;x<xres;x++)
				*p++ = 0xffff;
	}
	else if(bpp==32)
	{
		p2 = (unsigned int *)fb_base;
		for(y=0;y<yres;y++)
			for(x=0;x<xres;x++)
				*p2++ = 0xff0000;
			
		p2 = (unsigned int *)fb_base;
		for(y=0;y<yres;y++)
			for(x=0;x<xres;x++)
				*p2++ = 0x00ff00;
			
		p2 = (unsigned int *)fb_base;
		for(y=0;y<yres;y++)
			for(x=0;x<xres;x++)
				*p2++ = 0xffffff;
	}
	
	delay(100000);
/*
	draw_line(0, 0, xres-1, yres-1, 0xffacffcc);
	draw_line(xres-1, 0, 0, yres-1, 0xff48ffcc);
	draw_line(xres/2, 0, xres/2, yres-1, 0xffac00cc);
	draw_line(0, yres/2, xres-1, yres/2, 0xff11ff11);
	draw_line(0, 0, 0, yres-1, 0xffac1010);
	draw_line(0, 0, xres-1, 0, 0xffac0000);
	draw_line(0,yres-1, xres-1, yres-1, 0xff00ffcc);
	draw_line(xres-1, 0, xres-1, yres-1, 0xff00ff00);
*/
	delay(100000);

//	draw_circle(xres/2, yres/2, yres/2, 0xff857407);

//	fb_print_char(180, 100, 'A', 0xf800);

	fb_print_string(10, 10, 0xff0000, "Henry,32,sat there as the train of time passed the Emirates Stadium, gazing affectionately at his 22-year-old shadow.The increasingly distant ruts silently took away the noise of the four cities,but guided the people along the way to pursue the passing time, when Henry, 37,was there in tears, looking at him with deep affection. Trying to get back to the origin,the starting platform, remember the 17-year-old when I picked up my bag.\n\r**************************************************");
}
