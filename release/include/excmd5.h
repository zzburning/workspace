
#ifndef __EXC_MD5_H_2008_8_6
#define __EXC_MD5_H_2008_8_6



#ifdef __cplusplus
extern "C" {
#endif

extern char* MDString(char *str);
extern char* MDFile(char *file);
extern char* hmac_md5(char* text, char* key);

#ifdef __cplusplus
}
#endif




#endif /*MD5_H_*/
