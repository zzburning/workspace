/*
 * xeDEX.h
 * 2010-12-29	wuhm<wuhm@hisome.com>
 * 	Add: XEDEX_CATEGORY_DATA
 *
 * 2010-8-22 wangchunhuan <wangch@hisome.com>
 *	Add: image support
 *
 * 2010-8-16 wangchunhuan <wangch@hisome.com>
 *	Add: audio frame support
 *	Add: video lost support
 *	Add: data source channel index support
 *
 *  Created on: 2010-8-11
 *      Author: enigma
 *
 * lib2lib,module2module data exchange structure;
 */

#ifndef __XEDEX_H_
#define __XEDEX_H_

#include <sys/time.h>
#include <pthread.h>
/*###################################################################################*
 # Life of xedex_t:
 #  A. HDTI64E0
 #	I	libhxDavinci -> libxeSOE -> libxeSAP(buffer) -> xefd_free_f();
 #							|
 #							-> deliver to TCP/UDP/RTP consumers;
 #	II	libhxDavinci -> libxeSIS -> libxeSAP -> xefd_free_f();
 #							|
 #							-> xefd_free_f();
 #	III	libxeSAP -> ${NETWORK} -> xefd_free_f();
 #
 #-----------------------------------------------------------------------------------
 #
 #	B. HDTI64E1
 #	I	libhxDavinci -> libxeSOE -> libxeSAP(buffer) -> xefd_free_f();
 #							|
 #							-> deliver to TCP/UDP/RTP consumers;
 #	II	libhxDavinci -> libxeSIS_F -> xefd_free_f();
 #
 #------------------------------------------------------------------------------------
 #
 #	C. HDTI64D1
 #	I	${NETWORK} -> libxeSUCK -> libhxDavinci -> xefd_free_f();
 #
 #------------------------------------------------------------------------------------
 #
 #	D. HDMA61CP
 #	I	${NETWORK}	-> libxeSOE	-> libxeSAP(buffer)	-> xefd_free_f();
 #							|
 #							-> deliver to TCP/UDP/RTP consumers;
 #	II	libxeSAP -> ${NETWORK} -> xefd_free_f();
 #	III	${NETWORK}	-> libxeSUCK -> ${NETWORK}	-> xefd_free_f();
 #
 ####################################################################################*/

struct xedex_stru;
typedef struct xedex_stru xedex_t;

typedef void (*xedex_free_f)(xedex_t *dex);

enum XEDEX_FRAME_TYPE
{
	XEDEX_FRAME_TYPE_PS_I_FRAME = (1<<0),
	XEDEX_FRAME_TYPE_PS_P_FRAME = (1<<1),
	XEDEX_FRAME_TYPE_PS_B_FRAME = (1<<2),
	XEDEX_FRAME_TYPE_PS_A_FRAME = (1<<3),

	XEDEX_FRAME_TYPE_MJPEG	= (1<<4),

	XEDEX_FRAME_TYPE_SIMG_YUV420	= (1<<16),
	XEDEX_FRAME_TYPE_SIMG_JPEG	= (1<<17),
};

enum XEDEX_FRAME_RESOLUTION
{
	XEDEX_FRAME_RESOLUTION_UNKNOWN = 0,

	XEDEX_FRAME_RESOLUTION_USER=1,
	/**
	 * http://en.wikipedia.org/wiki/D1_(Sony)
	 * NTSC: 720*486
	 * PAL:720*576
	 **/
	XEDEX_FRAME_RESOLUTION_D1_720x486,/*NTSC D1*/
	XEDEX_FRAME_RESOLUTION_D1_720x576,/*PAL D1*/	
	XEDEX_FRAME_RESOLUTION_HALF_D1_720x288,/*PAL Half-D1*/

