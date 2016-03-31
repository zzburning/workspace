SRC_FILES := $(wildcard *.c)
OBJ_FILES := $(patsubst %.c, %.o, $(SRC_FILES))
DEP_FILES := $(addsuffix .d,$(basename $(OBJ_FILES)))


lib: $(OBJ_FILES)
	$(AR) -rsvu  $(LIB_COMMON_A) $(OBJ_FILES)
	cp -f $(LIB_COMMON_A) $(LIBDIR)

clean:
	rm -f $(OBJ_FILES) $(DEP_FILES) $(LIB_COMMON_A)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@


ifneq ($(MAKECMDGOALS),clean)
-include $(DEP_FILES)
endif

