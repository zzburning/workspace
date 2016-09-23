#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "wlog.h"
#include "config.h"

//error argument
#define EARG	-2
/*current target ID we are testing*/
extern hx_target_t cur_tID;

static void __report(int res)
{
	int my_errno;

	if(res >= 0)
	{
		ats_LOG("\tConfig(%s) PASS!", cur_conf_cmd->cl_name);
	}
	else if(res == -1)
	{
		my_errno = hx_get_errno(cur_tID);	//report errno message
		if(!my_errno)
			my_errno = hx_errno;
		ats_LOG("\tConfig(%s) FAIL! errno=%d strerror=%s", cur_conf_cmd->cl_name, my_errno, hx_get_strerror(my_errno));
	}
	else if(res == EARG)
	{
		ats_LOG("\tConfig(%s) FAIL! ARG ERROR!!!", cur_conf_cmd->cl_name);
	}
	else
	{
		xeLOG_ERR("It's a bug!!!");
	}
}

static int __arglen(char **arg)
{
	int len = 0;

	while(*arg)
	{
		len++;
		arg++;
	}
	printf("len=%d\n",len);
	return len;
}


/* equipment config function list */
int _iocg_eq_hostname(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_eq_hostname stru_name;

	bzero(&stru_name, sizeof(stru_name));
	ret = hx_ioctl(tID, HX_IOCG_EQ_HOSTNAME, &stru_name, sizeof(struct hx_ioc_eq_hostname));
	if(!ret)
	{
		DBG("hostname=%s", stru_name.hname);
	}
	__report(ret);
	return ret;
}

int _iocs_eq_hostname(int tID, char **arg)
{
	int ret = -1;

	if(__arglen(arg) != 1)
	{
		__report(EARG);
		return -1;
	}
	struct hx_ioc_eq_hostname stru_name;

	bzero(&stru_name, sizeof(stru_name));
	strcpy(stru_name.hname, arg[0]);
	ret = hx_ioctl(tID, HX_IOCS_EQ_HOSTNAME, &stru_name, sizeof(stru_name));

	__report(ret);
	return ret;
}

int _iocg_eq_bootproto(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_eq_bootproto stru_bp;

	bzero(&stru_bp, sizeof(struct hx_ioc_eq_bootproto));
	ret = hx_ioctl(tID, HX_IOCG_EQ_BOOTPROTO, &stru_bp, sizeof(struct hx_ioc_eq_bootproto));
	if(!ret)
	{
		DBG("bootproto=%s", stru_bp.bpname);
	}
	__report(ret);
	return ret;
}

int _iocs_eq_bootproto(int tID, char **arg)
{
	int ret = -1;

	if(__arglen(arg) != 1)
	{
		xeLOG_ERR("Usage: ARG=[bootproto]");
		__report(EARG);
		return -1;
	}
	struct hx_ioc_eq_bootproto stru_bp;

	bzero(&stru_bp, sizeof(struct hx_ioc_eq_bootproto));
	strcpy(stru_bp.bpname, arg[0]);
	ret = hx_ioctl(tID, HX_IOCS_EQ_BOOTPROTO, &stru_bp, sizeof(struct hx_ioc_eq_bootproto));

	__report(ret);
	return ret;
}

int _iocg_eq_ip(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_eq_ip stru_ip;

	bzero(&stru_ip, sizeof(struct hx_ioc_eq_ip));
	ret = hx_ioctl(tID, HX_IOCG_EQ_IP, &stru_ip, sizeof(struct hx_ioc_eq_ip));

	__report(ret);
	return ret;
}

int _iocs_eq_ip(int tID, char **arg)
{
	int ret = -1;

	if(__arglen(arg) != 3)
	{
		__report(EARG);
		return -1;
	}
	DBG("ipaddr=%s netmask=%s gateway=%s", arg[0], arg[1], arg[2]);
	in_addr_t ipaddr, netmask, gateway;

	if(INADDR_NONE == (ipaddr = inet_addr(arg[0])))
		goto arg_err;
	if(INADDR_NONE == (netmask = inet_addr(arg[1])))
		goto arg_err;
	if(INADDR_NONE == (gateway = inet_addr(arg[2])))
		goto arg_err;

	struct hx_ioc_eq_ip stru_ip = { ipaddr, netmask, gateway };

	ret = hx_ioctl(tID, HX_IOCS_EQ_IP, &stru_ip, sizeof(struct hx_ioc_eq_ip));

	__report(ret);
	return ret;

  arg_err:
	__report(EARG);
	return -1;
}


int _iocg_eq_dns(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_eq_dns stru_dns;

	bzero(&stru_dns, sizeof(struct hx_ioc_eq_dns));
	ret = hx_ioctl(tID, HX_IOCG_EQ_DNS, &stru_dns, sizeof(struct hx_ioc_eq_dns));
	if(!ret)
	{
		DBG("dns1=%s", inet_ntoa(*((struct in_addr *)&stru_dns.dns1)));
		DBG("dns2=%s", inet_ntoa(*((struct in_addr *)&stru_dns.dns2)));
	}
	__report(ret);
	return ret;
}

int _iocs_eq_dns(int tID, char **arg)
{
	int ret = -1;

	if(__arglen(arg) != 2)
	{
		xeLOG_ERR("Usage: ARG=[DNS1] [DNS2]");
		__report(EARG);
		return -1;
	}
	in_addr_t dns1;

	in_addr_t dns2;

	if(INADDR_NONE == (dns1 = inet_addr(arg[0])))
		goto arg_err;
	if(INADDR_NONE == (dns2 = inet_addr(arg[1])))
		goto arg_err;

	struct hx_ioc_eq_dns stru_dns = { dns1, dns2 };
	ret = hx_ioctl(tID, HX_IOCS_EQ_DNS, &stru_dns, sizeof(struct hx_ioc_eq_dns));

	__report(ret);
	return ret;
  arg_err:
	__report(EARG);
	return -1;
}

int _iocg_eq_pppoe(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_eq_pppoe stru_ppp;

	bzero(&stru_ppp, sizeof(stru_ppp));
	ret = hx_ioctl(tID, HX_IOCG_EQ_PPPOE, &stru_ppp, sizeof(struct hx_ioc_eq_pppoe));
	if(!ret)
	{
		DBG("status=%d	isp=%s	username=%s	password=%s", stru_ppp.status, stru_ppp.isp,
			stru_ppp.username, stru_ppp.password);
	}

	__report(ret);
	return ret;
}

int _iocs_eq_pppoe(int tID, char **arg)
{
	int ret = -1;

	if(__arglen(arg) != 4)
	{
		xeLOG_ERR("Usage: ARG=[status(0=disable/1=enable)] [isp] [username] [password]");
		__report(EARG);
		return -1;
	}
	struct hx_ioc_eq_pppoe stru_ppp;

	bzero(&stru_ppp, sizeof(stru_ppp));
	stru_ppp.status = atoi(arg[0]);
	strcpy(stru_ppp.isp, arg[1]);
	strcpy(stru_ppp.username, arg[2]);
	strcpy(stru_ppp.password, arg[3]);


	ret = hx_ioctl(tID, HX_IOCS_EQ_PPPOE, &stru_ppp, sizeof(struct hx_ioc_eq_pppoe));
	__report(ret);
	return ret;
}

int _iocg_eq_datetime(int tID, char **arg)
{
	int ret = -1;

	hx_datetime_t dt;

	bzero(&dt, sizeof(dt));
	ret = hx_ioctl(tID, HX_IOCG_EQ_DATETIME, &dt, sizeof(hx_datetime_t));
	if(!ret)
	{
		ats_LOG("datetime=%04d_%02d_%02d_%02d_%02d_%02d", dt.year, dt.mon, dt.day, dt.hour, dt.min, dt.sec);
		DBG("datetime=%04d-%02d-%02d %02d:%02d:%02d", dt.year, dt.mon, dt.day, dt.hour, dt.min, dt.sec);
	}

	__report(ret);
	return ret;
}

int _iocs_eq_datetime(int tID, char **arg)
{
	int ret = -1;

	if(__arglen(arg) != 6)
	{
		xeLOG_ERR("Usage: ARG=[year] [mon] [day] [hour] [min] [sec]");
		__report(EARG);
		return -1;
	}
	hx_datetime_t dt;

	dt.year = atoi(arg[0]);
	if(atoi(arg[1])>=1 && atoi(arg[1])<=12)
	{
		dt.mon = atoi(arg[1]);
	}else{
		printf("month range of [1-12]");
		return -1;
	}
	if(atoi(arg[2])>=1 && atoi(arg[2])<=31)
	{
		dt.day = atoi(arg[2]);
	}else{
		printf("day range of [1-31]");
		return -1;
	}
	if(atoi(arg[3])>=0 && atoi(arg[3])<24)
	{
		dt.hour = atoi(arg[3]);
	}else{
		printf("hour range of [0-23]");
		return -1;
	}
	if(atoi(arg[4])>=0 && atoi(arg[4])<60)
	{
		dt.min = atoi(arg[4]);
	}else{
		printf("min range of [0-60]");
		return -1;
	}
	if(atoi(arg[5])>=0 && atoi(arg[5])<60)
	{
		dt.sec = atoi(arg[5]);
	}else{
		printf("sec range of [0-60]");
		return -1;
	}

	ret = hx_ioctl(tID, HX_IOCS_EQ_DATETIME, &dt, sizeof(hx_datetime_t));

	__report(ret);
	return ret;
}

int _iocs_eq_default(int tID, char **arg)
{
	int ret = -1;

	int opt;

	if(__arglen(arg) != 1 || (opt = atoi(arg[0])) != 1)
	{
		xeLOG_ERR("ARG ERROR!!! Must be ARG=1!!!");
		__report(EARG);
		return -1;
	}

	ret = hx_ioctl(tID, HX_IOCS_EQ_DEFAULT, &opt, sizeof(int));
	__report(ret);
	return ret;
}

int _iocs_eq_reboot(int tID, char **arg)
{
	int ret = -1;

	int opt;

	if(__arglen(arg) != 1 || (opt = atoi(arg[0])) != 1)
	{
		xeLOG_ERR("ARG ERROR!!! Must be ARG=1!!!");
		__report(EARG);
		return -1;
	}

	ret = hx_ioctl(tID, HX_IOCS_EQ_REBOOT, &opt, sizeof(int));
	__report(ret);
	return ret;
}

int _iocs_eq_halt(int tID, char **arg)
{
	int ret = -1;

	int opt;

	if(__arglen(arg) != 1 || (opt = atoi(arg[0])) != 1)
	{
		xeLOG_ERR("ARG ERROR!!! Must be ARG=1!!!");
		__report(EARG);
		return -1;
	}

	ret = hx_ioctl(tID, HX_IOCS_EQ_HALT, &opt, sizeof(int));
	__report(ret);
	return ret;
}

int _iocg_eq_user(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_eq_user stru_user;

	bzero(&stru_user, sizeof(stru_user));
	ret = hx_ioctl(tID, HX_IOCG_EQ_USER, &stru_user, sizeof(struct hx_ioc_eq_user));
	if(!ret)					//print user message
	{
		struct hx_ioc_eq_user *head = &stru_user, *next;

		int i = 1;

		while(head)
		{
			next = head->nuser;
			DBG("User_%d: username=%s password=%s gid=%d", i, head->username, head->password, head->gid);
			i++;
			head = next;
		}

		head = stru_user.nuser;
		while(head)
		{
			next = head->nuser;

			free(head);
			head = next;
		}
	}

	__report(ret);
	return ret;
}

