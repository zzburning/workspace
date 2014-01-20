/*		Filename: mylog.c
 *************************************************
 * Description:
 *		log interface.
 * Version:
 *		V_0.1	
 * Copyright:
 *		
 * Author:
 *	
 */

#include "mylog.h"

int be_syslog=1;
int log_level=7;

int init_mylog(void){
#ifdef LOG_AS_SYSLOG
	if(be_syslog){
		openlog(MSG_PREFIX,LOG_PERROR,LOG_DAEMON);
	}
#endif
	return 0;
}

#if defined(LOG_AS_NETWORK)
int mylog_sockfd = -1;

static char *mylog_buffer=NULL;
static int mylog_buffer_len=0;

int mylog_PUSH(char *sbuf,int slen){
	if(mylog_sockfd>=0)
		return write(mylog_sockfd,sbuf,slen);
	
	if(mylog_buffer==NULL){
		mylog_buffer=calloc(1,4096);
		if(mylog_buffer==NULL){
			return -1;
		}
	}
	
	if(mylog_buffer_len + slen < 4096){
		memcpy(mylog_buffer+mylog_buffer_len,sbuf,slen);
		mylog_buffer_len+=slen;
		return 0;
	}
	
	return -1;
}

int __mylog_flush(void){
	if(mylog_buffer){
		write(mylog_sockfd,mylog_buffer,mylog_buffer_len);
		free(mylog_buffer);
		mylog_buffer=NULL;
		mylog_buffer_len=0;
	}
	
	return 0;
}
int dnit_mylog_network(void){
	if(mylog_sockfd>=0){
		close(mylog_sockfd);
		mylog_sockfd=-1;
	}
	
	return 0;
}
int init_mylog_network(const char *remoteIP,int remotePort){
	struct sockaddr_in raddr;
	
	if(mylog_sockfd>=0){
		close(mylog_sockfd);
	}
	
	mylog_sockfd=socket(AF_INET,SOCK_DGRAM,0);
	if(mylog_sockfd==-1){
		printf("%s(%d): socket fail, %s\n",__func__,__LINE__,strerror(errno));
		return -1;
	}
	
	if(inet_aton(remoteIP,&raddr.sin_addr)==0){
		printf("%s(%d): invalid remoteIP(%s)\n",__func__,__LINE__,remoteIP);
		goto err_out;
	}
	
	raddr.sin_family = AF_INET;
	raddr.sin_port = htons(remotePort);
	
	if(connect(mylog_sockfd,(struct sockaddr*)&raddr,sizeof(raddr)) == -1){
		printf("%s(%d): connect(%s:%d) fail, %s\n",__func__,__LINE__, \
						remoteIP,remotePort,strerror(errno));
		goto err_out;
	}
	
	__mylog_flush();
	return 0;
	
err_out:
	close(mylog_sockfd);
	mylog_sockfd=-1;
	return -1;
}


#endif //end of #if defined(LOG_AS_NETWORK)

