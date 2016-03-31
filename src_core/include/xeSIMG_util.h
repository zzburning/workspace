#ifndef __HISOME_XESIMG_UTIL_H_
#define __HISOME_XESIMG_UTIL_H_
#include <xeSIMG.h>

enum xeSIMG_image_format __simg_format_str_2_int(const char *str);
const char* __simg_format_int_2_str(enum xeSIMG_image_format fmt);
enum xeSIMG_image_resolution __simg_resolution_str_2_int(const char *str);
const char* __simg_resolution_int_2_str(enum xeSIMG_image_resolution res);
extern int get_img_width(enum xeSIMG_image_resolution res);
extern int get_img_height(enum xeSIMG_image_resolution res);


#endif /*__HISOME_XESIMG_UTIL_H_*/