int _iocs_eq_user(int tID, char **arg)
{
	int ret = -1;

	if(__arglen(arg) != 3)
	{
		xeLOG_ERR("Usage: ARG=username password gid,if you want to del user,gid=-1");
		__report(EARG);
		return -1;
	}
	struct hx_ioc_eq_user user;

	bzero(&user, sizeof(struct hx_ioc_eq_user));
	strcpy(user.username, arg[0]);
	strcpy(user.password, arg[1]);
	user.gid = atoi(arg[2]);
	ret = hx_ioctl(tID, HX_IOCS_EQ_USER, &user, sizeof(user));

	return ret;
}


int _iocg_eq_group(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_eq_group stru_grp;

	bzero(&stru_grp, sizeof(stru_grp));
	ret = hx_ioctl(tID, HX_IOCG_EQ_GROUP, &stru_grp, sizeof(stru_grp));
	if(!ret)
	{
		struct hx_ioc_eq_group *head = &stru_grp, *next;

		int i = 1;

		while(head)
		{
			next = head->ngroup;
			DBG("Group_%d: gid=%d capabilities=%d openChannel=%lu", i,
				head->gid, head->capabilities, head->openChannel);
			i++;
			head = next;
		}

		head = stru_grp.ngroup;	//free memory
		while(head)
		{
			next = head->ngroup;
			free(head);

			head = next;
		}
	}

	__report(ret);
	return ret;
}

int _iocs_eq_group(int tID, char **arg)
{
	int ret = -1;

	if(__arglen(arg) != 3)
	{
		xeLOG_ERR("Usage: ARG=gid capabilities openChannel");
		__report(EARG);
		return -1;
	}
	struct hx_ioc_eq_group grp;

	bzero(&grp, sizeof(grp));
	grp.gid = atoi(arg[0]);
	grp.capabilities = atoi(arg[1]);
	grp.openChannel = atoi(arg[2]);
	ret = hx_ioctl(tID, HX_IOCS_EQ_GROUP, &grp, sizeof(grp));

	return ret;
}


/*get/set equipment preview windows number*/
int _iocg_eq_display_windows(int tID, char **arg)
{
	int ret = -1;

	int dis_win;

	ret = hx_ioctl(tID, HX_IOCG_EQ_DISPLAY_WINDOWS, &dis_win, sizeof(int));
	if(!ret)
	{
		DBG("display windows: %d", dis_win);
	}
	__report(ret);
	return ret;
}

int _iocs_eq_display_windows(int tID, char **arg)
{
	int ret = -1;

	if(__arglen(arg) != 1)
	{
		xeLOG_ERR("ARG ERROR!!! Must be only one arg!!!");
		__report(EARG);
		return -1;
	}
	int dis_win = atoi(arg[0]);

	ret = hx_ioctl(tID, HX_IOCS_EQ_DISPLAY_WINDOWS, &dis_win, sizeof(int));
	__report(ret);
	return ret;
}


/*get/set equipment preview frame position*/
int _iocg_eq_window_display(int tID, char **arg)
{
	int ret = -1;

	int i;

	struct hx_ioc_eq_win_display wdisp;

	bzero(&wdisp, sizeof(wdisp));

	for(i = 1; i <= 16; i++)
	{
		wdisp.winum = i;
		wdisp.ChaID = 0;
		ret = hx_ioctl(tID, HX_IOCG_EQ_WINDOW_DISPLAY, &wdisp, sizeof(wdisp));
		if(ret < 0)
		{
			xeLOG_ERR("winum_%d get display ERROR!!!", i);
		}
	}
	__report(ret);
	return ret;
}

int _iocs_eq_window_display(int tID, char **arg)
{
	int ret = -1;

	if(__arglen(arg) != 2)
	{
		__report(EARG);
		return -1;
	}
	struct hx_ioc_eq_win_display wdisp;

	bzero(&wdisp, sizeof(wdisp));
	wdisp.winum = atoi(arg[0]);
	wdisp.ChaID = atoi(arg[1]);
	ret = hx_ioctl(tID, HX_IOCS_EQ_WINDOW_DISPLAY, &wdisp, sizeof(wdisp));
	__report(ret);
	return ret;
}


int _iocg_eq_hosts(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_eq_hosts hosts;

	int len = sizeof(struct hx_ioc_eq_hosts);

	bzero(&hosts, len);
	ret = hx_ioctl(tID, HX_IOCG_EQ_HOSTS, &hosts, len);
	if(!ret)
	{
		struct hx_ioc_eq_hosts *head = &hosts;

		struct hx_ioc_eq_hosts *hnext;

		int i = 1;

		while(head)				//print msg
		{
			hnext = head->next;
			DBG("host_%d: hostip=%s hostname=%s", i, inet_ntoa(*(struct in_addr *)(&head->hostip)), head->hostnames);

			i++;
			head = hnext;
		}

		free(hosts.hostnames);
		struct hx_ioc_eq_hosts *host = hosts.next;

		while(host)
		{
			hnext = host->next;
			if(host->hostnames)
				free(host->hostnames);
			free(host);

			host = hnext;
		}
	}

	__report(ret);
	return ret;
}

int _iocs_eq_hosts(int tID, char **arg)
{
	int ret = -1;

	if(__arglen(arg) != 2)
	{
		xeLOG_ERR("Usage: ARG=hostip hostnames");
		__report(EARG);
		return -1;
	}
	struct hx_ioc_eq_hosts hosts;

	bzero(&hosts, sizeof(hosts));
	hosts.hostip = inet_addr(arg[0]);
	hosts.hostnames = arg[1];
	ret = hx_ioctl(tID, HX_IOCS_EQ_HOSTS, &hosts, sizeof(hosts));

	__report(ret);
	return ret;
}

int _iocg_eq_disk(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_eq_disk stru_disk;
	char *hd_state[]={"default","Standby","Working",};

	bzero(&stru_disk, sizeof(struct hx_ioc_eq_disk));
	// stru_disk.type = HX_DISK_TYPE_ALL;
	stru_disk.type = HX_DISK_TYPE_SATA;
	ret = hx_ioctl(tID, HX_IOCG_EQ_DISK, &stru_disk, sizeof(struct hx_ioc_eq_disk));
	if(!ret)
	{
		if(stru_disk.type==HX_DISK_TYPE_NONE)
		{
			printf("no partition infomation get.\n");
		}
		else
		{
			report_LOG("================================================");
			report_LOG("\tget harddisk partition infomation success");
			struct hx_ioc_eq_disk *i;

			i=&stru_disk;
			while(i)
			{
				printf("\t%s partition %s\n",i->type==HX_DISK_TYPE_SATA?"SATA":"USB",i->pname);
				report_LOG("\t%s partition %s\n",i->type==HX_DISK_TYPE_SATA?"SATA":"USB",i->pname);
				printf("\tMDIR=%s FSTYPE=%s CAPACITY=%dGB FREESPACE=%dGB\n", \
							i->mdir,i->fstype,i->capacity,i->freespace);
				report_LOG("\tMDIR=%s FSTYPE=%s CAPACITY=%dGB FREESPACE=%dGB\n",  \
							i->mdir,i->fstype,i->capacity,i->freespace);
				printf("\tharddisk state %s\n",hd_state[i->state]);
				report_LOG("\tharddisk state %s\n",hd_state[i->state]);
				
				printf("\tStartTime:%4d-%02d-%02d %02d:%02d:%02d\n",\
				      i->StartTime.year,i->StartTime.mon,i->StartTime.day,\
				      i->StartTime.hour,i->StartTime.min,i->StartTime.sec);
				
				printf("\tEndTime:%4d-%02d-%02d %02d:%02d:%02d\n",\
				      i->EndTime.year,i->EndTime.mon,i->EndTime.day,\
				      i->EndTime.hour,i->EndTime.min,i->EndTime.sec);
				
				printf("\tpicStartTime:%4d-%02d-%02d %02d:%02d:%02d\n",\
				      i->pic_StartTime.year,i->pic_StartTime.mon,i->pic_StartTime.day,\
				      i->pic_StartTime.hour,i->pic_StartTime.min,i->pic_StartTime.sec);
				
				printf("\tpicEndTime:%4d-%02d-%02d %02d:%02d:%02d\n",\
				      i->pic_EndTime.year,i->pic_EndTime.mon,i->pic_EndTime.day,\
				      i->pic_EndTime.hour,i->pic_EndTime.min,i->pic_EndTime.sec);
				
				printf("\tfile_num: %d\n",i->file_num);
				printf("\tfile_full_num: %d\n",i->file_full_num);
				printf("\tpic_full_num: %d\n",i->pic_full_num);
				printf("\tfile_empty_num: %d\n",i->file_empty_num);
				printf("\tfile_active_num: %d\n",i->file_active_num);
				printf("\tfile_error_num: %d\n",i->file_error_num);
				i=i->next;
			}

			struct hx_ioc_eq_disk *head, *next;
		
			head = stru_disk.next;
			while(head)
			{
				next = head->next;
				free(head);
				head = next;
			}
		}
	}
	else
	{
		printf("===============get disk info fail %d\n",ret);
		report_LOG("================================================");
		report_LOG("\tget harddisk partition infomation fail");
	}

	__report(ret);

	return ret;
}

int _iocs_eq_disk(int tID, char **arg)
{
	int ret = -1;

	if(__arglen(arg) != 2)
	{
		xeLOG_ERR("Usage: ARG=pname fstype");
		__report(EARG);
		return -1;
	}
	struct hx_ioc_eq_disk disk;

	bzero(&disk, sizeof(disk));

	disk.type = HX_DISK_TYPE_SATA;
	disk.oper = HX_DISK_OPER_CFS;
	strcpy(disk.pname, arg[0]);
	strcpy(disk.fstype, arg[1]);

	ret = hx_ioctl(tID, HX_IOCS_EQ_DISK, &disk, sizeof(disk));

	__report(ret);
	return ret;
}

#if 0
int _iocg_eq_disk_ext(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_eq_disk_ext stru_disk;

	bzero(&stru_disk, sizeof(struct hx_ioc_eq_disk_ext));
	ret = hx_ioctl(tID, HX_IOCG_EQ_DISK_EXT, &stru_disk, sizeof(struct hx_ioc_eq_disk_ext));
	if(!ret)
	{
		DBG("Disk_ext: dname=%s model=%s firmware=%s", stru_disk.dname, stru_disk.model, stru_disk.firmware);
	}

	__report(ret);
	return ret;
}
#endif

int _iocg_eq_sip(int tID, char **arg)
{
	int ret = -1;

	struct hxsdk_sip_account sip;

	bzero(&sip, sizeof(sip));
	ret = hx_ioctl(tID, HX_IOCG_EQ_SIP, &sip, sizeof(sip));
	if(!ret)
	{
		if(sip.sip_username)
			free(sip.sip_username);
		if(sip.sip_pwd)
			free(sip.sip_pwd);
		if(sip.sip_realm)
			free(sip.sip_realm);
		if(sip.sip_outbound_proxy)
			free(sip.sip_outbound_proxy);
		if(sip.sip_regsrv)
			free(sip.sip_regsrv);
		if(sip.local_addr)
			free(sip.local_addr);
	}

	__report(ret);
	return ret;
}


int _iocs_eq_sip(int tID, char **arg)
{
	int ret = -1;

	if(__arglen(arg) != 7)
	{
		xeLOG_ERR("Usage: ARG=username pwd realm outbound_proxy outbound_proxy_port regsrv regsrv_port");
		__report(EARG);
		return -1;
	}
	struct hxsdk_sip_account sip;

	bzero(&sip, sizeof(sip));
	sip.sip_username = (char *)arg[0];
	sip.sip_pwd = (char *)arg[1];
	sip.sip_realm = (char *)arg[2];
	sip.sip_outbound_proxy = (char *)arg[3];
	sip.sip_outbound_proxy_port = atoi(arg[4]);
	sip.sip_regsrv = (char *)arg[5];
	sip.sip_regsrv_port = atoi(arg[6]);
	ret = hx_ioctl(tID, HX_IOCS_EQ_SIP, &sip, sizeof(sip));

	__report(ret);
	return ret;
}


