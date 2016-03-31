TOPDIR := $(shell pwd)

# ifeq ($(MAKELEVEL),0)
# include $(TOPDIR)/TARGET.mk
# include $(TOPDIR)/VERSION.mk
# endif

ifeq ($(TARGET_PLATFORM),)
$(error "What TARGET_PLATFORM??")
endif


#package debug|release build
#BUILD_TARGET := Release
BUILD_TARGET ?= Debug

RELEASEDIR :=$(TOPDIR)/release
DEBUGDIR := $(TOPDIR)/debug

DATE=$(shell date "+%Y%m%d")

ifeq ($(BUILD_TARGET), Release)
CFLAGS += -O2 -DNDEBUG -DBUILD_TARGET=\"Release\"
CFLAGS +=-DCONFIG_CLOSE_DBG
else
CFLAGS += -g -DBUILD_TARGET=\"Debug\" -DDEBUG=1
CFLAGS +=-UCONFIG_CLOSE_DBG
endif

CFLAGS += -Wall 
#CFLAGS += -I$(TOPDIR)/include  

LDFLAGS += -lpthread

CC := gcc

export TOPDIR CFLAGS LDFLAGS

ifeq ($(BUILD_MEMWATCH),y)
CFLAGS += -DMEMWATCH 
export BUILD_MEMWATCH
endif

#=====================================================
SRC_FILES := $(wildcard *.c)
DEP_FILES := $(addsuffix .d,$(basename $(SRC_FILES)))


.PHONY: all clean

#===for multi separate files
# ALL_BINS := $(patsubst %.c, %.bin, $(SRC_FILES))
# 
# all: $(ALL_BINS)
# 	chmod +x $(ALL_BINS)
# 	rm -rf $(DEP_FILES)
# 	@echo "build test_local finish"
# 
# clean:
# 	rm -rf $(ALL_BINS) $(DEP_FILES)
# 	
# %.bin:%.c
# 	$(CC) -o $@ $(CFLAGS) $< $(LDFLAGS)
# 
#===for single target
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

	

#===for lib
# .PHONY: all clean dist $(LIBNAME)
# LIBNAME := libEXC
# LIBFNAME := $(LIBNAME).$(TARGET_PLATFORM).$(TARGET_BOARD_NAME).$(ARCH)_$(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_REVISION)-$(VERSION_BUILD_ID)_$(shell date "+%Y%m%d")
# export LIBNAME LIBFNAME
# 
# LIB_A := $(LIBFNAME).a
# LIB_A_PUB := $(LIBNAME).a
# LIB_SO := $(LIBFNAME).so
# LIB_SO_PUB := $(LIBNAME).so
# 
# export LIB_A LIB_A_PUB LIB_SO LIB_SO_PUB
# CFLAGS += -DLIBNAME=\"$(LIBNAME)\"  -DXELOG_PREFIX=\"$(LIBNAME)\"

#  
# all: $(LIBNAME) 
# 	@echo $(LIBNAME) build all finish.
# 
# clean:
# 	$(MAKE) -C src clean
# 	$(MAKE) -C test clean
# 	
# DIST_DIR := $(TOPDIR)/dist/$(LIBNAME)-dist_$(TARGET_PLATFORM).$(TARGET_BOARD_NAME).$(ARCH)_$(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_REVISION)-$(VERSION_BUILD_ID)_$(shell date "+%Y%m%d")
# export DIST_DIR
# 
# dist: $(LIBNAME)
# 	rm -rf $(DIST_DIR)
# 	rm -f $(DIST_DIR).tar.bz2
# 	mkdir -p $(DIST_DIR)/include/EXC $(DIST_DIR)/lib
# 	cp include/*.h $(DIST_DIR)/include/xeEXC
# # 	cp ReleaseNotes $(DIST_DIR)/
# 	$(MAKE) -C src dist
# 	cd dist; tar -jcf `basename $(DIST_DIR)`.tar.bz2 `basename $(DIST_DIR)`;
# 
# $(LIBNAME):
# 	$(MAKE) -C src $@
# 	
# 	
# backup:
# 	F=`basename $(TOPDIR)` ; cd .. ; \
# 	tar --force-local -zcvf `date "+$$F-%Y-%m-%d.src.tar.gz"` $$F
# 	
	
ifneq ($(MAKECMDGOALS),clean)
-include $(DEP_FILES)
endif
# 
# VERSION_MAJOR := 0
# VERSION_MINOR := 1
# VERSION_REVISION := 0
# VERSION_BUILD_ID := $(shell unset LANG; svn info | sed -n '/^Revision/s/Revision:[[:space:]]*\([[:digit:]]\+\)/\1/p'; )
# 
# ifeq  ($(VERSION_BUILD_ID),)
# VERSION_BUILD_ID := 999
# endif
# 
# CFLAGS += -DVERSION_MAJOR=$(VERSION_MAJOR)
# CFLAGS += -DVERSION_MINOR=$(VERSION_MINOR)
# CFLAGS += -DVERSION_REV=$(VERSION_REVISION)
# CFLAGS += -DVERSION_BUILD_ID=$(VERSION_BUILD_ID)
# 
# export VERSION_MAJOR VERSION_MINOR VERSION_REVISION VERSION_BUILD_ID
# 
