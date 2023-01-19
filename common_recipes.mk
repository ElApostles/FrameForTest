.PHONY : all clean fclean re dev test

SRC_MAIN = main.cpp
TEST_NAME ?= check
V ?= 1
DISABLE_DOCTEST ?= -D DOCTEST_CONFIG_DISABLE

SRC_IMP += ../utils/BigBeautifulTestFrame.cpp
ifeq ($(V), 0)
	DEFINE =
endif

TEST_MAIN = test.cpp

SRC = $(SRC_IMP)

INCLUDE = -I ../utils
INCLUDE += -I ../utils/doctest/doctest

ERROR_FLAGS ?= -Wall -Wextra -Werror 
CXX_STANDARD ?= -std=c++98
OPTIONAL_FLAGS ?= -MMD -MP
DEBUG ?= 


ifeq ($(MAKECMDGOALS), $(TEST_NAME))
	DISABLE_DOCTEST :=
	CXX_STANDARD = -std=c++11
	SRC += $(TEST_MAIN)
	D = 1
	C = 1
else ifeq ($(MAKECMDGOALS), clean)
	SRC += $(TEST_MAIN)
	SRC += $(SRC_MAIN)
else
	SRC += $(SRC_MAIN)
endif

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

DEFINE = -D VERBOSE $(DISABLE_DOCTEST)

CFLAGS = $(ERROR_FLAGS) $(CXX_STANDARD) $(OPTIONAL_FLAGS) $(DEBUG)

DEP = $(SRC:.cpp=.d)

OBJ = $(SRC:.cpp=.o)

JSON= $(SRC:.cpp=.part.json)

COMPILECOMMAND = compile_commands.json

DOCTEST = ../utils/doctest/doctest/doctest.h

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

$(DOCTEST) :
	git clone https://github.com/doctest/doctest.git ../utils/doctest

$(TEST_NAME) : $(OBJ)
	$(CXX) $(CFLAGS) $(TEST_INCLUDE) $(INCLUDE) $(OBJ) -o $@

test : | $(DOCTEST)
	$(MAKE) $(TEST_NAME)

ifneq "$(MAKECMDGOALS)" "clean"
-include $(DEP)
endif
