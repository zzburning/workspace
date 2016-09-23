#ifndef __HISOME_CORE_H_
#define __HISOME_CORE_H_
/*****************************************************************
 * Function:
 * 		init_core();
 * Description:
 * 		init at_suite's core, only first initialize will do some work;
 * 	following call this will just return success;
 * 
 * Reentrantable: N;
 * ------------------------------------------------------------------------------------
 * @cfile: configure file for core;
 * ------------------------------------------------------------------------------------
 * RETURN:
 * 		0: successe;
 * 		-1: fail;
 *****************************************************************/
int init_core(const char *cfile);

/*****************************************************************
 * Function:
 * 		core_mainloop();
 * Description:
 * 		at_suite's main loop. each call will do a complete work base
 * 	on core's configures.
 * 
 * Reentrantable: Y;
 * ------------------------------------------------------------------------------------
 * ------------------------------------------------------------------------------------
 * RETURN:
 * 		0: successe;
 * 		-1: fail;
 *****************************************************************/
int core_mainloop(void);

/************************************
 * Function:
 * 		deinit_core()
 * Description:
 * 		as at_suite run over,free memory
 * Reentrantable: N;
 *
 * RETURN:
 * 		always be 0
 ************************************/
int deinit_core();


#endif /*__HISOME_CORE_H_*/
