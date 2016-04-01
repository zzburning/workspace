#This is top Makefile

.PHONY: all core modules clean install 
	
#####################################################################################################
#add macro to define if excute some code
ROOTDIR := $(shell pwd)
CORE_DIR := src
CORE_SRC := $(CORE_DIR)/main.c \
 				$(CORE_DIR)/core.c \
 				$(CORE_DIR)/module.c \
				$(CORE_DIR)/wlog.c \
				$(CORE_DIR)/lpconfig.c \
				$(CORE_DIR)/uglib.c \
				$(CORE_DIR)/glist.c 

CORE_OBJS := $(patsubst %.c,%.o,$(CORE_SRC))
CORE_DEPS := $(patsubst %.c,%.d,$(CORE_SRC))
BIN_NAME	:= run.bin

CORE_INSTALL_DIR := $(ROOTDIR)/build
MOD_PREFIX := Makefile.sub
#MOD += config
MOD += config
MOD_INSTALL_DIR := $(ROOTDIR)/build
CONF_DIR := $(ROOTDIR)/conf
CONF_INSTALL_DIR := $(ROOTDIR)/build/conf

#####################################################################################################
#CPPFLAGS := -I$(ROOTDIR)/include  -DHXSDK_USE_EXTERNAL_XELOG
CPPFLAGS :=
CFLAGS := -g -Wall $(CPPFLAGS) $(SDK_DEFINE) -MMD  
LDFLAGS := -rdynamic -ldl -lpthread 
#LDFALGS += $(ROOTDIR)/lib

export CFLAGS LDFALGS
#####################################################################################################
CC := gcc
RM := rm -rf
MAKE := make
MKDIR := mkdir -p
CPFILE := cp -f

export CC RM MAKE MKDIR CPFILE CFLAGS 
#####################################################################################################
all: core modules

core: $(CORE_OBJS) 
	$(CC) -o $(BIN_NAME) $(CORE_OBJS) $(LDFLAGS)

	
modules:
	for i in $(MOD); do \
		$(MAKE) -f $(MOD_PREFIX).$$i all || exit $$?; \
	done

clean:
	$(RM) $(BIN_NAME) $(CORE_OBJS) $(CORE_DEPS)
	for i in $(MOD); do \
		$(MAKE) -f $(MOD_PREFIX).$$i clean || exit $$?; \
	done

####################################################################################################
.PHONY: install_dirs install_core install_modules install_conf 

install: all install_dirs install_core install_modules  

install_dirs:
	$(MKDIR) $(CORE_INSTALL_DIR)
	$(MKDIR) $(MOD_INSTALL_DIR)
	$(MKDIR) $(CONF_INSTALL_DIR)
	
install_core:
	$(CPFILE) $(BIN_NAME) $(CORE_INSTALL_DIR)

install_modules:
	for i in $(MODIR); do \
		$(MAKE) -f $(MOD_PREFIX).$$i install || exit $$?; \
	done

install_conf:
	$(CPFILE) $(CONF_DIR)/ats.conf $(CONF_INSTALL_DIR)
	$(CPFILE) $(CONF_DIR)/ats_linE.conf $(CONF_INSTALL_DIR)
	for i in $(MOD); do \
		$(MAKE) -f $(MOD_PREFIX).$$i install_conf || exit $$?; \
	done

#----------------------------------------------------------------------------------------------------
.PHONY: clean_install clean_install_core clean_install_modules clean_install_conf

clean_install: clean_install_core clean_install_modules clean_install_conf

clean_install_core:
	$(RM) $(CORE_INSTALL_DIR)/$(BIN_NAME)

clean_install_modules:
	$(RM) $(MOD_INSTALL_DIR)/*.so

clean_install_conf:
	$(RM) $(CONF_INSTALL_DIR)/*.conf
	
####################################################################################################
CASE_DIR_PREFIX := case
CASE_DIR = $(shell ls case)
.PHONY: cp_modules

cp_modules:
	for i in $(CASE_DIR); do \
		$(CPFILE) $(CORE_INSTALL_DIR)/$(BIN_NAME) 	$(CASE_DIR_PREFIX)/$$i/; \
		$(CPFILE) $(MOD_INSTALL_DIR)/*.so		$(CASE_DIR_PREFIX)/$$i/modules/; \
	done

#####################################################################################################
%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@
#####################################################################################################
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(CORE_DEPS),)
-include $(CORE_DEPS)
endif
endif
#####################################################################################################
