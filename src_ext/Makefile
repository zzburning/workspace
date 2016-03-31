CC :=gcc
CFLAGS := -DDEBUG -g
LDFLAGS :=
PROGRAM := xml_test.bin


SRC_FILES := $(wildcard *.c) #$(wildcard ../mystring/*.c) 
OBJ_FILES := $(patsubst %.c, %.o, $(SRC_FILES))
DEP_FILES := $(addsuffix .d, $(basename $(notdir $(OBJ_FILES))))

all: $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(OBJ_FILES) $(BASH2008) $(LDFLAGS)
	rm -f $(OBJ_FILES) $(DEP_FILES)
		
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES) $(DEP_FILES)
	
ifneq ($(MAKECMDGOALS),clean)
-include $(DEP_FILES)
endif
