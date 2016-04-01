
#ifndef __MODULE_H_
#define __MODULE_H_

/****************************************************************
 * Function prototype:
 * 		mod_init_f;
 * Description:
 * 		this callback will be called first when load-in this module;
 * ----------------------------------------------------------------------------------
 * PARAMS:
 * 		@cfile: test case configure file for module;
 * RETURN:
 * 		0: success;
 * 		-1: fail;
 ****************************************************************/
typedef int (*mod_init_f)(const char *cfile);

/****************************************************************
 * Function prototype:
 * 		mod_run_f;
 * Description:
 * 		this callback will be called to run module's main case;
 * ----------------------------------------------------------------------------------
 * PARAMS:NONE;
 * RETURN:
 * 		0: success;
 * 		-1: fail;
 ****************************************************************/
typedef int (*mod_run_f)(void);

/****************************************************************
 * Function prototype:
 * 		mod_deinit_f;
 * Description:
 * 		this callback will be called before de-load this module;
 * ----------------------------------------------------------------------------------
 * PARAMS:	NONE;
 * RETURN:	NONE;
 ****************************************************************/
typedef void (*mod_deinit_f)(void);

//===============================================================
struct module_struct{
	char *name;/*module name*/
	
	mod_init_f init_f;
	mod_run_f run_f;
	mod_deinit_f deinit_f;
	
	void *handle;//handle from dlopen();
};
typedef struct module_struct module_t;


/*****************************************************************
 * Function:
 * 		load_module();
 * Description:
 * 		load a module by it's filesystem name;
 * Reentrantable: Y;
 * ------------------------------------------------------------------------------------
 * @modname: module's name, absolute or relative PATH both OK;
 * ------------------------------------------------------------------------------------
 * RETURN:
 * 		fail: NULL;
 * 		success: valid pointer to module's &mod_export;
 *****************************************************************/
module_t* load_module(const char *modname);

/*****************************************************************
 * Function:
 * 		deload_module();
 * Description:
 * 		de-load a loaded module;
 * ------------------------------------------------------------------------------------
 * @mod_p: module's &mod_export from load_module();
 * ------------------------------------------------------------------------------------
 * RETURN: none;
 *****************************************************************/
void deload_module(module_t *mod_p);

#endif /*__MODULE_H_*/
