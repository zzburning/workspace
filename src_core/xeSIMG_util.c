#include <string.h>
#include <xeSIMG_util.h>

enum xeSIMG_image_format __simg_format_str_2_int(const char *str)
{
	if(!strcmp(str,XESIMG_FORMAT_YUV420SP_STR))
	{
		return XESIMG_FORMAT_YUV420SP;
	}
	else if(!strcmp(str,XESIMG_FORMAT_YUV422SP_STR))
	{
		return XESIMG_FORMAT_YUV422SP;
	}
	else if(!strcmp(str,XESIMG_FORMAT_YUV420_STR))
	{
		return XESIMG_FORMAT_YUV420;
	}
	else if(!strcmp(str,XESIMG_FORMAT_BMP24_STR) || !strcmp(str,XESIMG_FORMAT_RGB24_STR))
	{
		return XESIMG_FORMAT_BMP24;
	}
	else if(!strcmp(str,XESIMG_FORMAT_JPEG_STR))
	{
		return XESIMG_FORMAT_JPEG;
	}
	else if(!strcmp(str,XESIMG_FORMAT_JPEG2000_STR))
	{
		return XESIMG_FORMAT_JPEG2000;
	}
	
	return XESIMG_FORMAT_UNKNOWN;
}
const char* __simg_format_int_2_str(enum xeSIMG_image_format fmt)
{
	switch(fmt)
	{
	case XESIMG_FORMAT_YUV420SP:
		return XESIMG_FORMAT_YUV420SP_STR;
    case XESIMG_FORMAT_YUV422SP:
		return XESIMG_FORMAT_YUV422SP_STR;
	case XESIMG_FORMAT_YUV420:
		return XESIMG_FORMAT_YUV420_STR;
	case XESIMG_FORMAT_BMP24:
		return XESIMG_FORMAT_BMP24_STR;
	case XESIMG_FORMAT_JPEG:
		return XESIMG_FORMAT_JPEG_STR;
	case XESIMG_FORMAT_JPEG2000:
		return XESIMG_FORMAT_JPEG2000_STR;
	default:
		return XESIMG_FORMAT_UNKNOWN_STR;
	}
}
enum xeSIMG_image_resolution __simg_resolution_str_2_int(const char *str)
{
	if(!strcmp(XESIMG_RESOLUTION_D1_720x486_STR,str))
	{
		return XESIMG_RESOLUTION_D1_720x486;
	}
	else if(!strcmp(XESIMG_RESOLUTION_D1_720x576_STR,str))
	{
		return XESIMG_RESOLUTION_D1_720x576;
	}
	else if(!strcmp(XESIMG_RESOLUTION_HALF_D1_720x288_STR,str))
	{
		return XESIMG_RESOLUTION_HALF_D1_720x288;
	}
	else if(!strcmp(XESIMG_RESOLUTION_SQCIF_128x96_STR,str))
	{
		return XESIMG_RESOLUTION_SQCIF_128x96;
	}
	else if(!strcmp(XESIMG_RESOLUTION_QCIF_176x144_STR,str))
	{
		return XESIMG_RESOLUTION_QCIF_176x144;
	}
	else if(!strcmp(XESIMG_RESOLUTION_CIF_352x288_STR,str) )
	{
		return XESIMG_RESOLUTION_CIF_352x288;
	}
	else if(!strcmp(XESIMG_RESOLUTION_2CIF_704x288_STR,str))
	{
		return XESIMG_RESOLUTION_2CIF_704x288;
	}
	else if(!strcmp(XESIMG_RESOLUTION_4CIF_704x576_STR,str))
	{
		return XESIMG_RESOLUTION_4CIF_704x576;
	}
	else if(!strcmp(XESIMG_RESOLUTION_16CIF_1408x1152_STR,str))
	{
		return XESIMG_RESOLUTION_16CIF_1408x1152;
	}
	else if(!strcmp(XESIMG_RESOLUTION_4D1_1440x1152_STR,str))
	{
		return XESIMG_RESOLUTION_4D1_1440x1152;
	}
	else if(!strcmp(XESIMG_RESOLUTION_2D1_1440x576_STR,str))
	{
		return XESIMG_RESOLUTION_2D1_1440x576;
	}
	else if(!strcmp(XESIMG_RESOLUTION_1600x1200_STR,str))
	{
		return XESIMG_RESOLUTION_1600x1200;
	}
	else if(!strcmp(XESIMG_RESOLUTION_3744x1440_STR,str))
	{
		return XESIMG_RESOLUTION_3744x1440;
	}
	else if(!strcmp(XESIMG_RESOLUTION_3744x2880_STR,str))
	{
		return XESIMG_RESOLUTION_3744x2880;
	}
    
	return XESIMG_RESOLUTION_UNKNOWN;
}
const char* __simg_resolution_int_2_str(enum xeSIMG_image_resolution res)
{
	switch(res)
	{
	case XESIMG_RESOLUTION_D1_720x486:
		return XESIMG_RESOLUTION_D1_720x486_STR;
	case XESIMG_RESOLUTION_D1_720x576:
		return XESIMG_RESOLUTION_D1_720x576_STR;
	case XESIMG_RESOLUTION_HALF_D1_720x288:
		return XESIMG_RESOLUTION_HALF_D1_720x288_STR;
	case XESIMG_RESOLUTION_SQCIF_128x96:
		return XESIMG_RESOLUTION_SQCIF_128x96_STR;
	case XESIMG_RESOLUTION_QCIF_176x144:
		return XESIMG_RESOLUTION_QCIF_176x144_STR;
	case XESIMG_RESOLUTION_CIF_352x288:
		return XESIMG_RESOLUTION_CIF_352x288_STR;
	case XESIMG_RESOLUTION_2CIF_704x288:
		return XESIMG_RESOLUTION_2CIF_704x288_STR;
	case XESIMG_RESOLUTION_4CIF_704x576:
		return XESIMG_RESOLUTION_4CIF_704x576_STR;
	case XESIMG_RESOLUTION_16CIF_1408x1152:
		return XESIMG_RESOLUTION_16CIF_1408x1152_STR;
	case XESIMG_RESOLUTION_4D1_1440x1152:
		return XESIMG_RESOLUTION_4D1_1440x1152_STR;
	case XESIMG_RESOLUTION_2D1_1440x576:
		return XESIMG_RESOLUTION_2D1_1440x576_STR;
	case XESIMG_RESOLUTION_1600x1200:
		return XESIMG_RESOLUTION_1600x1200_STR;
    case XESIMG_RESOLUTION_3744x1440:
		return XESIMG_RESOLUTION_3744x1440_STR;
	case XESIMG_RESOLUTION_3744x2880:
		return XESIMG_RESOLUTION_3744x2880_STR;
	default:
		return XESIMG_RESOLUTION_UNKNOWN_STR;
	}
}

int get_img_width(enum xeSIMG_image_resolution res)
{
	int width=0;
	switch(res)
	{
		case XESIMG_RESOLUTION_D1_720x576:
			width=720;
			break;
		case XESIMG_RESOLUTION_4D1_1440x1152:
			width=1440;
			break;
		case XESIMG_RESOLUTION_2D1_1440x576:
			width=1440;
		default:
			break;
	}
	return width;
}

int get_img_height(enum xeSIMG_image_resolution res)
{
	int height=0;
	switch(res)
	{
		case XESIMG_RESOLUTION_D1_720x576:
			height=576;
			break;
		case XESIMG_RESOLUTION_4D1_1440x1152:
			height=1152;
			break;
		case XESIMG_RESOLUTION_2D1_1440x576:
			height=576;
		default:
			break;
	}
	return height;
}