int _iocg_eq_udp_pktsize(int tID, char **arg)
{
	int ret = -1;

	int pktsize;

	ret = hx_ioctl(tID, HX_IOCG_EQ_UDP_PKTSIZE, &pktsize, sizeof(int));
	if(!ret)
	{
		DBG("Pktsize: %d", pktsize);
	}

	__report(ret);
	return ret;
}

int _iocs_eq_udp_pktsize(int tID, char **arg)
{
	int ret = -1;

	int pktsize;

	if(__arglen(arg) != 1)
	{
		xeLOG_ERR("ARG ERROR!!! ARG=[pktsize]");
		__report(EARG);
		return -1;
	}
	pktsize = atoi(arg[0]);
	ret = hx_ioctl(tID, HX_IOCS_EQ_UDP_PKTSIZE, &pktsize, sizeof(int));

	__report(ret);
	return ret;
}

int _iocg_eq_ip_acl(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_eq_acl stru_acl;

	bzero(&stru_acl, sizeof(struct hx_ioc_eq_acl));
	if(__arglen(arg) != 1)
	{
		xeLOG_ERR("ARG ERROR!!! ARG=[1=allow|2=forbidden]");
		return -1;
	}
	stru_acl.acl = atoi(arg[0]);
	ret = hx_ioctl(tID, HX_IOCG_EQ_IP_ACL, &stru_acl, sizeof(struct hx_ioc_eq_acl));
	if(!ret)
	{
		struct hx_ioc_eq_acl *head = stru_acl.next, *next;;
		while(head)
		{
			next = head->next;
			free(head);
			head = next;
		}

	}

	__report(ret);
	return ret;
}

int _iocs_eq_ip_acl(int tID, char **arg)
{
	int ret = -1;

	if(__arglen(arg) != 3)
	{
		xeLOG_ERR("ARG ERROR!!! ARG=ACL METHOD ADDRESS");
		__report(EARG);
		return -1;
	}
	struct hx_ioc_eq_acl stru_acl;

	bzero(&stru_acl, sizeof(struct hx_ioc_eq_acl));
	stru_acl.acl = atoi(arg[0]);
	stru_acl.method = atoi(arg[1]);
	strcpy(stru_acl.addr, arg[2]);
	ret = hx_ioctl(tID, HX_IOCS_EQ_IP_ACL, &stru_acl, sizeof(struct hx_ioc_eq_acl));

	__report(ret);
	return ret;
}

int _iocg_eq_sipuri_acl(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_eq_acl stru_acl;

	bzero(&stru_acl, sizeof(struct hx_ioc_eq_acl));
	if(__arglen(arg) != 1)
	{
		xeLOG_ERR("ARG ERROR!!! ARG=[1=allow|2=forbidden]");
		return -1;
	}
	stru_acl.acl = atoi(arg[0]);

	ret = hx_ioctl(tID, HX_IOCG_EQ_SIPURI_ACL, &stru_acl, sizeof(struct hx_ioc_eq_acl));
	if(!ret)
	{
		struct hx_ioc_eq_acl *head = stru_acl.next, *next;;
		while(head)
		{
			next = head->next;
			free(head);
			head = next;
		}

	}

	__report(ret);
	return ret;
}

int _iocs_eq_sipuri_acl(int tID, char **arg)
{
	int ret = -1;

	if(__arglen(arg) != 3)
	{
		xeLOG_ERR("ARG ERROR!!! ARG=ACL METHOD ADDRESS");
		__report(EARG);
		return -1;
	}
	struct hx_ioc_eq_acl stru_acl;

	bzero(&stru_acl, sizeof(struct hx_ioc_eq_acl));
	stru_acl.acl = atoi(arg[0]);
	stru_acl.method = atoi(arg[1]);
	strcpy(stru_acl.addr, arg[2]);
	ret = hx_ioctl(tID, HX_IOCS_EQ_SIPURI_ACL, &stru_acl, sizeof(struct hx_ioc_eq_acl));

	__report(ret);
	return ret;
}

int _iocg_eq_equipment_id(int tID, char **arg)
{
	int ret = -1;

	int eID;

	ret = hx_ioctl(tID, HX_IOCG_EQ_EQUIPMENT_ID, &eID, sizeof(int));

	__report(ret);
	return ret;
}

int _iocs_eq_equipment_id(int tID, char **arg)
{
	int ret = -1;

	int eID = 0;

	if(__arglen(arg) != 1)
	{
		xeLOG_ERR("ARG ERROR!!! ARG=[eID]");
		return -1;
	}
	eID = atoi(arg[0]);
	ret = hx_ioctl(tID, HX_IOCS_EQ_EQUIPMENT_ID, &eID, sizeof(int));

	__report(ret);
	return ret;
}


int _iocs_eq_commit(int tID, char **arg)
{
	int ret = -1;

	if(__arglen(arg) != 1)
	{
		__report(EARG);
		return -1;
	}
	int opt = atoi(arg[0]);

	ret = hx_ioctl(tID, HX_IOCS_EQ_COMMIT, &opt, sizeof(int));

	__report(ret);
	return ret;
}

int _iocg_eq_ktask(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_eq_ktask ktask;

	bzero(&ktask, sizeof(ktask));
	ret = hx_ioctl(tID, HX_IOCG_EQ_KTASK, &ktask, sizeof(ktask));
	if(!ret)
	{
		struct hx_ioc_eq_ktask *head = ktask.next, *next;

		while(head)
		{
			next = head->next;
			free(head);
			head = next;
		}
	}

	__report(ret);
	return ret;
}

/*halt a kinescope task by TID*/
int _iocs_eq_ktask(int tID, char **arg)
{
	int ret = -1;

	int argc = __arglen(arg);

	if(!argc)
	{
		xeLOG_ERR("ARG ERROR!!! ARG=TID");
		__report(EARG);
		return -1;
	}
	char TID[128];

	bzero(TID, sizeof(TID));
	int i;

	for(i = 0; i < argc - 1; i++)	//we allow space in argument
	{
		strcat(TID, arg[i]);
		strcat(TID, " ");
	}
	strcat(TID, arg[argc - 1]);

	struct hx_ioc_eq_ktask ktask;

	bzero(&ktask, sizeof(ktask));
//  strcpy(ktask.TID,"C0-T-FROM-\"2009-03-11 00:00:01\"-TO-\"2012-03-10 00:00:01\"_69");
	strcpy(ktask.TID, TID);
	ret = hx_ioctl(tID, HX_IOCS_EQ_KTASK, &ktask, sizeof(ktask));
	__report(ret);
	return ret;
}

int _iocg_eq_stask(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_eq_stask stask;

	bzero(&stask, sizeof(stask));
	ret = hx_ioctl(tID, HX_IOCG_EQ_STASK, &stask, sizeof(stask));
	if(!ret)
	{
		struct hx_ioc_eq_stask *head = stask.next, *next;

		while(head)
		{
			next = head->next;
			free(head);
			head = next;
		}
	}

	__report(ret);
	return ret;
}

/*halt a live stream task by TID*/
int _iocs_eq_stask(int tID, char **arg)
{
	int ret = -1;

	if(__arglen(arg) != 2)
	{
		xeLOG_ERR("Usage: ARG=chaID TID!!!");
		__report(EARG);
		return -1;
	}
	struct hx_ioc_eq_stask stask;

	bzero(&stask, sizeof(stask));
	stask.ChaID = atoi(arg[0]);
	strcpy(stask.TID, arg[1]);
	ret = hx_ioctl(tID, HX_IOCS_EQ_STASK, &stask, sizeof(stask));

	__report(ret);
	return ret;
}


int _iocg_eq_logserver(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_eq_logserver logsrv;

	bzero(&logsrv, sizeof(logsrv));
	ret = hx_ioctl(tID, HX_IOCG_EQ_LOGSERVER, &logsrv, sizeof(logsrv));

	__report(ret);
	return ret;
}

int _iocs_eq_logserver(int tID, char **arg)
{
	int ret = -1;

	if(__arglen(arg) != 3)
	{
		xeLOG_ERR("ARG ERROR!!! ARG=srvIP srvPort level");
		__report(EARG);
		return -1;
	}
	struct hx_ioc_eq_logserver logsrv;

	bzero(&logsrv, sizeof(logsrv));
	logsrv.status = 1;
	logsrv.srvIP = inet_addr(arg[0]);
	logsrv.srvPort = atoi(arg[1]);
	logsrv.level = atoi(arg[2]);
	ret = hx_ioctl(tID, HX_IOCS_EQ_LOGSERVER, &logsrv, sizeof(logsrv));

	__report(ret);
	return ret;
}

int _iocg_eq_sw_version(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_eq_swver swver;

	bzero(&swver, sizeof(swver));
	ret = hx_ioctl(tID, HX_IOCG_EQ_SW_VERSION, &swver, sizeof(swver));

	__report(ret);
	return ret;
}

int _iocs_eq_update(int tID, char **arg)
{
	int ret = -1;

	if(__arglen(arg) != 2)
	{
		xeLOG_ERR("ARG ERROR!!! ARG=fname ftype");
		__report(EARG);
		return -1;
	}
	struct hx_ioc_eq_update eupdate;

	int ftype;

	bzero(&eupdate, sizeof(eupdate));
	if(!strcmp(arg[1], "linux_kernel"))
		ftype = HX_UPDATE_FTYPE_LINUX_KERNEL;
	else if(!strcmp(arg[1], "ramdisk"))
		ftype = HX_UPDATE_FTYPE_RAMDISK;
	else if(!strcmp(arg[1], "jffs2"))
		ftype = HX_UPDATE_FTYPE_JFFS2;
	else
	{
		xeLOG_ERR("Unknown type!!!");
		return -1;
	}
	struct stat fstat;

	bzero(&fstat, sizeof(fstat));
	int fd;

	char *fbp = NULL;

	ret = lstat(arg[0], &fstat);
	if(ret == -1)
	{
		xeLOG_ERR("lstat ERROR!!! errno=%d strerror=%s", errno, strerror(errno));
		goto err_out;
	}
	eupdate.flen = fstat.st_size;
	eupdate.ftype = ftype;

	fbp = calloc(1, eupdate.flen);
	if(fbp == NULL)
	{
		goto err_out;
	}

	fd = open(arg[0], O_RDONLY);
	if(fd == -1)
	{
		xeLOG_ERR("open ERROR!!!");
		goto err_out;
	}

	ret = read(fd, fbp, eupdate.flen);
	if(ret != eupdate.flen)
		goto err_out;
	close(fd);

	register unsigned long sum = 0;

	unsigned long *source = (unsigned long *)fbp;

	int count = eupdate.flen;

	while(count > 1)
	{
		sum += *source++;
		count -= 4;
	}
	eupdate.checksum = ~sum;
	ret = hx_ioctl(tID, HX_IOCS_EQ_UPDATE, &eupdate, sizeof(eupdate));
	free(fbp);
	__report(ret);
	return ret;
  err_out:
	__report(EARG);
	return -1;
}

int _iocg_eq_gauuid(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_eq_GAUUID gau;

	bzero(&gau, sizeof(gau));
	ret = hx_ioctl(tID, HX_IOCG_EQ_GAUUID, &gau, sizeof(gau));

	__report(ret);
	return ret;
}

