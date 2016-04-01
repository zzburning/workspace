#include <dlfcn.h>

#include "wlog.h"
#include "module.h"

#define MOD_EXPORT_SYM		"mod_export"

module_t* load_module(const char *modname)
{
	module_t *mod_p;
	void *handle=NULL;
	char *error;
	
	if(modname==NULL)
	{
		wLOG_ERR("modname is NULL.");
		return NULL;
	}
	
	handle = dlopen(modname,RTLD_LAZY);
	if(handle==NULL)
	{
		wLOG_ERR("dlopen fail, %s.",dlerror());
		return NULL;
	}
	
	dlerror();    /* Clear any existing error */
	mod_p = (module_t*)dlsym(handle,MOD_EXPORT_SYM);
	if((error = dlerror()) != NULL)
	{
		wLOG_ERR("dlsym %s fail, %s.",MOD_EXPORT_SYM,error);
		dlclose(handle);
		return NULL;
	}
	
	mod_p->handle = handle;
	return mod_p;
}

void deload_module(module_t *mod_p)
{
	mod_p->deinit_f();
	if(mod_p->handle)
		dlclose(mod_p->handle);
	return ;
}
