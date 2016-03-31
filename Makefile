TOPDIR := $(shell pwd)
DIST_DIR := $(TOPDIR)/dist

LIBNAME := libEXC
LIBFNAME := $(LIBNAME).$(ARCH)_$(VERSION_MAJOR).$(VERSION_MINOR).(shell date "+%Y%m%d")

CFLAGS += -DLIBNAME=\"$(LIBNAME)\"  -DXELOG_PREFIX=\"$(LIBNAME)\"

export TOPDIR DIST_DIR LIBNAME LIBFNAME

LIB_A := $(LIBFNAME).a
LIB_A_PUB := $(LIBNAME).a
LIB_SO := $(LIBFNAME).so
LIB_SO_PUB := $(LIBNAME).so

export LIB_A LIB_A_PUB LIB_SO LIB_SO_PUB

SRC_FILES := $(wildcard *.c)
ALL_BINS := $(patsubst %.c, %.bin, $(SRC_FILES))
DEP_FILES := $(addsuffix .d,$(basename $(SRC_FILES)))


CC := gcc
export ARCH CC AR


#BUILD_TARGET ?= Release
BUILD_TARGET ?= Debug

export BUILD_TARGET

ifeq ($(BUILD_TARGET), Release)
CFLAGS += -O2 -DCONFIG_CLOSE_DBG=1 -DDEBUG=0 -DNDEBUG -DBUILD_TARGET=\"Release\"
else
CFLAGS += -g -DCONFIG_CLOSE_DBG=0 -DDEBUG=1 -DBUILD_TARGET=\"Debug\" 
endif

CFLAGS += -Wall -MMD 
CFLAGS += -I$(TOPDIR)/include
CFLAGS += -I$(TOPDIR)/ext/include
CFLAGS += 

ifeq ($(BUILD_MEMWATCH),y)
CFLAGS += -DMEMWATCH 
export BUILD_MEMWATCH
endif

LDFLAGS += -lpthread

export CFLAGS LDFLAGS

.PHONY: all bin test clean dist $(LIBNAME)

%.bin:%.c
	$(CC) -o $@ $(CFLAGS) $< $(LDFLAGS)

bin: $(ALL_BINS)
	chmod +x $(ALL_BINS)
	rm -rf $(DEP_FILES)
	@echo "build test_local finish"

all: $(LIBNAME) bin test
	@echo $(LIBNAME) build all finish.

clean:
	$(MAKE) -C src clean
	$(MAKE) -C test clean
	rm -rf $(ALL_BINS) $(DEP_FILES)
	
dist: $(LIBNAME)
	rm -rf $(DIST_DIR)
	rm -f $(DIST_DIR).tar.bz2
	mkdir -p $(DIST_DIR)/include/EXC $(DIST_DIR)/lib
	cp include/*.h $(DIST_DIR)/include/xeEXC
# 	cp ReleaseNotes $(DIST_DIR)/
	$(MAKE) -C src dist
	cd dist; tar -jcf `basename $(DIST_DIR)`.tar.bz2 `basename $(DIST_DIR)`;

$(LIBNAME):
	$(MAKE) -C src $@
	
	
backup:
	F=`basename $(TOPDIR)` ; cd .. ; \
	tar --force-local -zcvf `date "+$$F-%Y-%m-%d.src.tar.gz"` $$F
	
test: $(LIBNAME)
	$(MAKE) -C test all
#	make -C test all
	
	
