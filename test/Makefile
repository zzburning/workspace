TOPDIR := $(shell pwd)
RELEASEDIR :=$(TOPDIR)/release
DEBUGDIR := $(TOPDIR)/debug

#package debug|release build
#BUILD_TARGET := Release
BUILD_TARGET ?= Debug

DATE=$(shell date "+%Y%m%d")

#define lib name 
#MODNAME=

CC := gcc

#CFLAGS += -Wall 
LDFLAGS += -lpthread
#CFLAGS += -I$(TOPDIR)/include  

ifeq ($(BUILD_TARGET), Release)
CFLAGS += -O2 -DNDEBUG -DBUILD_TARGET=\"Release\"
CFLAGS +=-DCONFIG_CLOSE_DBG
else
CFLAGS += -g -DBUILD_TARGET=\"Debug\" -DDEBUG=1
CFLAGS +=-DCONFIG_CLOSE_DBG
#CFLAGS +=-UCONFIG_CLOSE_DBG
endif

export TOPDIR CFLAGS LDFLAGS

.PHONY: all clean

SRC_FILES := $(wildcard *.c)
DEP_FILES := $(addsuffix .d,$(basename $(SRC_FILES)))

#ALL_BINS := $(patsubst %.c, %.bin, $(SRC_FILES))
#%.bin:%.c
	#$(CC) -o $@ $(CFLAGS) $< $(LDFLAGS)
#all: $(ALL_BINS)
	#chmod +x $(ALL_BINS)
	#rm -rf $(DEP_FILES)
	#@echo "build test_local finish"
#clean:
	#rm -rf $(ALL_BINS) $(DEP_FILES)
	

RUN_BIN := run.bin
OBJ_FILES :=$(patsubst %.c, %.o, $(SRC_FILES))
%.o:%.c
	$(CC) -o $@ $(CFLAGS) -c $< 
all: $(OBJ_FILES)
	$(CC) -o $(RUN_BIN) $(OBJ_FILES) $(LDFLAGS)
	chmod +x $(RUN_BIN)
	@echo "build $(OBJ_FILES) $(RUN_BIN) finish"
clean:
	rm -rf $(RUN_BIN)  $(DEP_FILES)

	
ifneq ($(MAKECMDGOALS),clean)
-include $(DEP_FILES)
endif