int _iocs_eq_gauuid(int tID, char **arg)
{
	int ret = -1;

	if(__arglen(arg) != 4)
	{
		xeLOG_ERR("ARG ERROR!!! ARG=government industry category seq");
		__report(EARG);
		return -1;
	}
	struct hx_ioc_eq_GAUUID gau;

	bzero(&gau, sizeof(gau));
	strcpy(gau.government, arg[0]);
	strcpy(gau.industry, arg[1]);
	strcpy(gau.category, arg[2]);
	strcpy(gau.seq, arg[3]);
	ret = hx_ioctl(tID, HX_IOCS_EQ_GAUUID, &gau, sizeof(gau));

	__report(ret);
	return ret;
}

int _iocg_eq_can_index(int tID, char **arg)
{
	int index;
	int ret=-1;
	ret=hx_ioctl(tID, HX_IOCG_EQ_CAN_INDEX, &index, sizeof(int));
	if (ret==0) {
		DBG("get can success.\n");
		DBG("can index: %d\n", index);
	} else {
		xeLOG_ERR("get can fail\n");
	}

	__report(ret);
	return ret;
}

int _iocs_eq_can_index(int tID, char **arg)
{
	int ret = -1;
	int index;
	if (__arglen(arg) != 1) {
		xeLOG_ERR("ARG ERROR!!!");
		__report(EARG);
		return -1;
	}

	index=atoi(arg[0]);
	if(index>=0 || index<10)
	{
		ret=hx_ioctl(tID, HX_IOCS_EQ_CAN_INDEX, &index, sizeof(int));
		if (ret==0) {
			DBG("set can success\n");
		} else {
			xeLOG_ERR("set can fail\n");
		}
	}else{
		return -1;
	}

	__report(ret);
	return ret;
}

int _iocg_eq_rw_num(int tID, char **arg)
{
	int ret=-1;
	int num;
	ret=hx_ioctl(tID, HX_IOCG_EQ_RW_NUM, &num, sizeof(int));
	if (ret==0) {
		DBG("get roadway num supported success\n");
		DBG("rw_num: %d\n", num);
	} else {
		xeLOG_ERR("get roadway num supported fail\n");
	}
	__report(ret);
	return ret;
}

int _iocs_eq_rw_num(int tID, char **arg)
{
	int ret=-1;
	int num;
	num=atoi(arg[0]);
	if(num>=1 || num<=4)
	{
		ret=hx_ioctl(tID, HX_IOCS_EQ_RW_NUM, &num, sizeof(int));
		if (ret==0) {
			DBG("set roadway num supported success\n");
		} else {
			xeLOG_ERR("set roadway num supported fail\n");
		}
	}
	__report(ret);
	return ret;
}

// add by wangtao
int _iocg_eq_video_winnum(int tID, char **arg)
{
	int ret=-1;

	struct hx_ioc_eq_video_winnum winnum;
	bzero(&winnum, sizeof(winnum));
	// winnum.vid_num = atoi(arg[0]); //vid_num must be 0
	ret = hx_ioctl(tID, HX_IOCG_EQ_VIDEO_WINNUM, &winnum, sizeof(winnum));
	
	if (ret==0) {
		DBG("get video output windows number success\n");	
		DBG("vid_num: %d; resolution: %s; winnum: %d; channels: %s; status: %s\n", 
			winnum.vid_num, winnum.resolution, winnum.winnum, winnum.channels, winnum.status);		
	} else {
		xeLOG_ERR("get video output windows number fail\n");
	}
	__report(ret);
	return ret;
}

int _iocs_eq_video_winnum(int tID, char **arg)
{
	int ret=-1;

	struct hx_ioc_eq_video_winnum winnum;

	
	bzero(&winnum, sizeof(winnum));
	
	winnum.winnum = atoi(arg[0]);
	strcpy(winnum.channels, arg[1]);
	ret = hx_ioctl(tID, HX_IOCS_EQ_VIDEO_WINNUM, &winnum, sizeof(winnum));
	if (ret==0) {
		DBG("set video output windows number success\n");
	} else {
		xeLOG_ERR("set video output windows number fail\n");
	}

	__report(ret);
	return ret;
}

int _iocg_eq_video_resolution(int tID, char **arg)
{
	int ret=-1;

	struct hx_ioc_eq_video_winnum winnum;
	bzero(&winnum, sizeof(winnum));
	ret = hx_ioctl(tID, HX_IOCG_EQ_VIDEO_RESOLUTION, &winnum, sizeof(winnum));
	
	if (ret==0) {
		DBG("get video ouput windows resolution success\n");
		DBG("vid_num: %d; resolution: %s; winnum: %d; channels: %s; status: %s\n", 
			winnum.vid_num, winnum.resolution, winnum.winnum, winnum.channels, winnum.status);
	} else {
		xeLOG_ERR("get video ouput windows resolution fail\n");
	}
	__report(ret);
	return ret;
}

int _iocs_eq_video_resolution(int tID, char **arg)
{
	int ret=-1;
	struct hx_ioc_eq_video_winnum winnum;
	bzero(&winnum, sizeof(winnum));

		strcpy(winnum.resolution, arg[0]);
		ret = hx_ioctl(tID, HX_IOCS_EQ_VIDEO_RESOLUTION, &winnum, sizeof(winnum));
		if (ret==0) {
			DBG("set video output windows resolution success\n");
		} else {
			xeLOG_ERR("set video output windows resolution fail\n");
		}

	__report(ret);
	return ret;
}

int _iocg_eq_video_status(int tID, char **arg)
{
	int ret=-1;

	struct hx_ioc_eq_video_winnum winnum;
	bzero(&winnum, sizeof(winnum));
	ret = hx_ioctl(tID, HX_IOCG_EQ_VIDEO_STATUS, &winnum, sizeof(winnum));
	
	if (ret==0) {
		DBG("get video output windows status success\n");
		DBG("vid_num: %d; resolution: %s; winnum: %d; channels: %s; status: %s\n", 
			winnum.vid_num, winnum.resolution, winnum.winnum, winnum.channels, winnum.status);
	} else {
		xeLOG_ERR("get video output windows status fail\n");
	}
	__report(ret);
	return ret;
}

int _iocs_eq_video_status(int tID, char **arg)
{
	int ret=-1;
	int num;
	struct hx_ioc_eq_video_winnum winnum;
	bzero(&winnum, sizeof(winnum));

	num=atoi(arg[0]);
	if(num>=1 || num<=16)
	{
		winnum.vid_num = num;
		strcpy(winnum.status, arg[1]);
		ret = hx_ioctl(tID, HX_IOCS_EQ_VIDEO_STATUS, &winnum, sizeof(winnum));
		if (ret==0) {
			report_LOG("================================================");
			report_LOG("\tenable video success");

			DBG("set video output windows status success\n");
		} else {
			report_LOG("================================================");
			report_LOG("\tenable video fail");

			xeLOG_ERR("set video output windows status fail\n");
		}
	}
	__report(ret);
	return ret;
}

int _iocg_eq_ntp(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_eq_ntp ntp;

	bzero(&ntp, sizeof(ntp));
	ret = hx_ioctl(tID, HX_IOCG_EQ_NTP, &ntp, sizeof(ntp));
	if(!ret){
		DBG("get ntp success\n");
		DBG("status: %d; ipaddr: %d.%d.%d.%d\n", ntp.status, 
			ntp.ipaddr & 0x000000ff, (ntp.ipaddr >> 8) & 0x000000ff, 
			(ntp.ipaddr >> 16) & 0x000000ff, (ntp.ipaddr >> 24) & 0x000000ff);
	}else{
		xeLOG_ERR("get ntp fail!");
	}

	__report(ret);
	return ret;
}



int _iocs_eq_ntp(int tID, char **arg)
{
	int ret = -1;

	/*if(__arglen(arg) != 2)
	{
		xeLOG_ERR("Usage: ARG=!!!");
		__report(EARG);
		return -1;
	}*/
	struct hx_ioc_eq_ntp ntp;
	int ip = 0;
	int i = 0;
	// int ips[4] = {0,0,0,0};
	char* res = NULL;

	res = (char*)strtok(arg[1],".");
	while (res != NULL){
		// ips[i++] = atoi(res);
		ip = ip | (atoi(res) << i*8);
		res = (char*)strtok(NULL,".");
		i++;
	}


	bzero(&ntp, sizeof(ntp));
	ntp.status = atoi(arg[0]);
	ntp.ipaddr = ip;
	DBG("ip set to : %s(%d)\n",arg[1],ip);
	ret = hx_ioctl(tID, HX_IOCS_EQ_NTP, &ntp, sizeof(ntp));
	if (ret==0) {
		DBG("set ntp success\n");
	} else {
		xeLOG_ERR("set ntp fail\n");
	}

	__report(ret);
	return ret;
}

int _iocg_eq_video_windows_4_de(int tID, char **arg)
{
	int ret=-1;

	struct hx_ioc_eq_video_windows_4_de windows;
	bzero(&windows, sizeof(windows));
	ret = hx_ioctl(tID, HX_IOCG_EQ_VIDEO_WINDOWS_4_DE, &windows, sizeof(windows));
	
	if (ret==0) {
		DBG("get windows & window's ChaID_Main & resolution success\n");
		DBG("ChaID: %d; number: %d\n", windows.ChaID,windows.number);
	} else {
		xeLOG_ERR("get windows & window's ChaID_Main & resolution fail\n");
	}
	__report(ret);
	return ret;
}

/*encode channel function*/
int _iocg_en_name(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_en_name stru_name;

	bzero(&stru_name, sizeof(stru_name));
	ret = hx_ioctl(tID, HX_IOCG_EN_NAME, &stru_name, sizeof(stru_name));
	if(ret==0)
	{
		DBG("get encode channel name success\n");
	}else{
		xeLOG_ERR("get encode channel name failed\n");
	}

	__report(ret);
	return ret;
}

int _iocs_en_name(int tID, char **arg)
{
	int ret = -1;

	if(__arglen(arg) != 1)
	{
		xeLOG_ERR("Usage: ARG=hostname");
		__report(EARG);
		return -1;
	}
	struct hx_ioc_en_name stru_name;

	bzero(&stru_name, sizeof(stru_name));
	strcpy(stru_name.name, arg[0]);
	ret = hx_ioctl(tID, HX_IOCS_EN_NAME, &stru_name, sizeof(stru_name));
	if (ret==0) {
		DBG("set encode channel name success\n");
	} else {
		xeLOG_ERR("set encode channel name failed\n");
	}

	__report(ret);
	return ret;
}

int _iocs_en_default(int tID, char **arg)
{
	int ret = -1;

	if(__arglen(arg) != 1)
	{
		__report(EARG);
		return -1;
	}
	int opt = atoi(arg[0]);

	ret = hx_ioctl(tID, HX_IOCS_EN_DEFAULT, &opt, sizeof(int));

	__report(ret);
	return ret;
}

int _iocg_en_video_encoder(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_en_venc stru_venc;

	memset(&stru_venc,0,sizeof(stru_venc));
	if(!strcmp(arg[0],"main"))
			stru_venc.stype=STYPE_MAIN;
	else if(!strcmp(arg[0],"subA"))
			stru_venc.stype=STYPE_SUB_A;

	ret = hx_ioctl(tID, HX_IOCG_EN_VIDEO_ENCODER, &stru_venc, sizeof(stru_venc));

	__report(ret);
	return ret;
}

