#ifndef __CONFIG_FUNC_H__
#define __CONFIG_FUNC_H__


/* equipment config function */
int _iocg_eq_hostname(int tID, char **arg);

int _iocs_eq_hostname(int tID, char **arg);

int _iocg_eq_bootproto(int tID, char **arg);

int _iocs_eq_bootproto(int tID, char **arg);

int _iocg_eq_ip(int tID, char **arg);

int _iocs_eq_ip(int tID, char **arg);

int _iocg_eq_dns(int tID, char **arg);

int _iocs_eq_dns(int tID, char **arg);

int _iocg_eq_pppoe(int tID, char **arg);

int _iocs_eq_pppoe(int tID, char **arg);

int _iocg_eq_datetime(int tID, char **arg);

int _iocs_eq_datetime(int tID, char **arg);

int _iocs_eq_default(int tID, char **arg);

int _iocs_eq_reboot(int tID, char **arg);

int _iocs_eq_halt(int tID, char **arg);

int _iocg_eq_user(int tID, char **arg);

int _iocs_eq_user(int tID, char **arg);

int _iocg_eq_group(int tID, char **arg);

int _iocs_eq_group(int tID, char **arg);

int _iocg_eq_display_windows(int tID, char **arg);

int _iocs_eq_display_windows(int tID, char **arg);

int _iocg_eq_window_display(int tID, char **arg);

int _iocs_eq_window_display(int tID, char **arg);

int _iocg_eq_hosts(int tID, char **arg);

int _iocs_eq_hosts(int tID, char **arg);

int _iocg_eq_disk(int tID, char **arg);

int _iocs_eq_disk(int tID, char **arg);

int _iocg_eq_disk_ext(int tID, char **arg);

int _iocg_eq_sip(int tID, char **arg);

int _iocs_eq_sip(int tID, char **arg);

int _iocg_eq_udp_pktsize(int tID, char **arg);

int _iocs_eq_udp_pktsize(int tID, char **arg);

int _iocg_eq_ip_acl(int tID, char **arg);

int _iocs_eq_ip_acl(int tID, char **arg);

int _iocg_eq_sipuri_acl(int tID, char **arg);

int _iocs_eq_sipuri_acl(int tID, char **arg);

int _iocg_eq_equipment_id(int tID, char **arg);

int _iocs_eq_equipment_id(int tID, char **arg);

int _iocs_eq_commit(int tID, char **arg);

int _iocg_eq_ktask(int tID, char **arg);

int _iocs_eq_ktask(int tID, char **arg);

int _iocg_eq_stask(int tID, char **arg);

int _iocs_eq_stask(int tID, char **arg);

int _iocg_eq_logserver(int tID, char **arg);

int _iocs_eq_logserver(int tID, char **arg);

int _iocg_eq_sw_version(int tID, char **arg);

int _iocs_eq_update(int tID, char **arg);

int _iocg_eq_gauuid(int tID, char **arg);

int _iocs_eq_gauuid(int tID, char **arg);

int _iocg_eq_can_index(int tID, char **arg);

int _iocs_eq_can_index(int tID, char **arg);

int _iocg_eq_rw_num(int tID, char **arg);

int _iocs_eq_rw_num(int tID, char **arg);

//add by wangtao
int _iocg_eq_video_winnum(int tID, char **arg);

int _iocs_eq_video_winnum(int tID, char **arg);

int _iocg_eq_video_resolution(int tID, char **arg);

int _iocs_eq_video_resolution(int tID, char **arg);

int _iocg_eq_video_status(int tID, char **arg);

int _iocs_eq_video_status(int tID, char **arg);

int _iocg_eq_ntp(int tID, char **arg);

int _iocs_eq_ntp(int tID, char **arg);


int _iocg_eq_video_windows_4_de(int tID, char **arg);

/*encode channel function*/
int _iocg_en_name(int tID, char **arg);

int _iocs_en_name(int tID, char **arg);

int _iocs_en_default(int tID, char **arg);

int _iocg_en_video_encoder(int tID, char **arg);

int _iocg_en_video_size(int tID, char **arg);

int _iocg_en_video_bitrate(int tID, char **arg);

int _iocs_en_video_bitrate(int tID, char **arg);

int _iocg_en_video_btype(int tID, char **arg);

int _iocs_en_video_btype(int tID, char **arg);

int _iocg_en_video_framerate(int tID, char **arg);

int _iocs_en_video_framerate(int tID, char **arg);

int _iocg_en_video_iframeinterval(int tID, char **arg);

int _iocs_en_video_iframeinterval(int tID, char **arg);

int _iocg_en_video_color(int tID, char **arg);

int _iocs_en_video_color(int tID, char **arg);

int _iocg_en_video_ratio(int tID, char **arg);

int _iocs_en_video_ratio(int tID, char **arg);

int _iocg_en_video_osd(int tID, char **arg);

int _iocs_en_video_osd(int tID, char **arg);

int _iocg_en_audio_encoder(int tID, char **arg);

int _iocg_en_mux(int tID, char **arg);

int _iocg_en_multicast(int tID, char **arg);

int _iocs_en_multicast(int tID, char **arg);

int _iocg_en_ptz(int tID, char **arg);

int _iocs_en_ptz(int tID, char **arg);

int _iocg_en_recwd(int tID, char **arg);

int _iocs_en_recwd(int tID, char **arg);

int _iocs_en_recwd_dup_2_channels(int tID,char **arg);

int _iocs_en_rewd_dup_2_weekdays(int tID,char **arg);

int _iocg_en_sub_recwd(int tID,char **arg);

int _iocs_en_sub_recwd(int tID,char **arg);

int _iocg_en_mdet(int tID, char **arg);

int _iocs_en_mdet(int tID, char **arg);

int _iocg_en_ptz_protocols(int tID, char **arg);

int _iocg_en_sip(int tID, char **arg);

int _iocs_en_sip(int tID, char **arg);

int _iocg_en_video_bitrate_raw(int tID, char **arg);

int _iocs_en_video_bitrate_raw(int tID, char **arg);


int _iocg_en_ktask(int tID, char **arg);

int _iocs_en_ktask(int tID, char **arg);

int _iocg_en_stask(int tID, char **arg);

int _iocs_en_stask(int tID, char **arg);


/*EQ STAT */
int _stat_eq_uptime(int tID, char **arg);

int _stat_eq_harddisk(int tID, char **arg);

int _rw_num_get(int tID,char **arg);

int _rw_num_set(int tID,char **arg);

int _can_get(int tID,char **arg);

int _can_set(int tID,char **arg);

//add by wangtao
int _s_video_preview(int tID, char **arg);

#endif	/*__CONFIG_FUNC_H__*/
