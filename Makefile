MAKE_DEBUG := 1

include src/Makefile
include test/Makefile

FILES := $(FILES)
EXE := stein
INC := $(INC)
LIBS :=

FLAGS := -Wall -W -ansi
DEBUG_FLAGS := -g -ftrapv -fexceptions -D_DEBUG=1

#AS_ERROR := 1

###########
# TEST
#TEST := 1
t_FILES := $(t_FILES)
t_INC :=
t_CFLAGS := -D_TEST=1 -g $(t_INC)
t_LIBS := $(LIBS) -lcheck
t_EXE := $(EXE)_test
###########

#########
# DO NOT TOUCH

FILES := $(FILES:%.c=src/%.c)
t_FILES := $(t_FILES:%.c=test/%.c)
OBJ := $(FILES:%.c=%.o)
t_OBJ := $(t_FILES:%.c=%.o)

CC := clang
CFLAGS := $(FLAGS) $(INC)

ifdef AS_ERROR
    CFLAGS := -Werror $(CFLAGS)
endif

ifdef MAKE_DEBUG
    CFLAGS := $(CFLAGS) $(DEBUG_FLAGS)
endif

ifndef TEST
    all: $(EXE)
else
    CFLAGS := $(CFLAGS) $(t_CFLAGS)
    all: annot $(t_EXE) run_test
endif
annot:
	ctags -R
$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIBS)
$(t_EXE): $(t_OBJ) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(t_OBJ) $(OBJ) $(t_LIBS)

run_test:
	@echo
	@echo "********************************************"
	@./$(t_EXE) donjon

cleanup:
	rm -f *.o
	rm -f src/*.o
	rm -f test/*.o
clean: cleanup
	rm -f $(EXE) $(t_EXE)