int _iocg_en_video_size(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_en_vsize vsize;

	memset(&vsize, 0, sizeof(vsize));
	if (!strcmp(arg[0], "main")){
		vsize.stype=STYPE_MAIN;
	}else if (!strcmp(arg[0], "subA")){
		vsize.stype=STYPE_SUB_A;
	}else if (!strcmp(arg[0], "subB")){
			vsize.stype=STYPE_SUB_B;
	}else if (!strcmp(arg[0], "subC")){
			vsize.stype=STYPE_SUB_C;
	}else if (!strcmp(arg[0], "subD")){
			vsize.stype=STYPE_SUB_D;
	}else if (!strcmp(arg[0], "subE")){
			vsize.stype=STYPE_SUB_E;
	}else{
		xeLOG_ERR("stype must be main|subA|subB|subC|subD|subE");
	}

	ret = hx_ioctl(tID, HX_IOCG_EN_VIDEO_SIZE, &vsize, sizeof(vsize));
	__report(ret);
	return ret;
}

int _iocg_en_video_bitrate(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_bitrate bitrate;

	memset(&bitrate, 0, sizeof(bitrate));
	if (!strcmp(arg[0], "main")){
		bitrate.stype=STYPE_MAIN;
	}else if (!strcmp(arg[0], "subA")){
		bitrate.stype=STYPE_SUB_A;
	}else if (!strcmp(arg[0], "subB")){
			bitrate.stype=STYPE_SUB_B;
	}else if (!strcmp(arg[0], "subC")){
			bitrate.stype=STYPE_SUB_C;
	}else if (!strcmp(arg[0], "subD")){
			bitrate.stype=STYPE_SUB_D;
	}else if (!strcmp(arg[0], "subE")){
			bitrate.stype=STYPE_SUB_E;
	}else{
		xeLOG_ERR("stype must be main|subA|subB|subC|subD|subE");
	}

	ret = hx_ioctl(tID, HX_IOCG_EN_VIDEO_BITRATE, &bitrate, sizeof(bitrate));

	__report(ret);
	return ret;
}

int _iocs_en_video_bitrate(int tID, char **arg)
{
	int ret = -1;

	if(__arglen(arg) != 2)
	{
		__report(EARG);
		return -1;
	}
	struct hx_ioc_bitrate bitrate;
	memset(&bitrate,0,sizeof(bitrate));
	if (!strcmp(arg[0], "LOW")){
		bitrate.level=HX_VIDEO_BITRATE_LOW;
	}else if (!strcmp(arg[0], "MIDDLE")){
		bitrate.level=HX_VIDEO_BITRATE_MIDDLE;
	}else if (!strcmp(arg[0], "HIGH")){
		bitrate.level=HX_VIDEO_BITRATE_HIGH;
	}else if (!strcmp(arg[0], "GOOD")){
		bitrate.level=HX_VIDEO_BITRATE_GOOD;
	}else{
		printf("arg is unknown\n");
	}

	if (!strcmp(arg[1], "main")){
		bitrate.stype=STYPE_MAIN;
	} else if (!strcmp(arg[1], "subA")) {
		bitrate.stype = STYPE_SUB_A;
	} else if (!strcmp(arg[1], "subB")) {
		bitrate.stype = STYPE_SUB_B;
	} else if (!strcmp(arg[1], "subC")) {
		bitrate.stype = STYPE_SUB_C;
	} else if (!strcmp(arg[1], "subD")) {
		bitrate.stype = STYPE_SUB_D;
	} else if (!strcmp(arg[1], "subE")) {
		bitrate.stype = STYPE_SUB_E;
	} else {
		xeLOG_ERR("stype must be main|subA|subB|subC|subD|subE");
	}

	ret = hx_ioctl(tID, HX_IOCS_EN_VIDEO_BITRATE, &bitrate, sizeof(bitrate));

	__report(ret);
	return ret;
}

int _iocg_en_video_ratio(int tID, char **arg) {
	int ret = -1;

	struct hx_ioc_en_ratio ratio;

	memset(&ratio, 0, sizeof(ratio));

	if (!strcmp(arg[0], "main")) {
		ratio.stype = STYPE_MAIN;
	} else if (!strcmp(arg[0], "subA")) {
		ratio.stype = STYPE_SUB_A;
	} else if (!strcmp(arg[0], "subB")) {
		ratio.stype = STYPE_SUB_B;
	} else if (!strcmp(arg[0], "subC")) {
		ratio.stype = STYPE_SUB_C;
	} else if (!strcmp(arg[0], "subD")) {
		ratio.stype = STYPE_SUB_D;
	} else if (!strcmp(arg[0], "subE")) {
		ratio.stype = STYPE_SUB_E;
	} else {
		xeLOG_ERR("stype must be main|subA|subB|subC|subD|subE");
	}

	ret = hx_ioctl(tID, HX_IOCG_EN_VIDEO_RATIO, &ratio, sizeof(ratio));

	__report(ret);
	return ret;
}

int _iocs_en_video_ratio(int tID, char **arg) {
	int ret = -1;

	struct hx_ioc_en_ratio ratio;

	memset(&ratio, 0, sizeof(ratio));

	if (!strcmp(arg[0], "main")) {
		ratio.stype = STYPE_MAIN;
	} else if (!strcmp(arg[0], "subA")) {
		ratio.stype = STYPE_SUB_A;
	} else if (!strcmp(arg[0], "subB")) {
		ratio.stype = STYPE_SUB_B;
	} else if (!strcmp(arg[0], "subC")) {
		ratio.stype = STYPE_SUB_C;
	} else if (!strcmp(arg[0], "subD")) {
		ratio.stype = STYPE_SUB_D;
	} else if (!strcmp(arg[0], "subE")) {
		ratio.stype = STYPE_SUB_E;
	} else {
		xeLOG_ERR("stype must be main|subA|subB|subC|subD|subE");
	}
	ratio.ratio=atoi(arg[1]);

	ret = hx_ioctl(tID, HX_IOCS_EN_VIDEO_RATIO, &ratio, sizeof(ratio));

	__report(ret);
	return ret;
}

int _iocg_en_video_btype(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_en_bitrate_type btype;

	memset(&btype, 0, sizeof(btype));

	if (!strcmp(arg[0], "main")){
		btype.stype=STYPE_MAIN;
	}else if (!strcmp(arg[0], "subA")){
		btype.stype=STYPE_SUB_A;
	}else if (!strcmp(arg[0], "subB")){
		btype.stype=STYPE_SUB_B;
	}else if (!strcmp(arg[0], "subC")){
		btype.stype=STYPE_SUB_C;
	}else if (!strcmp(arg[0], "subD")){
		btype.stype=STYPE_SUB_D;
	}else if (!strcmp(arg[0], "subE")){
		btype.stype=STYPE_SUB_E;
	}else{
		xeLOG_ERR("stype must be main|subA|subB|subC|subD|subE");
	}

	ret = hx_ioctl(tID, HX_IOCG_EN_VIDEO_BTYPE, &btype, sizeof(btype));
	if(ret==0)
	{
		printf("HX_IOCG_EN_VIDEO_BTYPE SUCCESS\n!");
	}else{
		printf("HX_IOCG_EN_VIDEO_BTYPE FAIL\n!");
	}

	__report(ret);
	return ret;
}

int _iocs_en_video_btype(int tID, char **arg)
{
	int ret = -1;

	if(__arglen(arg) != 2)
	{
		__report(EARG);
		return -1;
	}
	struct hx_ioc_en_bitrate_type btype;
	memset(&btype,0,sizeof(btype));

	if (!strcmp(arg[0], "main")){
		btype.stype=STYPE_MAIN;
	} else if (!strcmp(arg[0], "subA")) {
		btype.stype = STYPE_SUB_A;
	} else if (!strcmp(arg[0], "subB")) {
		btype.stype = STYPE_SUB_B;
	} else if (!strcmp(arg[0], "subC")) {
		btype.stype = STYPE_SUB_C;
	} else if (!strcmp(arg[0], "subD")) {
		btype.stype = STYPE_SUB_D;
	} else if (!strcmp(arg[0], "subE")) {
		btype.stype = STYPE_SUB_E;
	} else {
		xeLOG_ERR("stype must be main|subA|subB|subC|subD|subE");
	}

	if(!strcmp(arg[1],"VBR"))
	{
		btype.btype=HX_VIDEO_BITRATE_TYPE_VBR;
	}else if(!strcmp(arg[1],"CBR")){
		btype.btype=HX_VIDEO_BITRATE_TYPE_CBR;
	}else{
		btype.btype=HX_VIDEO_BITRATE_TYPE_UNKNOWN;
	}
	ret = hx_ioctl(tID, HX_IOCS_EN_VIDEO_BTYPE, &btype, sizeof(btype));
	if (ret == 0) {
		printf("HX_IOCS_EN_VIDEO_BTYPE SUCCESS\n!");
	} else {
		printf("HX_IOCS_EN_VIDEO_BTYPE FAIL\n!");
	}

	__report(ret);
	return ret;
}

int _iocg_en_video_framerate(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_en_frate frate;
	memset(&frate, 0, sizeof(frate));

	if (!strcmp(arg[0], "main")){
		frate.stype=STYPE_MAIN;
	}else if (!strcmp(arg[0], "subA")){
		frate.stype=STYPE_SUB_A;
	}else if (!strcmp(arg[0], "subB")){
			frate.stype=STYPE_SUB_B;
	}else if (!strcmp(arg[0], "subC")){
			frate.stype=STYPE_SUB_C;
	}else if (!strcmp(arg[0], "subD")){
			frate.stype=STYPE_SUB_D;
	}else if (!strcmp(arg[0], "subE")){
			frate.stype=STYPE_SUB_E;
	}else{
		xeLOG_ERR("stype must be main|subA|subB|subC|subD|subE");
	}

	ret = hx_ioctl(tID, HX_IOCG_EN_VIDEO_FRAMERATE, &frate, sizeof(frate));

	__report(ret);
	return ret;
}

int _iocs_en_video_framerate(int tID, char **arg)
{
	int ret = -1;
	if (__arglen(arg) != 2) {
		__report(EARG);
		return -1;
	}
	struct hx_ioc_en_frate frate;

	memset(&frate, 0, sizeof(frate));
	frate.frate=atoi(arg[0]);
	if (!strcmp(arg[1], "main")){
		frate.stype = STYPE_MAIN;
	} else if (!strcmp(arg[1], "subA")) {
		frate.stype = STYPE_SUB_A;
	} else if (!strcmp(arg[0], "subB")) {
		frate.stype = STYPE_SUB_B;
	} else if (!strcmp(arg[0], "subC")) {
		frate.stype = STYPE_SUB_C;
	} else if (!strcmp(arg[0], "subD")) {
		frate.stype = STYPE_SUB_D;
	} else if (!strcmp(arg[0], "subE")) {
		frate.stype = STYPE_SUB_E;
	} else {
		xeLOG_ERR("stype must be main|subA|subB|subC|subD|subE");
	}

	ret = hx_ioctl(tID, HX_IOCS_EN_VIDEO_FRAMERATE, &frate, sizeof(frate));

	__report(ret);
	return ret;
}

int _iocg_en_video_iframeinterval(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_en_ifi ifi;

	memset(&ifi,0,sizeof(ifi));
	if (!strcmp(arg[0], "main")){
		ifi.stype=STYPE_MAIN;
	}else if (!strcmp(arg[0], "subA")){
		ifi.stype=STYPE_SUB_A;
	}else if (!strcmp(arg[0], "subB")){
		ifi.stype=STYPE_SUB_B;
	}else if (!strcmp(arg[0], "subC")){
		ifi.stype=STYPE_SUB_C;
	}else if (!strcmp(arg[0], "subD")){
		ifi.stype=STYPE_SUB_D;
	}else if (!strcmp(arg[0], "subE")){
		ifi.stype=STYPE_SUB_E;
	}else{
		xeLOG_ERR("stype must be main|subA|subB|subC|subD|subE");
	}
	ret = hx_ioctl(tID, HX_IOCG_EN_VIDEO_IFRAMEINTERVAL, &ifi, sizeof(ifi));

	__report(ret);
	return ret;
}