	/**
	 * http://en.wikipedia.org/wiki/Common_Intermediate_Format
	 **/
	XEDEX_FRAME_RESOLUTION_SQCIF_128x96,
	XEDEX_FRAME_RESOLUTION_QCIF_176x144,
	XEDEX_FRAME_RESOLUTION_CIF_352x288,
	XEDEX_FRAME_RESOLUTION_2CIF_704x288,
	XEDEX_FRAME_RESOLUTION_4CIF_704x576,
	XEDEX_FRAME_RESOLUTION_D1_704x576 = XEDEX_FRAME_RESOLUTION_4CIF_704x576,/*-------------add by huhg*/
	XEDEX_FRAME_RESOLUTION_16CIF_1408x1152,

	XEDEX_FRAME_RESOLUTION_4D1_1440x1152,/*4 PAL D1*/
	XEDEX_FRAME_RESOLUTION_2D1_1440x576,/*2 PAL D1*/       

	XEDEX_FRAME_RESOLUTION_1600x1200,/*SONY/Kodak 200W CCD*/
	XEDEX_FRAME_RESOLUTION_SONY_200W_CCD = XEDEX_FRAME_RESOLUTION_1600x1200,
	XEDEX_FRAME_RESOLUTION_KODAK_200W_CCD = XEDEX_FRAME_RESOLUTION_1600x1200,

	XEDEX_FRAME_RESOLUTION_3648x1380,/*Kodak 1000W CCD, half horizon, or just called Kodak 500W CCD*/
	XEDEX_FRAME_RESOLUTION_KODAK_500W_CCD = XEDEX_FRAME_RESOLUTION_3648x1380,
	
	XEDEX_FRAME_RESOLUTION_720P_1280x760,/*-------------add by huhg*/ 
	    
};

/**
 * Apr-6-2011 added by wuhm<wuhm@hisome.com>
 * 	V: Video Sequence
 * 	S: Still Image
 * 	A: Audio bitrate
 * Generator MUST set codec correctly;
 */
enum XEDEX_VSA_CODEC
{
	XEDEX_VSA_CODEC_UNKNOWN=0,

	/*V: bit0~bit7*/
	XEDEX_VSA_CODEC_H264	= (1UL<<0),
	XEDEX_VSA_CODEC_MPEG4	= (1UL<<1),

	/*S: bit8~bit15*/
	XEDEX_VSA_CODEC_JPEG	= (1UL<<8),

	/*A: bit16~bit30*/
	XEDEX_VSA_CODEC_MP3		= (1UL<<16),

	/**
	 * This is a special value for query;
	 */
	XEDEX_VSA_CODEC_AUTO	= (1UL<<31),
};

enum XEDEX_CATEGORY
{
	/**
	 * Stream Media's per frame or a Still Image data
	 **/
	XEDEX_CATEGORY_FRAME,
/*Added for audio support by wangchunhuan @ 20100816 BEGIN*/
	XEDEX_CATEGORY_AUDIO,
/*Added for audio support by wangchunhuan @ 20100816 END*/
/*Added for image support by wangchunhuan @ 20100822 BEGIN*/
	XEDEX_CATEGORY_IMAGE,
/*Added for image support by wangchunhuan @ 20100822 END*/

	/**
	* Raw Data
	* Dec-29-2010 added by wuhm<wuhm@hisome.com>
	**/
	XEDEX_CATEGORY_DATA,
};

#define XEDEX_MAGIK_H_0	(0x20)
#define XEDEX_MAGIK_H_1	(0x11)
#define XEDEX_MAGIK_H_2	(0x04)
#define XEDEX_MAGIK_H_3	(0x06)

#define XEDEX_MAGIK_T_0	(0x07)
#define XEDEX_MAGIK_T_1	(0x04)
#define XEDEX_MAGIK_T_2	(0x11)
#define XEDEX_MAGIK_T_3	(0x20)

