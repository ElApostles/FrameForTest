SRC_MAIN = main.cpp
TEST_NAME ?= check
V ?= 1
DEFINE = -D VERBOSE

SRC_IMP += ../utils/BigBeautifulTestFrame.cpp
ifeq ($(V), 0)
	DEFINE =
endif

TEST_MAIN = test.cpp

SRC = $(SRC_IMP)

INCLUDE = -I ../utils

ERROR_FLAGS ?= -Wall -Wextra -Werror 
CXX_STANDARD ?= -std=c++98
OPTIONAL_FLAGS ?= -MMD -MP
DEBUG ?= 

ifeq ($(D), 1)
	ERROR_FLAGS := -Weverything
	DEBUG := -g -fsanitize=address,undefined
endif

ifeq ($(J), 1)
	OPTIONAL_FLAGS += -MJ $*.part.json
endif

ifeq ($(C), clang)
	CXX := clang++
endif

ifeq ($(MAKECMDGOALS), test)
	SRC += $(TEST_MAIN)
	INCLUDE += -I ../utils/doctest/doctest
	CXX_STANDARD := -std=c++17
else ifeq ($(MAKECMDGOALS), clean)
	SRC += $(TEST_MAIN)
	SRC += $(SRC_MAIN)
else
	SRC += $(SRC_MAIN)
endif

CFLAGS = $(ERROR_FLAGS) $(CXX_STANDARD) $(OPTIONAL_FLAGS) $(DEBUG)

DEP = $(SRC:.cpp=.d)

OBJ = $(SRC:.cpp=.o)

JSON= $(SRC:.cpp=.part.json)

COMPILECOMMAND = compile_commands.json

all : $(NAME)

$(NAME) : $(OBJ)
	$(CXX) $(CFLAGS) $(INCLUDE) $(OBJ) -o $@

%.o: %.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) $(DEFINE) $(MAKE_JSON) -c $< -o $(<:.cpp=.o)

clean :
	rm -f $(OBJ)
	rm -f $(DEP)
	rm -f $(JSON)

fclean :
	$(MAKE) clean
	rm -f $(NAME)
	rm -f $(TEST_NAME)
	rm -f $(COMPILECOMMAND)

re :
	$(MAKE) fclean
	$(MAKE)

dev : 
	(printf [ && find . -name "*.part.json" | xargs cat && printf ]) > compile_commands.json

test : $(TEST_NAME)

$(TEST_NAME) : $(OBJ)
	$(CXX) $(CFLAGS) $(TEST_INCLUDE) $(INCLUDE) $(OBJ) -o $@

.PHONY : all clean fclean re dev test

ifneq "$(MAKECMDGOALS)" "clean"
-include $(DEP)
endif