int _iocs_en_video_iframeinterval(int tID, char **arg)
{
	int ret = -1;

	if(__arglen(arg) != 2)
	{
		__report(EARG);
		return -1;
	}
	struct hx_ioc_en_ifi ifi;

	memset(&ifi,0,sizeof(ifi));
	ifi.ifi=atoi(arg[0]);
	if (!strcmp(arg[1], "main")) {
		ifi.stype = STYPE_MAIN;
	} else if (!strcmp(arg[1], "subA")) {
		ifi.stype = STYPE_SUB_A;
	} else if (!strcmp(arg[1], "subB")) {
		ifi.stype = STYPE_SUB_B;
	} else if (!strcmp(arg[1], "subC")) {
		ifi.stype = STYPE_SUB_C;
	} else if (!strcmp(arg[1], "subD")) {
		ifi.stype = STYPE_SUB_D;
	} else if (!strcmp(arg[1], "subE")) {
		ifi.stype = STYPE_SUB_E;
	} else {
		xeLOG_ERR("stype must be main|subA|subB|subC|subD|subE");
	}

	ret = hx_ioctl(tID, HX_IOCS_EN_VIDEO_IFRAMEINTERVAL, &ifi, sizeof(ifi));

	__report(ret);
	return ret;
}

int _iocg_en_video_color(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_vcolor vcolor;

	bzero(&vcolor, sizeof(struct hx_ioc_vcolor));
	ret = hx_ioctl(tID, HX_IOCG_EN_VIDEO_COLOR, &vcolor, sizeof(struct hx_ioc_vcolor));

	__report(ret);
	return ret;
}

int _iocs_en_video_color(int tID, char **arg)
{
	int ret = -1;

	if(__arglen(arg) != 4)
	{
		__report(EARG);
		return -1;
	}
	struct hx_ioc_vcolor vcolor;

	bzero(&vcolor, sizeof(struct hx_ioc_vcolor));
	vcolor.brightness = atoi(arg[0]);
	vcolor.contrast = atoi(arg[1]);
	vcolor.saturation = atoi(arg[2]);
	vcolor.hue = atoi(arg[3]);
	ret = hx_ioctl(tID, HX_IOCS_EN_VIDEO_COLOR, &vcolor, sizeof(struct hx_ioc_vcolor));

	__report(ret);
	return ret;
}

int _iocg_en_video_osd(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_osd osd;

	bzero(&osd, sizeof(struct hx_ioc_osd));
	ret = hx_ioctl(tID, HX_IOCG_EN_VIDEO_OSD, &osd, sizeof(struct hx_ioc_osd));

	__report(ret);
	return ret;
}

int _iocs_en_video_osd(int tID, char **arg)
{
	int ret = -1;

	if(__arglen(arg) != 7)
	{
		__report(EARG);
		return -1;
	}
	struct hx_ioc_osd osd;

	bzero(&osd, sizeof(struct hx_ioc_osd));
	osd.ID = atoi(arg[0]);
	osd.status = atoi(arg[1]);
	osd.type = atoi(arg[2]);
	osd.color = atoi(arg[3]);
	osd.xpos = atoi(arg[4]);
	osd.ypos = atoi(arg[5]);
	strcpy(osd.text, arg[6]);
	ret = hx_ioctl(tID, HX_IOCS_EN_VIDEO_OSD, &osd, sizeof(struct hx_ioc_osd));

	__report(ret);
	return ret;
}

int _iocg_en_audio_encoder(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_en_aenc aenc;

	bzero(&aenc, sizeof(struct hx_ioc_en_aenc));
	if (!strcmp(arg[0], "main")){
		aenc.stype=STYPE_MAIN;
	}else if (!strcmp(arg[0], "subA")){
		aenc.stype=STYPE_SUB_A;
	}else if (!strcmp(arg[0], "subB")){
		aenc.stype=STYPE_SUB_B;
	}else if (!strcmp(arg[0], "subC")){
		aenc.stype=STYPE_SUB_C;
	}else if (!strcmp(arg[0], "subD")){
		aenc.stype=STYPE_SUB_D;
	}else if (!strcmp(arg[0], "subE")){
		aenc.stype=STYPE_SUB_E;
	}else{
		xeLOG_ERR("stype must be main|subA|subB|subC|subD|subE");
	}

	ret = hx_ioctl(tID, HX_IOCG_EN_AUDIO_ENCODER, &aenc, sizeof(struct hx_ioc_en_aenc));

	__report(ret);
	return ret;
}

int _iocg_en_mux(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_en_mux mux;

	bzero(&mux, sizeof(struct hx_ioc_en_mux));
	ret = hx_ioctl(tID, HX_IOCG_EN_MUX, &mux, sizeof(struct hx_ioc_en_mux));

	__report(ret);
	return ret;
}


int _iocg_en_multicast(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_mcast mcast;

	bzero(&mcast, sizeof(struct hx_ioc_mcast));
	ret = hx_ioctl(tID, HX_IOCG_EN_MULTICAST, &mcast, sizeof(struct hx_ioc_mcast));

	__report(ret);
	return ret;
}

int _iocs_en_multicast(int tID, char **arg)
{
	int ret = -1;

	if(__arglen(arg) != 5)
	{
		__report(EARG);
		return -1;
	}
	struct hx_ioc_mcast mcast;

	bzero(&mcast, sizeof(struct hx_ioc_mcast));
	mcast.status = atoi(arg[0]);
	mcast.ipaddr = inet_addr(arg[1]);
	mcast.port = atoi(arg[2]);
	mcast.ttl = atoi(arg[3]);
	mcast.pktsize = atoi(arg[4]);
	ret = hx_ioctl(tID, HX_IOCS_EN_MULTICAST, &mcast, sizeof(struct hx_ioc_mcast));

	__report(ret);
	return ret;
}

int _iocg_en_ptz(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_en_ptz ptz;

	bzero(&ptz, sizeof(struct hx_ioc_en_ptz));
	ret = hx_ioctl(tID, HX_IOCG_EN_PTZ, &ptz, sizeof(struct hx_ioc_en_ptz));

	__report(ret);
	return ret;
}

int _iocs_en_ptz(int tID, char **arg)
{
	int ret = -1;

	if(__arglen(arg) != 3)
	{
		__report(EARG);
		return -1;
	}
	struct hx_ioc_en_ptz ptz;

	bzero(&ptz, sizeof(struct hx_ioc_en_ptz));
	ptz.status = atoi(arg[0]);
	strcpy(ptz.protocol, arg[1]);
	ptz.addr = atoi(arg[2]);
	ret = hx_ioctl(tID, HX_IOCS_EN_PTZ, &ptz, sizeof(struct hx_ioc_en_ptz));
	__report(ret);
	return ret;
}

int _iocg_en_recwd(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_en_recwd recwd;

	if(__arglen(arg) != 2)
		goto err_out;

	bzero(&recwd, sizeof(struct hx_ioc_en_recwd));
	recwd.wd = atoi(arg[0]);

	ret = hx_ioctl(tID, HX_IOCG_EN_RECWD, &recwd, sizeof(struct hx_ioc_en_recwd));
	if(!ret)
	{

		struct hx_ioc_en_recwd *head , *next;

		head = recwd.next;
		while(head)
		{
			if (head->status) {
				DBG(
						"Recwd: index=%d status=%d keepdays=%d StartTime=%d:%d:%d EndTime=%d:%d:%d",
						head->idx, head->status, head->keepdays, head->st_hour,
						head->st_min, head->st_sec, head->et_hour,
						head->et_min, head->et_sec);
			}else{
				printf("idx=%d disable\n",head->idx);
			}
			head = head->next;
		}

		head = recwd.next;
		while(head)
		{
			next = head->next;
			free(head);
			head = next;
		}
	}

	__report(ret);
	return ret;
  err_out:
	xeLOG_ERR("ARG ERROR!!! Enter weekday,Sun=0");
	return 0;
}

int _iocs_en_recwd(int tID, char **arg) {
	int ret = -1;

	if (__arglen(arg) != 5) {
		__report(EARG);
		return -1;
	}
	struct hx_ioc_en_recwd recwd;

	bzero(&recwd, sizeof(recwd));

	if (atoi(arg[0]) >= 0 && atoi(arg[0]) <= 6) {
		recwd.wd = atoi(arg[0]);
	} else {
		printf("wd is [0,6]\n");
		return -1;
	}
	recwd.idx = atoi(arg[1]);
	recwd.status = atoi(arg[2]);
	int ret1, ret2;

	ret1 = sscanf(arg[3], "%d:%d:%d", &recwd.st_hour, &recwd.st_min, &recwd.st_sec);
	ret2 = sscanf(arg[4], "%d:%d:%d", &recwd.et_hour, &recwd.et_min, &recwd.et_sec);
	if (!(ret1 == 3 && ret2 == 3)) {
		xeLOG_ERR("sscanf ERROR!!!");
		return -1;
	}
	recwd.keepdays = 30;
	ret = hx_ioctl(tID, HX_IOCS_EN_RECWD, &recwd, sizeof(recwd));

	if(ret==0)
	{
		DBG("HX_IOCS_EN_RECWD SUCCESS\n");
	}else{
		DBG("HX_IOCS_EN_RECWD SUCCESS\n");
		xeLOG_ERR("HX_IOCS_EN_RECWD FAIL\n");
	}
	__report( ret);
	return ret;
}

int _iocs_en_recwd_dup_2_channels(int tID, char **arg) {
	int ret = -1;

	if (__arglen(arg) != 1) {
		__report(EARG);
		return -1;
	}

	struct hx_ioc_en_recwd_dup_2_channels recwd_dup2_channels;
	memset(&recwd_dup2_channels,0,sizeof(recwd_dup2_channels));

	recwd_dup2_channels.from_ChaID=atoi(arg[0]);
	recwd_dup2_channels.to_channels=(~(1<<atoi(arg[0])))&(~HX_IOC_EN_CHANUM_MASK);

	ret=hx_ioctl(tID,HX_IOCS_EN_RECWD_DUP_2_CHANNELS,&recwd_dup2_channels,sizeof(recwd_dup2_channels));
	if(ret==0)
	{
		DBG("HX_IOCS_EN_RECWD_DUP_2_CHANNELS SUCCES\n");
	}else{
		xeLOG_ERR("HX_IOCS_EN_RECWD_DUP_2_CHANNELS FAIL\n");
	}
	__report(ret);
	return ret;
}

