#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#include <errno.h>
#include <unistd.h>
#include <pthread.h>

#define HAVE_FILE_BACKUP_TASKS    1

#ifdef HAVE_FILE_BACKUP_TASKS

#include "mylist.h"
#include "xelog.h"
#include "file_backup_tasks.h"


#ifndef likely
  #define likely(x)     __builtin_expect(!!(x), 1)
#endif
#ifndef unlikely
  #define unlikely(x)   __builtin_expect(!!(x), 0)
#endif

// formate:char FID[128] = "FID=505c4cdc:2b2a9@/mnt/sdb1/E_0072.DAT_0x1eeae5b3_0x3ffe25a0";

static task_list_t task_downloading, task_waiting, task_downloaded;
static int flag_init = 0;



static void tast_list_init(task_list_t * task_x)
{
     pthread_mutex_init(&task_x->mutex, NULL);
    
     pthread_mutex_lock(&task_x->mutex);
     task_x->status = 0;
     task_x->num = 0;
     INIT_LIST_HEAD(&(task_x->list));
     pthread_mutex_unlock(&task_x->mutex);
     
     return;
}

int task_lists_init(void)
{
   if(!flag_init) {
       tast_list_init(&task_downloading);
       tast_list_init(&task_waiting);
       tast_list_init(&task_downloaded);
       flag_init = 1;
   }

   return 0;
}


static int task_info_compare(file_task_info_t *info_new, file_task_info_t *info_old)
{
	if(info_new->cha == info_old->cha && info_new->type == info_old->type && strcmp(info_new->FID, info_old->FID) == 0)
	{
		return 0;
	}
	return 1;

}

task_t *check_task_is_in_lists(file_task_info_t *info)
{
    task_t *task = NULL;
    task_t *tmp;

    list_for_each_entry_safe(task, tmp, &task_downloading.list, list)
    {
        if (likely(task_info_compare(info, &task->info) != 0 ))
            continue;

        goto __end;
    }


    list_for_each_entry_safe(task, tmp, &task_downloaded.list, list)
    {
        if (likely(task_info_compare(info, &task->info) != 0 ))
            continue;

        goto __end;
    }

    list_for_each_entry_safe(task, tmp, &task_waiting.list, list)
    {
        if (likely(task_info_compare(info, &task->info) != 0 ))
            continue;
        goto __end;
    }

    return NULL;

__end:
    return task;
}



static void task_init(task_t * task)
{
     pthread_mutex_init(&task->mutex, NULL);

     pthread_mutex_lock(&task->mutex);
     memset(&task->info, 0, sizeof(task->info)); 
     task->status = TASK_STATUS_VIEW_NORMAL;
     INIT_LIST_HEAD(&(task->list));
     pthread_mutex_unlock(&task->mutex);

     return;
}

static void task_uinit(task_t * task)
{
     pthread_mutex_destroy(&task->mutex);

     return;
}


static int set_new_task(task_t *task, file_task_info_t *info)
{
    pthread_mutex_lock(&task->mutex);
    task->info = *info;
    pthread_mutex_unlock(&task->mutex);

    return 0;
}


static int set_task_status(task_t *task, int status)
{
    pthread_mutex_lock(&task->mutex);
    task->status = status;
    pthread_mutex_unlock(&task->mutex);

    return 0;
}

static int update_tasks_status_in_list(task_list_t *task_list, int status)
{
    int cnt = 0;
    struct list_head *pos,*p;
    task_t *task;

    struct list_head *list;

    pthread_mutex_lock(&task_list->mutex);

    list = &task_list->list;
    list_for_each_safe(pos, p, list){
        task = list_entry(pos, task_t, list);
        pthread_mutex_lock(&task->mutex);
        if(task->status != status) {
            task->status = status;
            cnt += 1;
        }
        pthread_mutex_unlock(&task->mutex);
    }

    pthread_mutex_unlock(&task_list->mutex);

    return cnt;
}

int set_status_hide_in_list_downloaded(void)
{
     return update_tasks_status_in_list(&task_downloaded, TASK_STATUS_VIEW_HIDE);
}

