# TARGET.mk_X86_SIMULATE.PC.Unknown
###############################################################################################
TARGET_PLATFORM := X86_SIMULATE
export TARGET_PLATFORM 

CFLAGS += -DCONFIG_PLATFORM=\"$(TARGET_PLATFORM)\"
CFLAGS += -DCONFIG_PLATFORM_$(TARGET_PLATFORM)=\"$(TARGET_PLATFORM)\"

###############################################################################################

ARCH := X86
CC := gcc
AR := ar
export ARCH CC AR

###############################################################################################

TARGET_PRODUCT_MODEL := Unknown
export TARGET_PRODUCT_MODEL

CFLAGS += -DCONFIG_PRODUCT_MODEL=\"$(TARGET_PRODUCT_MODEL)\"
CFLAGS += -DCONFIG_PRODUCT_MODEL_$(TARGET_PRODUCT_MODEL)=\"$(TARGET_PRODUCT_MODEL)\"

###############################################################################################

TARGET_BOARD_NAME := PC
TARGET_BOARD_VERSION := AO
export TARGET_BOARD_NAME TARGET_BOARD_VERSION

CFLAGS += -DCONFIG_BOARD_NAME=\"$(TARGET_BOARD_NAME)\"
CFLAGS += -DCONFIG_BOARD_NAME_$(TARGET_BOARD_NAME)=\"$(TARGET_BOARD_NAME)\"
CFLAGS += -DCONFIG_BOARD_VERSION=\"$(TARGET_BOARD_VERSION)\"
CFLAGS += -DCONFIG_BOARD_VERSION_$(TARGET_BOARD_VERSION)=\"$(TARGET_BOARD_VERSION)\"

###############################################################################################
TARGET_PLATFORM := X86_SIMULATE
export TARGET_PLATFORM 

CFLAGS += -DCONFIG_PLATFORM=\"$(TARGET_PLATFORM)\"
CFLAGS += -DCONFIG_PLATFORM_$(TARGET_PLATFORM)=\"$(TARGET_PLATFORM)\"

###############################################################################################
#Application specific build defins begin here
#build with memwatch or no
#BUILD_MEMWATCH := y

#BUILD_TARGET := Release
BUILD_TARGET := Debug

###############################################################################################
CFLAGS += -DCONFIG_USE_XEHSC=1

TARGET_DEVPLAT := LINUXGCC_32
CFLAGS += -DCONFIG_XEHSC_DEVPLAT_$(TARGET_DEVPLAT)=\"$(TARGET_DEVPLAT)\"

###############################################################################################
 
echo_ENV:
	@echo "TARGET_PLATFORM="$(TARGET_PLATFORM)
	@echo "TARGET_PRODUCT_MODEL="$(TARGET_PRODUCT_MODEL)
	@echo "TARGET_BOARD_NAME="$(TARGET_BOARD_NAME)
	@echo "TARGET_BOARD_VERSION"=$(TARGET_BOARD_VERSION)
	@echo "ARCH"=$(ARCH)
	@echo "CC="$(CC)
	@echo "AR="$(AR)
	@echo "CFLAGS="$(CFLAGS)
	
###############################################################################################
