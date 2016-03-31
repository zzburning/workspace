TOPDIR := $(shell pwd)

ifeq ($(MAKELEVEL),0)
include $(TOPDIR)/TARGET.mk
include $(TOPDIR)/VERSION.mk
endif

ifeq ($(TARGET_PLATFORM),)
$(error "What TARGET_PLATFORM??")
endif

LIBNAME := libEXC
LIBFNAME := $(LIBNAME).$(TARGET_PLATFORM).$(TARGET_BOARD_NAME).$(ARCH)_$(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_REVISION)-$(VERSION_BUILD_ID)_$(shell date "+%Y%m%d")
export LIBNAME LIBFNAME

LIB_A := $(LIBFNAME).a
LIB_A_PUB := $(LIBNAME).a
LIB_SO := $(LIBFNAME).so
LIB_SO_PUB := $(LIBNAME).so

export LIB_A LIB_A_PUB LIB_SO LIB_SO_PUB

#package debug|release build
#BUILD_TARGET ?= Release
BUILD_TARGET ?= Debug
export BUILD_TARGET

#lib A or SO as part of other application
#BUILD_USE_ENV	:= LIBASO
BUILD_USE_ENV	:= STANDALONE
export BUILD_USE_ENV


CFLAGS += -Wall -I$(TOPDIR)/include
CFLAGS += -MMD

LDFLAGS += -lpthread

ifeq ($(BUILD_TARGET), Release)
CFLAGS += -O2 -DNDEBUG -DBUILD_TARGET=\"Release\"
else#Debug
CFLAGS += -g -DBUILD_TARGET=\"Debug\" -DDEBUG=1

endif#Debug

CFLAGS += -DLIBNAME=\"$(LIBNAME)\"  -DXELOG_PREFIX=\"$(LIBNAME)\"

ifeq ($(BUILD_MEMWATCH),y)
CFLAGS += -DMEMWATCH 
export BUILD_MEMWATCH
endif

CFLAGS += -I$(TOPDIR)/ext/include

export TARGET_PLATFORM TOPDIR ARCH CC AR CFLAGS LDFLAGS



.PHONY: all clean dist $(LIBNAME)

all: $(LIBNAME) test
	@echo $(LIBNAME) build all finish.

clean:
	$(MAKE) -C src clean
	$(MAKE) -C test clean
	
DIST_DIR := $(TOPDIR)/dist/$(LIBNAME)-dist_$(TARGET_PLATFORM).$(TARGET_BOARD_NAME).$(ARCH)_$(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_REVISION)-$(VERSION_BUILD_ID)_$(shell date "+%Y%m%d")
export DIST_DIR

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
	
	