int add_task_2_list(task_list_t *task_list, task_t *task) 
{
     assert(task);
     assert(task_list);

     pthread_mutex_lock(&task_list->mutex);
     
     pthread_mutex_lock(&task->mutex);
     list_add(&task->list, &task_list->list);
     pthread_mutex_unlock(&task->mutex);
     task_list->num += 1;
     pthread_mutex_unlock(&task_list->mutex);
     
     return 0;
}

int get_task_downloading_num(void);
int new_task_waiting(task_t **new_task, file_task_info_t *info)
{
    task_t *task;

    task = check_task_is_in_lists(info);

    if(task) { // it's found
        *new_task = task;
        return 0;
    }
    int num = get_task_downloading_num();
    if(num >= TASK_DOWNLOADING_NUM_MAX)
        return -1;

    task = (task_t *)calloc(1, sizeof(task_t));

    if (unlikely(NULL == task))
    {
        xeLOG_ERR("Alloc memory for new bakup task fail(%d): %s", errno, strerror(errno));
        goto __error_0;
    }

    task_init(task);
    set_new_task(task, info);
    add_task_2_list(&task_waiting, task);

    *new_task = task;
    return 1;

__error_0:
    return -2;
}


int remove_task_from_list(task_list_t *task_list, task_t *task)
{
    assert(task);
    assert(task_list);
    
    pthread_mutex_lock(&task_list->mutex);

    pthread_mutex_lock(&task->mutex);    
    list_del(&task->list);
    pthread_mutex_unlock(&task->mutex);
  
    task_list->num -= 1;
    pthread_mutex_unlock(&task_list->mutex);

    return 0;
}


int remove_task_from_downloading(task_t *task)
{
    return remove_task_from_list(&task_downloading, task);
}


int remove_task_from_waiting(task_t *task)
{
    return remove_task_from_list(&task_waiting, task);
}

int remove_task_from_downloaded(task_t *task)
{
    return remove_task_from_list(&task_downloaded, task);
}



int destory_task_in_list(task_list_t *task_list, task_t *task)
{

    remove_task_from_list(task_list, task);
        
    task_uinit(task);
    free(task);  
 
    return 0;  
}


int destory_alltasks_in_list(task_list_t *task_list)
{
    struct list_head *pos,*p;
    task_t *task;

    struct list_head *list;

    pthread_mutex_lock(&task_list->mutex);

    list = &task_list->list;
    list_for_each_safe(pos, p, list){  
        task = list_entry(pos, task_t, list);
        pthread_mutex_lock(&task->mutex);
        list_del(pos);
        pthread_mutex_unlock(&task->mutex);
        task_uinit(task);
        free(task);  
    }
    task_list->num = 0; 
    pthread_mutex_unlock(&task_list->mutex);

    if (list_empty(list)){  
        dprintf("The list now is empty!\n");  
    }

    return 0;  
}


int destory_tasks_in_list_downloading(void)
{
    return destory_alltasks_in_list(&task_downloading);
}

int destory_tasks_in_list_waiting(void)
{
    return destory_alltasks_in_list(&task_waiting);
}

int destory_tasks_in_list_downloaded(void)
{
    return destory_alltasks_in_list(&task_downloaded);
}

int destory_tasks_in_all_lists(void)
{
	if(!flag_init)//if uninitialized return 0
	{
		return 0;
	}
    destory_alltasks_in_list(&task_downloading);
    destory_alltasks_in_list(&task_waiting);
    destory_alltasks_in_list(&task_downloaded);
    return 0;
}

task_t *get_last_task(task_list_t *task_list)
{
      task_t *tmp = NULL;

      struct list_head *list;

      pthread_mutex_lock(&task_list->mutex);

      list = &task_list->list;
      if (!list_empty(list)) {
         tmp = list_first_entry(list, task_t, list);
      }

      pthread_mutex_unlock(&task_list->mutex);

      return tmp;
}

task_t *get_first_task(task_list_t *task_list)
{
      task_t *tmp = NULL;

      struct list_head *head;//, *pos;

      pthread_mutex_lock(&task_list->mutex);

      head = &task_list->list;
      if (!list_empty(head)) {
               tmp = list_last_entry(head, task_t, list);
      }

      pthread_mutex_unlock(&task_list->mutex);

      return tmp;
}