int _iocs_en_rewd_dup_2_weekdays(int tID,char **arg)
{
	int ret = -1i;

	if (__arglen(arg) != 2) {
		__report(EARG);
		return -1;
	}
	struct hx_ioc_en_recwd_dup_2_wdays recwd_dup2_wdays;
	memset(&recwd_dup2_wdays,0,sizeof(recwd_dup2_wdays));

	recwd_dup2_wdays.ChaID=atoi(arg[0]);
	if(atoi(arg[1])>=0 && atoi(arg[1])<=6)
	{
		recwd_dup2_wdays.from_wday=atoi(arg[1]);
	}else{
		printf("from_wday range is [0,6\n");
	}
	recwd_dup2_wdays.to_wdays=(~(1<<atoi(arg[1])))&(~HX_IOC_EN_WDAY_MASK);

	ret = hx_ioctl(tID, HX_IOCS_EN_RECWD_DUP_2_WDAYS, &recwd_dup2_wdays,
			sizeof(recwd_dup2_wdays));
	if (ret == 0) {
		DBG("HX_IOCS_EN_RECWD_DUP_2_WDAYS SUCCES\n");
	} else {
		xeLOG_ERR("HX_IOCS_EN_RECWD_DUP_2_WDAYS FAIL\n");
	}
	__report(ret);
	return ret;

}
int _iocg_en_sub_recwd(int tID,char **arg)
{
	int ret=-1;
	struct hx_ioc_en_sub_recwd recwd;
	memset(&recwd,0,sizeof(recwd));

	if(!strcmp(arg[0],"main"))
	{
		recwd.stype=STYPE_MAIN;
	}else if(!strcmp(arg[0],"subA"))
	{
		recwd.stype=STYPE_SUB_A;
	}else if(!strcmp(arg[0],"subB"))
	{
		recwd.stype=STYPE_SUB_B;
	}else if(!strcmp(arg[0],"subC"))
	{
		recwd.stype=STYPE_SUB_C;
	}else if(!strcmp(arg[0],"subD"))
	{
		recwd.stype=STYPE_SUB_D;
	}else if(!strcmp(arg[0],"subE"))
	{
		recwd.stype=STYPE_SUB_E;
	}else{
		xeLOG_ERR("stype must be main|subA|subB|subC|subD|subE\n");
	}

	ret = hx_ioctl(tID, HX_IOCG_EN_SUB_RECWD, &recwd, sizeof(recwd));
	if (ret == 0) {
		DBG("get sub stream kinescope SUCCESS.\n");
		if (recwd.mode == 2) {
			DBG("duration:%02d_%02d_%02d %02d_%02d_%02d\n", recwd.st_hour,
					recwd.st_min, recwd.st_sec, recwd.et_hour, recwd.et_min,
					recwd.et_sec);
		} else if (recwd.mode == 1) {
			DBG("all day\n");
		} else {
			printf("disable\n");
		}
	} else {
		xeLOG_ERR("get sub stream kinescope FAIL.\n");
	}
	__report(ret);
	return ret;
}

int _iocs_en_sub_recwd(int tID, char **arg) {
	int ret = -1;
	if(__arglen(arg)!=4)
	{
		__report(EARG);
		return -1;
	}

	struct hx_ioc_en_sub_recwd recwd;
	memset(&recwd,0,sizeof(recwd));

	if (!strcmp(arg[0], "main")) {
		recwd.stype = STYPE_MAIN;
	} else if (!strcmp(arg[0], "subA")) {
		recwd.stype = STYPE_SUB_A;
	} else if (!strcmp(arg[0], "subB")) {
		recwd.stype = STYPE_SUB_B;
	} else if (!strcmp(arg[0], "subC")) {
		recwd.stype = STYPE_SUB_C;
	} else if (!strcmp(arg[0], "subD")) {
		recwd.stype = STYPE_SUB_D;
	} else if (!strcmp(arg[0], "subE")) {
		recwd.stype = STYPE_SUB_E;
	} else {
		xeLOG_ERR("stype must be main|subA|subB|subC|subD|subE\n");
	}
	recwd.mode = atoi(arg[1]);
	int ret1,ret2;
	ret1 = sscanf(arg[2], "%d:%d:%d", &recwd.st_hour, &recwd.st_min,
			&recwd.st_sec);
	ret2 = sscanf(arg[3], "%d:%d:%d", &recwd.et_hour, &recwd.et_min,
			&recwd.et_sec);
	if (!(ret1 == 3 && ret2 == 3)) {
		xeLOG_ERR("sscanf ERROR!!!");
		return -1;
	}

	ret = hx_ioctl(tID, HX_IOCS_EN_SUB_RECWD, &recwd, sizeof(recwd));
	if (ret == -1) {
		xeLOG_ERR("set sub stream kinescope FAIL\n");
	} else {
		DBG("set sub stream kinescope SUCCESS.\n");
	}
	__report(ret);
	return ret;
}

int _iocg_en_mdet(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_en_mdet mdet;

	bzero(&mdet, sizeof(struct hx_ioc_en_mdet));
	ret = hx_ioctl(tID, HX_IOCG_EN_MDET, &mdet, sizeof(struct hx_ioc_en_mdet));

	__report(ret);
	return ret;
}

int _iocs_en_mdet(int tID, char **arg)
{
	int ret = -1;

	if(__arglen(arg) != 4)
	{
		__report(EARG);
		return -1;
	}
	struct hx_ioc_en_mdet mdet;

	bzero(&mdet, sizeof(struct hx_ioc_en_mdet));
	/*first get,the set */
	ret = hx_ioctl(tID, HX_IOCG_EN_MDET, &mdet, sizeof(struct hx_ioc_en_mdet));
	if(ret < 0)
	{
		xeLOG_ERR("GET EN_MDET ERROR!!!");
		return -1;
	}
	int row = atoi(arg[1]), col = atoi(arg[2]);

	mdet.status = atoi(arg[0]);
	mdet.row[row].col[col] = atoi(arg[3]);
	ret = hx_ioctl(tID, HX_IOCS_EN_MDET, &mdet, sizeof(struct hx_ioc_en_mdet));
	__report(ret);
	return ret;
}

int _iocg_en_ptz_protocols(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_en_ptz_protocols protos;

	bzero(&protos, sizeof(protos));
	ret = hx_ioctl(tID, HX_IOCG_EN_PTZ_PROTOCOLS, &protos, sizeof(protos));
	if(!ret)
	{
		struct hx_ioc_en_ptz_protocols *tmp = protos.next, *next;

		while(tmp)				//free memory
		{
			next = tmp->next;
			free(tmp);

			tmp = next;
		}
	}

	__report(ret);
	return ret;
}

int _iocg_en_sip(int tID, char **arg)
{
	int ret = -1;

	struct hxsdk_sip_account sip;

	bzero(&sip, sizeof(sip));
	ret = hx_ioctl(tID, HX_IOCG_EN_SIP, &sip, sizeof(sip));
	if(!ret)
	{
		if(sip.sip_username)
			free(sip.sip_username);
		if(sip.sip_pwd)
			free(sip.sip_pwd);
		if(sip.sip_realm)
			free(sip.sip_realm);
		if(sip.sip_outbound_proxy)
			free(sip.sip_outbound_proxy);
		if(sip.sip_regsrv)
			free(sip.sip_regsrv);
		if(sip.local_addr)
			free(sip.local_addr);
	}

	__report(ret);
	return ret;
}

int _iocs_en_sip(int tID, char **arg)
{
	int ret = -1;

	if(__arglen(arg) != 7)
	{
		xeLOG_ERR("Usage: ARG=username pwd realm outbound_proxy outbound_proxy_port regsrv regsrv_port");
		__report(EARG);
		return -1;
	}
	struct hxsdk_sip_account sip;

	bzero(&sip, sizeof(sip));
	sip.sip_username = (char *)arg[0];
	sip.sip_pwd = (char *)arg[1];
	sip.sip_realm = (char *)arg[2];
	sip.sip_outbound_proxy = (char *)arg[3];
	sip.sip_outbound_proxy_port = atoi(arg[4]);
	sip.sip_regsrv = (char *)arg[5];
	sip.sip_regsrv_port = atoi(arg[6]);
	ret = hx_ioctl(tID, HX_IOCS_EN_SIP, &sip, sizeof(sip));

	__report(ret);
	return ret;

	__report(ret);
	return ret;
}

int _iocg_en_video_bitrate_raw(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_en_bitrate_raw braw;
	memset(&braw,0,sizeof(braw));

	if (!strcmp(arg[0], "main")){
		braw.stype=STYPE_MAIN;
	}else if (!strcmp(arg[0], "subA")){
		braw.stype=STYPE_SUB_A;
	}else if (!strcmp(arg[0], "subB")){
		braw.stype=STYPE_SUB_B;
	}else if (!strcmp(arg[0], "subC")){
		braw.stype=STYPE_SUB_C;
	}else if (!strcmp(arg[0], "subD")){
		braw.stype=STYPE_SUB_D;
	}else if (!strcmp(arg[0], "subE")){
		braw.stype=STYPE_SUB_E;
	}else{
		printf("stype must be main|subA|subB|subC|subD|subE");
	}
	ret = hx_ioctl(tID, HX_IOCG_EN_VIDEO_BITRATE_RAW, &braw, sizeof(braw));

	__report(ret);
	return ret;
}

int _iocs_en_video_bitrate_raw(int tID, char **arg)
{
	int ret = -1;

	if(__arglen(arg) != 2)
	{
		xeLOG_ERR("Usage: ARG=[bitrate]");
		__report(EARG);
		return -1;
	}
	struct hx_ioc_en_bitrate_raw braw;
	memset(&braw,0,sizeof(braw));

	braw.bitrate= atoi(arg[0]);
	if(braw.bitrate<64 || braw.bitrate>4096)
	{
		printf("arg is [64,4096]\n");
	}
	if (!strcmp(arg[1], "main")) {
		braw.stype = STYPE_MAIN;
	} else if (!strcmp(arg[1], "subA")) {
		braw.stype = STYPE_SUB_A;
	} else if (!strcmp(arg[1], "subB")) {
		braw.stype = STYPE_SUB_B;
	} else if (!strcmp(arg[1], "subC")) {
		braw.stype = STYPE_SUB_C;
	} else if (!strcmp(arg[1], "subD")) {
		braw.stype = STYPE_SUB_D;
	} else if (!strcmp(arg[1], "subE")) {
		braw.stype = STYPE_SUB_E;
	} else {
		printf("stype must be main|subA|subB|subC|subD|subE");
	}

	ret = hx_ioctl(tID, HX_IOCS_EN_VIDEO_BITRATE_RAW, &braw, sizeof(braw));

	__report(ret);
	return ret;
}

int _iocg_en_ktask(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_eq_ktask ktask;

	bzero(&ktask, sizeof(ktask));
	ret = hx_ioctl(tID, HX_IOCG_EN_KTASK, &ktask, sizeof(ktask));
	if(!ret)
	{
		struct hx_ioc_eq_ktask *head = ktask.next, *next;

		while(head)
		{
			next = head->next;
			free(head);
			head = next;
		}
	}

	__report(ret);
	return ret;
}

int _iocs_en_ktask(int tID, char **arg)
{
	int ret = -1;

	int argc = __arglen(arg);

	if(!argc)
	{
		xeLOG_ERR("ARG ERROR!!! ARG=TID");
		__report(EARG);
		return -1;
	}
	char TID[128];

	bzero(TID, sizeof(TID));
	int i;

	for(i = 0; i < argc - 1; i++)	//we allow space in argument
	{
		strcat(TID, arg[i]);
		strcat(TID, " ");
	}
	strcat(TID, arg[argc - 1]);

	struct hx_ioc_eq_ktask ktask;

	bzero(&ktask, sizeof(ktask));
	strcpy(ktask.TID, TID);
	ret = hx_ioctl(tID, HX_IOCS_EN_KTASK, &ktask, sizeof(ktask));

	__report(ret);
	return ret;
}

int _iocg_en_stask(int tID, char **arg)
{
	int ret = -1;

	struct hx_ioc_eq_stask stask;

	bzero(&stask, sizeof(stask));
	ret = hx_ioctl(tID, HX_IOCG_EN_STASK, &stask, sizeof(stask));
	if(!ret)
	{
		struct hx_ioc_eq_stask *head = stask.next, *next;

		while(head)
		{
			next = head->next;
			free(head);
			head = next;
		}
	}

	__report(ret);
	return ret;
}

int _iocs_en_stask(int tID, char **arg)
{
	int ret = -1;

	if(__arglen(arg) != 1)
	{
		xeLOG_ERR("Usage: ARG=TID!!!");
		__report(EARG);
		return -1;
	}
	struct hx_ioc_eq_stask stask;

	bzero(&stask, sizeof(stask));
	strcpy(stask.TID, arg[0]);
	ret = hx_ioctl(tID, HX_IOCS_EN_STASK, &stask, sizeof(stask));

	__report(ret);
	return ret;
}

