/***************************************************************************		
 * Filename: xeSIMG.h
 ***************************************************************************
 * Description:
 *		hisome still image common defines.
 * Version:
 *		V_0.2	Jul-01-2010
 * Copyright:
 *		HISOME <www.hisome.com.>
 * Author:
 *		wuhm <wuhm@hisome.com.>
 * History:
 * 		Mar-30-2009 wuhm <wuhm@hisome.com>
 * 			V_0.1 Initial version of this code
 * 		Jul-01-2010 hanln <hanln@hisome.com>
 * 			V_0.2 Add XESIMG_RESOLUTION_1600x1200 and XESIMG_RESOLUTION_2560x1920
 *************************************************************************/

#ifndef __HISOME_XESIMG_H_
#define __HISOME_XESIMG_H_
#ifdef  CONFIG_USE_XEDEX2
	#include <xeDEX2.h>
#else
	#include <xeDEX.h>
#endif

#define XESIMG_FORMAT_YUV420_STR		"YUV420"
#define XESIMG_FORMAT_YUV420SP_STR		"YUV420SP"
#define XESIMG_FORMAT_YUV422SP_STR		"YUV422SP"
#define XESIMG_FORMAT_BMP24_STR			"BMP24"
#define XESIMG_FORMAT_RGB24_STR			"RGB24"
#define XESIMG_FORMAT_JPEG_STR			"JPEG"
#define XESIMG_FORMAT_JPEG2000_STR		"JPEG2000"
#define XESIMG_FORMAT_UNKNOWN_STR		"UNKNOWN"

enum xeSIMG_image_format
{
	XESIMG_FORMAT_YUV420=1,
	XESIMG_FORMAT_YUV420P=1,
	XESIMG_FORMAT_BMP24=2,
	XESIMG_FORMAT_RGB24=2,
	XESIMG_FORMAT_JPEG,
	XESIMG_FORMAT_JPEG2000,
	XESIMG_FORMAT_YUV420SP,
	XESIMG_FORMAT_YUV422SP,
	XESIMG_FORMAT_UNKNOWN,
	XESIMG_FORMAT_ANY,
	
};

#define XESIMG_RESOLUTION_D1_720x486_STR		"720x480"
#define XESIMG_RESOLUTION_D1_720x576_STR		"720x576"
#define XESIMG_RESOLUTION_HALF_D1_720x288_STR	"720x288"
#define XESIMG_RESOLUTION_SQCIF_128x96_STR		"128x96"
#define XESIMG_RESOLUTION_QCIF_176x144_STR		"176x144"
#define XESIMG_RESOLUTION_CIF_352x288_STR		"352x288"
#define XESIMG_RESOLUTION_2CIF_704x288_STR		"704x288"
#define XESIMG_RESOLUTION_4CIF_704x576_STR		"704x576"
#define XESIMG_RESOLUTION_16CIF_1408x1152_STR	"1408x1172"
#define XESIMG_RESOLUTION_4D1_1440x1152_STR		"1440x1152"
#define XESIMG_RESOLUTION_2D1_1440x576_STR		"1440x576"
#define XESIMG_RESOLUTION_1600x1200_STR			"1600x1200"
#define XESIMG_RESOLUTION_3744x1440_STR			"3744x1440"
#define XESIMG_RESOLUTION_3744x2880_STR			"3744x2880"
#define XESIMG_RESOLUTION_UNKNOWN_STR			"UNKNOWN"

enum xeSIMG_image_resolution
{
	XESIMG_RESOLUTION_USER=1,
	/**
	 * http://en.wikipedia.org/wiki/D1_(Sony)
	 * NTSC: 720*486
	 * PAL:720*576
	 **/
	XESIMG_RESOLUTION_D1_720x486,/*NTSC D1*/
	XESIMG_RESOLUTION_D1_720x576,/*PAL D1*/
	XESIMG_RESOLUTION_HALF_D1_720x288,/*PAL Half-D1*/
	
	/**
	 * http://en.wikipedia.org/wiki/Common_Intermediate_Format
	 **/
	XESIMG_RESOLUTION_SQCIF_128x96,
	XESIMG_RESOLUTION_QCIF_176x144,
	XESIMG_RESOLUTION_CIF_352x288,
	XESIMG_RESOLUTION_2CIF_704x288,
	XESIMG_RESOLUTION_4CIF_704x576,
	XESIMG_RESOLUTION_16CIF_1408x1152,
	
	XESIMG_RESOLUTION_4D1_1440x1152,/*4 PAL D1*/
	XESIMG_RESOLUTION_2D1_1440x576,/*2 PAL D1*/

	XESIMG_RESOLUTION_1600x1200,/*2.0 CCD*/
	XESIMG_RESOLUTION_3744x1440,/*5.0 CCD*/
	XESIMG_RESOLUTION_3744x2880,/*5.0 CCD*/

	XESIMG_RESOLUTION_UNKNOWN,
	XESIMG_RESOLUTION_ANY,
};

typedef struct xeSIMG_image
{
	enum xeSIMG_image_format fmt;
	enum xeSIMG_image_resolution res;
	
	/**
	 * if image_res == XESIMG_RESOLUTION_USER then
	 * 	ires_width and ires_height is MUST.
	 * ires_width must between [32,1920]
	 * ires_height must between [32,1080]
	 **/
	int ires_width;
	int ires_height;
	
	/**
	 * image data buffer pointer;
	 * image date length can be caculated by its format and resolution,
	 * but we still have here for checking only;
	 **/
	void *data_p;
	/**
	 * valid data length in data buffer;
	 **/
	int data_len;
	/**
	 * data buffer size;
	 **/
	int data_size;
    /*
       *point of struct xedex_stru
       */
    struct xedex_stru *xedex_p;
}xeSIMG_t;

#endif /*__HISOME_XESIMG_H_*/
