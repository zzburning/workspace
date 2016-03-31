/*
linphone
Copyright (C) 2000  Simon MORLAT (simon.morlat@free.fr)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include "uglib.h"

#ifndef _WIN32
#	include <time.h>
#	include <sys/resource.h>
#	include <sys/wait.h>
#else
#	include <io.h>
#	include <limits.h>
#	ifndef PATH_MAX
#		define PATH_MAX 512
#	endif
#	include <direct.h>
#endif
#include <unistd.h>
#include <sys/time.h>

GError *g_error_new(gint dummy1, gint dummy2, const gchar* errormsg,...){
	va_list args;
	fprintf(stderr,"Warning:");
	va_start (args, errormsg);
	vfprintf (stderr, errormsg, args);
	va_end (args);
	fprintf(stderr,"\n");
	return "";
}
void    g_set_error(GError **err,gint dummy1,gint dummy2,const gchar *errormsg,...){
	va_list args;
	fprintf(stderr,"Warning:");
	va_start (args, errormsg);
	vfprintf (stderr, errormsg, args);
	va_end (args);
	fprintf(stderr,"\n");
	return;
}


gboolean g_file_test(const char *filename, gint test)
{
  return access(filename,F_OK)==0;
}


gchar*
g_strconcat (const gchar *string1, ...)
{
  gsize	  l;
  va_list args;
  gchar	  *s;
  gchar	  *concat;
  gchar   *ptr;

  g_return_val_if_fail (string1 != NULL, NULL);

  l = 1 + strlen (string1);
  va_start (args, string1);
  s = va_arg (args, gchar*);
  while (s)
    {
      l += strlen (s);
      s = va_arg (args, gchar*);
    }
  va_end (args);

  concat = g_new (gchar, l);
  ptr = concat;

  ptr = g_stpcpy (ptr, string1);
  va_start (args, string1);
  s = va_arg (args, gchar*);
  while (s)
    {
      ptr = g_stpcpy (ptr, s);
      s = va_arg (args, gchar*);
    }
  va_end (args);

  return concat;
}

void g_strfreev(gchar **strarray){
	while(*strarray!=NULL){
		g_free(*strarray);
		strarray++;
	}		
}



gdouble g_timer_elapsed(GTimer *t,guint *us){
  struct timeval current;
  gint tmp;
  gdouble elapsed;
  gettimeofday(&current,NULL);
  tmp=current.tv_usec-t->tv_usec;
  if (us!=NULL) {
    if (tmp>0) *us=tmp;
    else *us=1000000+tmp;
  }
  elapsed=(current.tv_sec-t->tv_sec) + ((double)tmp/1e6);
  return elapsed;
}

static void grow_gstring(GString *obj, gint bytes){
	if (obj->allocated_len<=(bytes+obj->len)){
		obj->allocated_len+=bytes;
		obj->str=(gchar *)g_realloc(obj->str,obj->allocated_len);
	}
}

/* GString */
GString *g_string_new(const gchar *init){
	GString *obj=g_new(GString,1);
	if (init!=NULL){
		obj->str=g_strdup(init);
		obj->curindex=obj->len=strlen(init);
		obj->allocated_len=obj->len+1;
	}else{
		obj->str=(gchar *)g_malloc(40);
		obj->len=0;
		obj->curindex=0;
		obj->str[0]='\0';
		obj->allocated_len=40;
	}
	return obj;
}

GString *g_string_append_c(GString *obj, gchar c){
	grow_gstring(obj,1);
	obj->str[obj->curindex]=c;
	obj->curindex++;
	obj->len++;
	obj->str[obj->curindex]='\0';
	return obj;
}
GString *g_string_append(GString *obj, const gchar *val){
	gint len=strlen(val);
	grow_gstring(obj,len);
	strcpy(&obj->str[obj->curindex],val);
	obj->curindex+=len;
	obj->len+=len;
	obj->str[obj->curindex]='\0';
	return obj;
}

GString *g_string_append_len(GString *obj, const gchar *val, gssize len)
{
	grow_gstring(obj,len);
	memcpy(&obj->str[obj->curindex],val,len);
	obj->curindex+=len;
	obj->str[obj->curindex]='\0';
	obj->len+=len;
	return obj;
}

gchar * g_string_free(GString *string, gboolean free_segment){
	gchar *ret=string->str;
	if (free_segment) {
		g_free(string->str);
		return NULL;
	}
	g_free(string);
	return ret;
}

char * __g_strdup_vprintf(const char *fmt, va_list ap)
{
	/* Guess we need no more than 100 bytes. */
	int n, size = 100;
	char *p;
	if ((p = (char *)g_malloc (size)) == NULL)
		return NULL;
	while (1)
	{
		/* Try to print in the allocated space. */
		n = vsnprintf (p, size, fmt, ap);
		/* If that worked, return the string. */
		if (n > -1 && n < size)
			return p;
		//printf("Reallocing space.\n");
		/* Else try again with more space. */
		if (n > -1)	/* glibc 2.1 */
			size = n + 1;	/* precisely what is needed */
		else		/* glibc 2.0 */
			size *= 2;	/* twice the old size */
		if ((p = (char *)g_realloc (p, size)) == NULL)
			return NULL;
	}
}	

char * g_strdup_printf(const char *fmt, ...)
{
	va_list ap;
	char *ret;
	va_start (ap, fmt);
	ret = __g_strdup_vprintf (fmt,ap);
	va_end (ap);
	return ret;
}


#ifndef HAVE_STRNDUP
char *strndup(const char *s, size_t n){
	int max=MIN(strlen(s),n);
	char *ret=(char *)malloc(max+1);
	memcpy(ret,s,max);
	ret[max]='\0';
	return ret;
}
#endif

#ifndef HAVE_GET_CURRENT_DIR_NAME
char *get_current_dir_name(void){
	char *ret=(char *)malloc(255);
	return getcwd(ret,255);
}
#endif

#ifndef HAVE_STPCPY
char *stpcpy(char *dest, const char *src){
	char *ret=strcpy(dest,src);
	return ret+strlen(src)+1;
}
#endif

guint32 g_random_int(void){
	static int initialized=0;

	if(!initialized){
		srand((unsigned int)time(NULL));
		initialized=1;
	}
	return rand();
}


void uglib_log(const gchar *log_domain,GLogLevelFlags log_level,
                                           const gchar *message,
                                           gpointer user_data)
{
	gchar *lev;
	switch(log_level){
		case G_LOG_LEVEL_MESSAGE:
			lev="message";
			break;
		case G_LOG_LEVEL_WARNING:
			lev="warning";
			break;
		case G_LOG_LEVEL_ERROR:
			lev="error";
		default:
			lev="(unknown log type)";
	}
	if (user_data==NULL){
		user_data=stdout;
	}
	fprintf((FILE*)user_data,"%s-%s:%s\n",log_domain,lev,message);
}


static GLogFunc __log_func=uglib_log;
static gpointer __log_user_data=(gpointer)NULL;

void g_log(const gchar *log_domain,GLogLevelFlags log_level,const gchar *format,...){
	va_list args;
	va_start(args,format);
	g_logv(log_domain,log_level,format,args);
	va_end(args);
}

void g_logv(const gchar *log_domain,GLogLevelFlags log_level,const gchar *format,va_list args){
	gchar *msg;
	msg=__g_strdup_vprintf(format,args);
	__log_func(log_domain,log_level,msg,__log_user_data);
	g_free(msg);
}

void g_log_set_handler(const gchar *log_domain,GLogLevelFlags log_levels, GLogFunc log_func, gpointer user_data){
	__log_func=log_func;
	__log_user_data=user_data;
}