struct xedex_stru
{
	/**
	 * Apr-6-2011 added by wuhm<wuhm@hisome.com>
	 * for xedex_t tranferring in network checking, memory using ignore this value;
	 * 		magiK_H[0] == XEDEX_MAGIK_H_0
	 * 		magiK_H[1] == XEDEX_MAGIK_H_1
	 * 		magiK_H[2] == XEDEX_MAGIK_H_2
	 * 		magiK_H[3] == XEDEX_MAGIK_H_3
	 **/
	unsigned char magiK_H[4];

	enum XEDEX_CATEGORY category;
/*Added for data source channel index support by wangchunhuan @ 20100816 BEGIN*/
	int channel;
/*Added for data source channel index support by wangchunhuan @ 20100816 END*/
	union
	{
		struct
		{
			enum XEDEX_FRAME_TYPE type;
			/**
			 * Apr-6-2011 added by wuhm<wuhm@hisome.com>
			 */
			enum XEDEX_VSA_CODEC codec;

/*Added for video lost support by wangchunhuan @ 20100816 BEGIN*/
			int video_lost;/*0: normal video signal; others: video lost*/
/*Added for video lost support by wangchunhuan @ 20100816 BEGIN*/

			enum XEDEX_FRAME_RESOLUTION resolution;
			/**
			 * if frame_resolution==XEFD_FRAME_RESOLUTION_USER, ures_width+ures_height is valid
			 **/
			int ures_width,ures_height;

			/**
			 * sequence number of this frame
			 **/
			int seq;

			void *data;
			int data_len;
			int data_size;
		}frame;/*XEDEX_CATEGORY_FRAME*/

		/**more other category's data structure**/
/*Added for audio support by wangchunhuan @ 20100816 BEGIN*/
		struct
		{
			/**
			 * sequence number of this frame
			 **/
			int seq;

			void *data;
			int data_len;
			int data_size;
		}audio;/*XEDEX_CATEGORY_AUDIO*/
/*Added for audio support by wangchunhuan @ 20100816 BEGIN*/
/*Added for image support by wangchunhuan @ 20100822 BEGIN*/
		struct
		{
			enum XEDEX_FRAME_TYPE type;	//image type
			/**
			 * Apr-6-2011 added by wuhm<wuhm@hisome.com>
			 */
			enum XEDEX_VSA_CODEC codec;

			/**
			 * sequence number of this image
			 **/
			int seq;

			void *data;
			int data_len;
			int data_size;

			unsigned short width;	//image width
			unsigned short height;	//image height
			unsigned short q_value;	/*Quality factor for encoder
						 *Set to a value between 0 (lowest quality)
						 *and 100 (highest quality).
						 */
			void *priv;		/*private data. 
						 *Type "PG_PTri_scene_t *" only
						 *We do not use "PG_PTri_scene_t *"directly
						 *for decrease head file interdepends
						 */
			
		}image;
/*Added for image support by wangchunhuan @ 20100822 END*/

		/**
		 * Dec-29-2010 added by wuhm<wuhm@hisome.com>
		 */
		struct
		{
			void *addr_virt;/*virture address*/
			unsigned long addr_phy;/*physical address for DMA*/
			int length,size;
		}data;/*XEDEX_CATEGORY_DATA*/

	}U;

	/**
	 * creater MUST initlizer this member;
	 */
	pthread_mutex_t lock;

	/**
	 * this data's timestamp
	 */
	struct timeval birthsec;

	/**
	 * xedex_t generator's dexfree() method
	 */
	xedex_free_f dexfree;

	/**
	 * this is xedex_t generator's private data, for dexfree() context
	 */
	void *priv;

	/**
	 * Apr-6-2011 added by wuhm<wuhm@hisome.com>
	 * for xedex_t tranferring in network checking, memory using ignore this value;
	 * 		magiK_T[0] == XEDEX_MAGIK_T_0
	 * 		magiK_T[1] == XEDEX_MAGIK_T_1
	 * 		magiK_T[2] == XEDEX_MAGIK_T_2
	 * 		magiK_T[3] == XEDEX_MAGIK_T_3
	 **/
	unsigned char magiK_T[4];
};


#endif /* __XEDEX_H_ */
