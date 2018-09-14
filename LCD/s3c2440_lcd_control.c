#include "lcd_control.h"
#include "lcd.h"
#include "s3c2440_soc.h"

#define HCLK 100

void jz2440_pins_init()
{
	GPBCON &= ~0x3;
	GPBCON |= 0x01;
	GPCCON = 0xaaaaaaaa;
	GPDCON = 0xaaaaaaaa;
	GPGCON |= (3<<8);
}

void s3c2440_lcd_controller_init(P_lcd_params plcdparams)
{
	int pixeplace;
	unsigned int addr;
	
	jz2440_pins_init();

	//int clkval = (double)HCLK/plcdparams->time_seq.vclk/2-1+0.5;
	int clkval = 5;
	int bppmode = plcdparams->bpp == 8?0xb:\
		plcdparams->bpp == 16?0xc:\
		0xd;/* 0xd: 24,32bpp */
	LCDCON1 = (clkval<<8) | (3<<5) |(bppmode<<1);
	LCDCON2 = ((plcdparams->time_seq.tvb-1)<<24) | \
			  ((plcdparams->yres-1)<<14)         | \
			  ((plcdparams->time_seq.tvf-1)<<6)  | \
			  ((plcdparams->time_seq.tvp-1)<<0);
	
	LCDCON3 = ((plcdparams->time_seq.thb-1)<<19) | \
			  ((plcdparams->xres-1)<<8)          | \
			  ((plcdparams->time_seq.thf-1)<<0);

	LCDCON4 = ((plcdparams->time_seq.thp-1)<<0);

	pixeplace = plcdparams->bpp == 32 ? (0) : plcdparams->bpp == 16 ? (1) : (1<<1);

	LCDCON5 = (plcdparams->pins_pol.vclk<<10) |\
			  (plcdparams->pins_pol.rgb<<7)   |\
			  (plcdparams->pins_pol.hsync<<9) |\
			  (plcdparams->pins_pol.vsync<<8) |\
			  (plcdparams->pins_pol.de<<6)    |\
			  (plcdparams->pins_pol.pwren<<5) |\
			  (1<<11) | pixeplace;

	addr = plcdparams->fb_base&~(1<<31);
	LCDSADDR1 = (addr>>1);
	addr = plcdparams->fb_base + plcdparams->xres*plcdparams->yres*plcdparams->bpp/8;
	addr >>=1;
	addr &= 0x1fffff;
	LCDSADDR2 = addr;
}

void s3c2440_lcd_controller_enable(void)
{
	GPBDAT |= (1<<0);
	LCDCON5 |= (1<<3);
	LCDCON1 |= (1<<0);
}

void s3c2440_lcd_controller_disable(void)
{
	GPBDAT &= ~(1<<0);
	LCDCON5 &= ~(1<<3);
	LCDCON1 &= ~(1<<0);
}

lcd_controller s3c2440_lcd_controller = {
	.name = "s3c2440",
	.init = s3c2440_lcd_controller_init,
	.enable = s3c2440_lcd_controller_enable,
	.disable = s3c2440_lcd_controller_disable,
};

void s3c2440_lcd_controller_add(void)
{
	register_lcd_controller(&s3c2440_lcd_controller);
}