/*EQ stat*/
int _stat_eq_uptime(int tID, char **arg)
{
	int ret = -1;

	struct hx_stat_eq_uptime uptime;

	bzero(&uptime, sizeof(uptime));
	ret = hx_status(tID, HX_STAT_EQ_UPTIME, &uptime, sizeof(uptime));

	__report(ret);
	return ret;
}

int _stat_eq_harddisk(int tID, char **arg)
{
	int ret = -1;

	struct hx_stat_eq_harddisk harddisk;
	bzero(&harddisk, sizeof(harddisk));
	ret = hx_status(tID, HX_STAT_EQ_HARDDISK, &harddisk, sizeof(harddisk));
	if(!ret)
	{
		struct hx_stat_eq_harddisk *head = harddisk.next, *next;

		while(head)
		{
			next = head->next;
			free(head);
			head = next;
		}

	}

	__report(ret);
	return ret;
}

int _rw_num_get(int tID,char **arg)
{
	int num,ret;
	ret = hx_ioctl(tID, HX_IOCG_EQ_RW_NUM, &num, sizeof(int));
	if (ret == 0) {
		DBG("get roadway num supported success\n");
		DBG("rw_num: %d\n", num);
	} else {
		xeLOG_ERR("get roadway num supported fail\n");
	}
	__report(ret);
	return ret;
}

int _rw_num_set(int tID,char **arg)
{
	if (__arglen(arg) != 1) {
		xeLOG_ERR("arg must be 1");
		__report(EARG);
		return -1;
	}
	int ret,num;
	num=atoi(arg[0]);
	if(num>=1 && num>=4)
	{
		ret = hx_ioctl(tID, HX_IOCS_EQ_RW_NUM, &num, sizeof(int));
		if (ret == 0) {
			DBG("set roadway num supported success\n");
		} else {
			xeLOG_ERR("set roadway num supported fail\n");
		}
	}else{
		return -1;
	}
	__report(ret);
	return ret;
}

int _can_get(int tID,char **arg)
{
	int ret,index;
	ret = hx_ioctl(tID, HX_IOCG_EQ_CAN_INDEX, &index, sizeof(int));
	if (ret == 0) {
		DBG("get can success.\n");
		DBG("can index: %d\n", index);
	} else {
		xeLOG_ERR("get can fail\n");
	}
	__report(ret);
	return ret;
}
int _can_set(int tID,char **arg)
{
	if (__arglen(arg) != 1) {
		xeLOG_ERR("arg must be 1");
		__report(EARG);
		return -1;
	}
	int ret, index;
	ret = hx_ioctl(tID, HX_IOCS_EQ_CAN_INDEX, &index, sizeof(int));
	if (ret == 0) {
		DBG("set can success.\n");
	} else {
		xeLOG_ERR("set can fail\n");
	}
	__report(ret);
	return ret;
}

int __s_recwd();
//add by wangtao
int _s_video_preview(int tID, char **arg)
{
	int ret = -1;
	int i = 0,j = 0;
	int channel_num = 4;
	char channels[64];
	char cha[4];
	static char resolution[][16] = {"1920x1080","1280x720","1024x768"};//"720x576"};
							//resolution 720x576 could not display on monitor
	struct hx_ioc_eq_video_winnum winnum;
	struct hx_ioc_osd osd;
	hx_target_t ctID = -1;
	char target[32];

	bzero(&winnum, sizeof(winnum));
	bzero(&osd, sizeof(struct hx_ioc_osd));
	
	channel_num = atoi(arg[1]);
	printf("channel_num: %d\n", channel_num);

	osd.ID = 2;
	osd.status = 2;
	osd.type = 3;
	osd.color = 1;
	osd.xpos = 1;
	osd.ypos = 1;
	strcpy(osd.text, "Resolution:");


	// printf("===============here works===================\n");
	// return 0;

	// set recwd
	ret = __s_recwd();
	if (!ret)
	{
		printf("set recwd fail\n");
	}

	
	// set default win_num
	winnum.winnum = channel_num;
	bzero(&channels, sizeof(channels));
	strcpy(channels,"0");
	for (i = 1; i < channel_num; i++){
		sprintf(cha,",%d",i);
		strcat(channels,cha);
	}
	strcpy(winnum.channels, channels);
	ret = hx_ioctl(tID, HX_IOCS_EQ_VIDEO_WINNUM, &winnum, sizeof(winnum));
	if (ret==0) {
		report_LOG("================================================");
		report_LOG("\tset video default win_num success");
	} else {
		report_LOG("================================================");
		report_LOG("\tset video default win_num fail");
	}
	// set default resolution
	strcpy(winnum.resolution, resolution[1]);
	ret = hx_ioctl(tID, HX_IOCS_EQ_VIDEO_RESOLUTION, &winnum, sizeof(winnum));
	if (ret==0) {
		report_LOG("================================================");
		report_LOG("\tset video default resolution success");
	} else {
		report_LOG("================================================");
		report_LOG("\tset video default resolution fail");
	}
	// wait 10s
	sleep(10);

	
	// change resolutions
	for (i = 0; i < 3; i++){
		//set resolution		
		strcpy(winnum.resolution, resolution[i]);
		ret = hx_ioctl(tID, HX_IOCS_EQ_VIDEO_RESOLUTION, &winnum, sizeof(winnum));
		if (ret==0) {
			report_LOG("\tset video %s success",resolution[i]);
		} else {
			report_LOG("\tset video %s fail",resolution[i]);
		}
		//set osd
		sprintf(osd.text,"Resolution: %s",resolution[i]);
		for (j = 0; j < channel_num; j++){
			ats_LOG("channel %d:", j);
			sprintf(target, "%s:%d", conf_target.identity, j);
			ctID = hx_open(target, conf_target.username, conf_target.pwd, 0);
			ret = hx_ioctl(ctID, HX_IOCS_EN_VIDEO_OSD, &osd, sizeof(osd));
		}
		//wait 10s
		sleep(10);
	}
	
	
	// preview each channel
	winnum.winnum = 1;
	for (i = 0; i < channel_num; i++){
		//set preview window
		bzero(&channels, sizeof(channels));
		sprintf(channels,"%d",i);
		strcpy(winnum.channels, channels);
		ret = hx_ioctl(tID, HX_IOCS_EQ_VIDEO_WINNUM, &winnum, sizeof(winnum));
		//wait 5s
		sleep(5);
	}
	

	//restore default win_num
	winnum.winnum = channel_num;
	bzero(&channels, sizeof(channels));
	strcpy(channels,"0");
	for (i = 1; i < channel_num; i++){
		sprintf(cha,",%d",i);
		strcat(channels,cha);
	}
	printf("channels:%s\n",channels);
	strcpy(winnum.channels, channels);
	ret = hx_ioctl(tID, HX_IOCS_EQ_VIDEO_WINNUM, &winnum, sizeof(winnum));	
	//restore default resolution 1280x720
	strcpy(winnum.resolution, resolution[1]);
	ret = hx_ioctl(tID, HX_IOCS_EQ_VIDEO_RESOLUTION, &winnum, sizeof(winnum));
	//resotre default osd
	osd.status = 1;
	strcpy(osd.text,"");
	for (j = 0; j < channel_num; j++){
		ats_LOG("channel %d:", j);
		sprintf(target, "%s:%d", conf_target.identity, j);
		ctID = hx_open(target, conf_target.username, conf_target.pwd, 0);
		ret = hx_ioctl(ctID, HX_IOCS_EN_VIDEO_OSD, &osd, sizeof(osd));
	}
	//wait 5s
	sleep(5);

	return ret;//ret1 | ret2 |ret..
}

//enable recwd
int __s_en_recwd(int tID) {
	int ret = -1;

	struct hx_ioc_en_recwd recwd;
	bzero(&recwd, sizeof(recwd));

	recwd.wd = 0;
	recwd.idx = 1;
	recwd.status = 1;

	int ret1, ret2;

	char *starttime = "00:00:00";
	char *endtime = "23:59:59";
	ret1 = sscanf(starttime, "%d:%d:%d", &recwd.st_hour, &recwd.st_min, &recwd.st_sec);
	ret2 = sscanf(endtime, "%d:%d:%d", &recwd.et_hour, &recwd.et_min, &recwd.et_sec);
	if (!(ret1 == 3 && ret2 == 3)) {
		xeLOG_ERR("sscanf time ERROR!!!");
		return -1;
	}
	recwd.keepdays = 30;
	ret = hx_ioctl(tID, HX_IOCS_EN_RECWD, &recwd, sizeof(recwd));

	if(ret==0)
	{
		report_LOG("================================================");
		report_LOG("\tset record success");
		
		DBG("HX_IOCS_EN_RECWD SUCCESS\n");
	}else{
		report_LOG("================================================");
		report_LOG("\tset record fail");
		
		DBG("HX_IOCS_EN_RECWD SUCCESS\n");
		xeLOG_ERR("HX_IOCS_EN_RECWD FAIL\n");
	}
	__report( ret);
	return ret;
}

int __s_recwd_dup_2_channels(int tID) {
	int ret = -1;

	struct hx_ioc_en_recwd_dup_2_channels recwd_dup2_channels;
	memset(&recwd_dup2_channels,0,sizeof(recwd_dup2_channels));

	recwd_dup2_channels.from_ChaID=0;
	recwd_dup2_channels.to_channels=(~(1<<0))&(~HX_IOC_EN_CHANUM_MASK);

	ret=hx_ioctl(tID,HX_IOCS_EN_RECWD_DUP_2_CHANNELS,&recwd_dup2_channels,sizeof(recwd_dup2_channels));
	if(ret==0)
	{
		report_LOG("\tset record duplicate to channels success");
		DBG("HX_IOCS_EN_RECWD_DUP_2_CHANNELS SUCCES\n");
	}else{
		report_LOG("\tset record duplicate to channels fail");
		xeLOG_ERR("HX_IOCS_EN_RECWD_DUP_2_CHANNELS FAIL\n");
	}
	__report(ret);
	return ret;
}

int __s_rewd_dup_2_weekdays(int tID)
{
	int ret = -1i;

	struct hx_ioc_en_recwd_dup_2_wdays recwd_dup2_wdays;
	memset(&recwd_dup2_wdays,0,sizeof(recwd_dup2_wdays));

	recwd_dup2_wdays.ChaID=0;
	recwd_dup2_wdays.from_wday=0;
	recwd_dup2_wdays.to_wdays=(~(1<<0))&(~HX_IOC_EN_WDAY_MASK);

	ret = hx_ioctl(tID, HX_IOCS_EN_RECWD_DUP_2_WDAYS, &recwd_dup2_wdays,
			sizeof(recwd_dup2_wdays));
	if (ret == 0) {
		report_LOG("\tset record duplicate to weekdays success");
		DBG("HX_IOCS_EN_RECWD_DUP_2_WDAYS SUCCES\n");
	} else {
		report_LOG("\tset record duplicate to weekdays fail");
		xeLOG_ERR("HX_IOCS_EN_RECWD_DUP_2_WDAYS FAIL\n");
	}
	__report(ret);
	return ret;

}

int __s_recwd()
{
	int ret1, ret2, ret3;

	hx_target_t entID = -1;
	char target[32];

	sprintf(target, "%s:%d", conf_target.identity, 0);
	entID = hx_open(target, conf_target.username, conf_target.pwd, 0);
	if (entID < 0) {
		xeLOG_ERR("open target(%s) FAIL!!!", target);
	}
	DBG("open target(%s) OK!", target);

	ret1 = __s_en_recwd(entID);
	ret2 = __s_rewd_dup_2_weekdays(entID);
	ret3 = __s_recwd_dup_2_channels(entID);

	return ret1 | ret2 | ret3;
}
