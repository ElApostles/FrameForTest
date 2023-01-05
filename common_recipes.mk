SRC_MAIN = main.cpp
TEST_NAME ?= check

SRC_IMP += ../utils/BigBeautifulTestFrame.cpp
ifeq ($(V), 1)
	DEFINE = -D VERBOSE
endif

TEST_MAIN = test.cpp

SRC = $(SRC_IMP)

INCLUDE = -I ../utils

CFLAGS = -Wall -Wextra -Werror --std=c++98 -MMD -MP

ifeq ($(MAKECMDGOALS), test)
	SRC += $(TEST_MAIN)
	INCLUDE += -I ../utils/doctest/doctest
	CFLAGS = -Wall -Wextra -Werror --std=c++17 -MMD -MP
else ifeq ($(MAKECMDGOALS), clean)
	SRC += $(TEST_MAIN)
	SRC += $(SRC_MAIN)
else
	SRC += $(SRC_MAIN)
endif

DEP = $(SRC:.cpp=.d)

OBJ = $(SRC:.cpp=.o)

JSON= $(SRC:.cpp=.part.json)


COMPILECOMMAND = compile_commands.json

ifeq ($(D), 1)
	CFLAGS += -g -fsanitize=address,undefined
	MAKE_JSON = -MJ $*.part.json
endif

ifeq ($(COMPILER), clang)
	CXX := clang++
endif

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
