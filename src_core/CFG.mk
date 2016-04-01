###########################################################################
# Version Config
###########################################################################
VERSION_MAJOR := 0
VERSION_MINOR := 2
VERSION_REVISION := 1
VERSION_EXTSTR := RC1

# VERSION_BUILD_ID := $(shell unset LANG; svn info | sed -n '/^Revision/s/Revision:[[:space:]]*\([[:digit:]]\+\)/\1/p'; )

ifeq  ($(VERSION_BUILD_ID),)
VERSION_BUILD_ID := 999
endif

CFLAGS += -DVERSION_MAJOR=$(VERSION_MAJOR)
CFLAGS += -DVERSION_MINOR=$(VERSION_MINOR)
CFLAGS += -DVERSION_REV=$(VERSION_REVISION)
CFLAGS += -DVERSION_BUILD_ID=$(VERSION_BUILD_ID)
CFLAGS += -DVERSION_EXTSTR=\"$(VERSION_EXTSTR)\"

export VERSION_MAJOR VERSION_MINOR VERSION_REVISION VERSION_BUILD_ID VERSION_EXTSTR

###########################################################################
# Build Flags Config
###########################################################################
BUILD_TARGET := Debug 
#BUILD_TARGET := Release 

CFLAGS += -Wall -I$(TOPDIR)/include -MMD 

ifeq ($(BUILD_TARGET), Release)
CFLAGS += -O2 -DNDEBUG -DBUILD_TARGET=\"Release\" -UMEMWATCH -DNO_DEBUG
else
CFLAGS += -g -DBUILD_TARGET=\"Debug\" -DDEBUG=1 
endif

#Build with external xelog.h
CFLAGS += -DXELOG_PREFIX=\"core_other\" -DEMBED=1
CFLAGS += -DCONFIG_USE_EXTERNAL_XELOG=1 -DXELOG_2_LOCAL=1
CFLAGS += -DCONFIG_USE_XEDEX2

# #NFS_DEBUG_MODE for RB-S2012 NFS DEBUG
# CFLAGS += -DNFS_DEBUG_MODE=1

LDFLAGS += -lpthread

export CFLAGS LDFLAGS 

###########################################################################
# Build Target Config
###########################################################################
#***begin for x86 board*******************************
ARCH := X86
CC := gcc
AR := ar

TARGET_PLATFORM := X86
TARGET_PRODUCT_MODEL := RB-NG
TARGET_BOARD_NAME := XSIMULATE
TARGET_BOARD_VERSION := VB10x
#***end for x86 board*********************************

#***begin for raspberry board*************************
# TOOLPATH ?= /opt/arm-2009q1/bin/
# ARCH := ARM926EJ-S
# CC := $(TOOLPATH)/arm-none-linux-gnueabi-gcc
# AR := $(TOOLPATH)/arm-none-linux-gnueabi-ar

# TARGET_PLATFORM := ARM
# TARGET_PRODUCT_MODEL := RB-NG
# TARGET_BOARD_NAME := RASPBERRY
# TARGET_BOARD_VERSION := VB10x
#***end for raspberry board***************************

export TARGET_PLATFORM
export ARCH CC AR
export TARGET_PRODUCT_MODEL
export TARGET_BOARD_NAME 
export TARGET_BOARD_VERSION 

CFLAGS += -DCONFIG_PLATFORM=\"$(TARGET_PLATFORM)\"
CFLAGS += -DCONFIG_PRODUCT_MODEL=\"$(TARGET_PRODUCT_MODEL)\"
CFLAGS += -DCONFIG_BOARD_NAME=\"$(TARGET_BOARD_NAME)\"
CFLAGS += -DCONFIG_BOARD_VERSION=\"$(TARGET_BOARD_VERSION)\"
