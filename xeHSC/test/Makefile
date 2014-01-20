LIB_A := $(TOPDIR)/lib/$(LIB_A)

SRC_FILES := $(wildcard *.c)

ALL_BINS := $(patsubst %.c, %.bin, $(SRC_FILES))

DEP_FILES := $(addsuffix .d,$(basename $(SRC_FILES)))

%.bin:%.c 
	$(CC) -o $@ $(CFLAGS)  $<  $(LIB_A) $(LDFLAGS)


.PHONY: all clean

all: $(LIB_A) $(ALL_BINS)
	chmod +x $(ALL_BINS)
	@echo "build test finish"

clean:
	rm -rf $(ALL_BINS) $(DEP_FILES)
	
ifneq ($(MAKECMDGOALS),clean)
-include $(DEP_FILES)
endif
	
