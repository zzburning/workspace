
#ifndef __FILE_BACKUP_TASKS_H_
#define __FILE_BACKUP_TASKS_H_

#include "hxSDK_types.h"
#include "mylist.h"
#include <pthread.h>

struct _file_task_info {
        char FID[128];   /*filename ID*/
        int cha;        /*index cha in this response*/
        int locked;     /*1=locked,0=not locked*/
        unsigned long type;
        hx_datetime_t StartTime;
        hx_datetime_t EndTime;
        char bname[16];/*Alarm Body name*/
        enum video_size vsize;/*file encoder size*/
        enum video_encoder venc;/*file encoder name,such as MJPEG,H264*/
};

typedef struct _file_task_info file_task_info_t; 

#define TASK_STATUS_VIEW_NORMAL    (0)
#define TASK_STATUS_VIEW_HIDE      (1)
#define TASK_DOWNLOADING_NUM_MAX  (128)

struct taskinfo{
        file_task_info_t info;
        char status;// 0 - view, 1 - hide
        pthread_mutex_t mutex;
        struct list_head list;
    };
typedef struct taskinfo task_t;

struct task_list_info{
        unsigned int status;
        unsigned int num;
        pthread_mutex_t mutex;
        struct list_head list;
};

typedef struct task_list_info task_list_t;



typedef enum{
        TASK_STATUS_FREE = 0,
        TASK_STATUS_BUSY = 1,
        TASK_STATUS_OVER = 2
}task_status_e;

#ifdef __cplusplus
extern "C" {
#endif

extern int task_lists_init(void);
extern task_t *check_task_is_in_lists(file_task_info_t *info);

extern int add_task_2_list(task_list_t *task_list, task_t *task);
extern int new_task_waiting(task_t **new_task, file_task_info_t *info);

extern task_list_t *get_downloading_task(void);
extern task_list_t *get_waiting_task(void);
extern task_list_t *get_downloaded_task(void);

extern task_t *get_first_task(task_list_t *task_list);
extern char *get_task_num_str(void);
extern int process_download (void);

//extern int remove_task_from_downloading(task_t *task);
//extern int remove_task_from_waiting(task_t *task);
//extern int remove_task_from_downloaded(task_t *task);
extern int destory_task_in_list(task_list_t *task_list, task_t *task);
extern int destory_tasks_in_all_lists(void);

extern int remove_task_from_downloading(task_t *task);

extern int set_status_hide_in_list_downloaded(void);

#ifdef __cplusplus
}
#endif

#endif

