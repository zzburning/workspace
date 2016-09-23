#include "stdio.h"




/* 长整型大小端互换 */
#define BigLittleSwap32(A)  ((((unsigned int)(A) & 0xff000000) >> 24) | \
                             (((unsigned int)(A) & 0x00ff0000) >> 8) | \
                             (((unsigned int)(A) & 0x0000ff00) << 8) | \
                             (((unsigned int)(A) & 0x000000ff) << 24))


/* 本机大端返回1，小端返回0 */
int checkCPUendian()
{
	union{
	      unsigned int i;
	      unsigned char s[4];
	}c; 

	c.i = 0x12345678;
	return (0x12 == c.s[0]);
} 

/* 模拟htonl函数，本机字节序转网络字节序 
 * 若本机为大端，与网络字节序同，直接返回
 * 若本机为小端，转换成大端再返回
 */
unsigned int _htonl(unsigned int h)
{
	/* return checkCPUendian() ? h : BigLittleSwap32(h); */
	return BigLittleSwap32(h);
}

/* 模拟ntohl函数，网络字节序转本机字节序 
 * 若本机为大端，与网络字节序同，直接返回
 * 若本机为小端，网络数据转换成小端再返回
 */
unsigned int _ntohl(unsigned int n)
{
   /* return checkCPUendian() ? n : BigLittleSwap32(n); */
	return BigLittleSwap32(n);
}


int main()
{
	int a = 0x11223344;
	printf("%d\n",checkCPUendian());
	printf("%c\n", ((char*)&a)[0]);
	printf("%s\n", ((char*)&a));
}