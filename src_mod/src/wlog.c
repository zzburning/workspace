
#include "wlog.h"

int be_syslog=1;
int log_level=7;

int init_wlog(void){
#ifdef LOG_AS_SYSLOG
	if(be_syslog){
		openlog(MSG_PREFIX,LOG_PERROR,LOG_DAEMON);
	}
#endif
	return 0;
}

#if defined(LOG_AS_NETWORK)
int wlog_sockfd = -1;

static char *wlog_buffer=NULL;
static int wlog_buffer_len=0;

int wLOG_PUSH(char *sbuf,int slen){
	if(wlog_sockfd>=0)
		return write(wlog_sockfd,sbuf,slen);
	
	if(wlog_buffer==NULL){
		wlog_buffer=calloc(1,4096);
		if(wlog_buffer==NULL){
			return -1;
		}
	}
	
	if(wlog_buffer_len + slen < 4096){
		memcpy(wlog_buffer+wlog_buffer_len,sbuf,slen);
		wlog_buffer_len+=slen;
		return 0;
	}
	
	return -1;
}

int __wlog_flush(void){
	if(wlog_buffer){
		write(wlog_sockfd,wlog_buffer,wlog_buffer_len);
		free(wlog_buffer);
		wlog_buffer=NULL;
		wlog_buffer_len=0;
	}
	
	return 0;
}
int dnit_wlog_network(void){
	if(wlog_sockfd>=0){
		close(wlog_sockfd);
		wlog_sockfd=-1;
	}
	
	return 0;
}
int init_wlog_network(const char *remoteIP,int remotePort){
	struct sockaddr_in raddr;
	
	if(wlog_sockfd>=0){
		close(wlog_sockfd);
	}
	
	wlog_sockfd=socket(AF_INET,SOCK_DGRAM,0);
	if(wlog_sockfd==-1){
		printf("%s(%d): socket fail, %s\n",__func__,__LINE__,strerror(errno));
		return -1;
	}
	
	if(inet_aton(remoteIP,&raddr.sin_addr)==0){
		printf("%s(%d): invalid remoteIP(%s)\n",__func__,__LINE__,remoteIP);
		goto err_out;
	}
	
	raddr.sin_family = AF_INET;
	raddr.sin_port = htons(remotePort);
	
	if(connect(wlog_sockfd,(struct sockaddr*)&raddr,sizeof(raddr)) == -1){
		printf("%s(%d): connect(%s:%d) fail, %s\n",__func__,__LINE__, \
						remoteIP,remotePort,strerror(errno));
		goto err_out;
	}
	
	__wlog_flush();
	return 0;
	
err_out:
	close(wlog_sockfd);
	wlog_sockfd=-1;
	return -1;
}


#endif //end of #if defined(LOG_AS_NETWORK)

