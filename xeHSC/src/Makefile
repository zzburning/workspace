#select .C file if need
ifeq ($(BUILD_USE_ENV),STANDALONE)
SRC_FILES := $(wildcard *.c)
else
SRC_FILES := $(wildcard *.c)
endif

ifeq ($(BUILD_MEMWATCH),y)
SRC_FILES += $(TOPDIR)/ext/src/memwatch.c
endif

OBJ_FILES := $(patsubst %.c, %.o, $(SRC_FILES))
DEP_FILES := $(addsuffix .d,$(basename $(OBJ_FILES)))


$(LIB_A): $(OBJ_FILES)
	$(AR) -rsvu  $(LIB_A) $(OBJ_FILES)
	
$(LIB_SO): $(LIB_A)
	$(CC) -shared -o $(LIB_SO) $(OBJ_FILES)	

$(LIBNAME): $(OBJ_FILES) $(LIB_A) $(LIB_SO)	
	cp -f $(LIB_A) $(TOPDIR)/lib/
	
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

	
clean:
	rm -f $(OBJ_FILES) $(DEP_FILES)  *.a *.so
	
dist:
	cp $(LIB_A) $(DIST_DIR)/lib
	cp $(LIB_SO) $(DIST_DIR)/lib
	cd $(DIST_DIR)/lib; \
	ln -s $(LIB_A) $(LIB_A_PUB); \
	ln -s $(LIB_SO) $(LIB_SO_PUB);
	
ifneq ($(MAKECMDGOALS),clean)
-include $(DEP_FILES)
endif
	