task_list_t *get_downloading_task(void)
{
     return (task_list_t *)&task_downloading;
}

task_list_t *get_waiting_task(void)
{
     return (task_list_t *)&task_waiting;
}

task_list_t *get_downloaded_task(void)
{
     return (task_list_t *)&task_downloaded;
}

int process_download (void)
{
    task_t *task;

    task = get_first_task(&task_downloading);

    if(task)
        return 1;

    //downloading is empty!
    task = get_first_task(&task_waiting);     // get a task;
    if(task == NULL)
        return 0;
 
    remove_task_from_list(&task_waiting, task);
    
    add_task_2_list(&task_downloading, task); // add to  

    return 1;
}


int get_task_num_in_list(task_list_t *task_list)
{
     int num;

     pthread_mutex_lock(&task_list->mutex);
     num = task_list->num;
     pthread_mutex_unlock(&task_list->mutex);

     return num;
}


int get_task_downloading_num(void)
{
    int num, total = 0;

    num = get_task_num_in_list(&task_downloading);
    total += num;
    num = get_task_num_in_list(&task_waiting);
    total += num;

    return total;
}


int get_task_total_num(void)
{
    int num, total = 0;

    num = get_task_num_in_list(&task_downloading);
    total += num;
    num = get_task_num_in_list(&task_downloaded);
    total += num;
    num = get_task_num_in_list(&task_waiting);
    total += num;

    return total;
}

int get_task_downloaded_num(void)
{
    return get_task_num_in_list(&task_downloaded);
}

char *get_task_num_str(void)
{
      static char s_num[16];

      snprintf(s_num, sizeof(s_num), "%d/%d", get_task_downloaded_num(), get_task_total_num());

      return s_num;
}


int print_fileInfo()//struct list_head *waiting
{
	task_t *task = NULL, *tmp;
	task_t *tem = NULL;
	int i = 1;
	int stat = 0;
	list_for_each_entry_safe(task, tmp, &task_waiting.list, list)
	{
        //MsgEGL_NOTICE("task_waiting.list-------------count(%d)------------",i++);
        //MsgEGL_NOTICE("channel = %d FID = %s, bname = %s, type = %d",task->info.cha,task->info.FID,task->info.bname,task->info.type);
	}

	tem = get_first_task(&task_waiting);//
	if(tem != NULL)
	{
		remove_task_from_list(&task_waiting, tem);
                add_task_2_list(&task_downloading, tem);//task -> downloading
	}

	i = 1;
	list_for_each_entry_safe(task, tmp, &task_waiting.list, list)
		{
            //MsgEGL_NOTICE("surplus_list_:waiting-------------surplus count(%d)------------",i++);
            //MsgEGL_NOTICE("channel = %d FID = %s, bname = %s, type = %d",task->info.cha,task->info.FID,task->info.bname,task->info.type);
		}


	i = 1;
	list_for_each_entry_safe(task, tmp, &task_downloading.list, list)
	{
        //MsgEGL_NOTICE("task_downloading.list-------------count(%d)------------",i++);
        //MsgEGL_NOTICE("channel = %d FID = %s, bname = %s, type = %d",task->info.cha,task->info.FID,task->info.bname,task->info.type);
	}

	if(tem != NULL)
	{
			stat = remove_task_from_list(&task_downloading, tem);
	}
	i = 1;
	list_for_each_entry_safe(task, tmp, &task_downloading.list, list)
	{
        //MsgEGL_NOTICE("surplus_task_downloading.list-------------surplus_count(%d)------------",i++);
        //MsgEGL_NOTICE("channel = %d FID = %s, bname = %s, type = %d",task->info.cha,task->info.FID,task->info.bname,task->info.type);
	}

	if(tem != NULL)
	{
		stat = add_task_2_list(&task_downloaded, tem);
	}

	i = 1;
	list_for_each_entry_safe(task, tmp, &task_downloaded.list, list)
	{
        //MsgEGL_NOTICE("list_downloaded-------------count(%d)------------",i++);
        //MsgEGL_NOTICE("channel = %d FID = %s, bname = %s, type = %d",task->info.cha,task->info.FID,task->info.bname,task->info.type);
	}
	return 0;
}


#endif //#define HAVE_FILE_BACKUP_TASKS
