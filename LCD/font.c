#include "video_font.h"

extern const unsigned char video_fontdata[VIDEO_FONT_SIZE];
static unsigned int fb_base;
static int xres,yres,bpp;

void font_get_lcd_params(void)
{
	get_lcd_params(&fb_base, &xres, &yres, &bpp);
}

/* 打印一个字符 */
void fb_print_char(int x,int y,char c,unsigned int color)
{
	int i,j;
	/* 得到字符在数组中的数据 */
	const unsigned char *cot = &video_fontdata[c*16];

	for(i=0;i<VIDEO_FONT_HEIGHT;i++)
	{
		for(j=0;j<VIDEO_FONT_WIDTH;j++)
		{
			if((*cot>>(VIDEO_FONT_WIDTH-j-1))&0x01)
			{
				fb_put_pixel(x+j, y+i, color);
			}
		}
		cot++;
	}
}

/* 打印字符串 */
void fb_print_string(int x,int y,unsigned int color ,char *str)
{
	int i;
	while(*str != '\0')
	{
		if(*str == '\n')
			y += 16;
		else if(*str == '\r')
			x = 10;
		else
			fb_print_char(x, y, *str, color);
		str++;
		if(x>=(xres-20))
		{
			x = 10;
			y += 16;
		}
		else 
			x += 8;	
	}
}

