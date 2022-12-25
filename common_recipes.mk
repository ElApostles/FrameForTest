SRC_MAIN = main.cpp

SRC_IMP += ../utils/BigBeautifulTestFrame.cpp
ifeq ($(V), 1)
	DEFINE = -D VERBOSE
endif

SRC = $(SRC_IMP) $(SRC_MAIN)

DEP = $(SRC:.cpp=.d)

OBJ = $(SRC:.cpp=.o)

JSON= $(SRC:.cpp=.part.json)

CFLAGS = -Wall -Wextra -Werror --std=c++98 -MMD -MP

INCLUDE = -I ../utils

COMPILECOMMAND = compile_commands.json

ifeq ($(D), 1)
	CFLAGS += -g -fsanitize=address,undefined
endif

ifeq ($(COMPILER), clang)
	CXX := clang++
endif

all : $(NAME)

$(NAME) : $(OBJ)
	$(CXX) $(CFLAGS) $(INCLUDE) $(OBJ) -o $@

%.o: %.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) $(DEFINE) -MJ $*.part.json -c $< -o $(<:.cpp=.o)

clean :
	rm -f $(OBJ)
	rm -f $(DEP)
	rm -f $(JSON)

fclean :
	$(MAKE) clean
	rm -f $(NAME)
	rm -f $(COMPILECOMMAND)

re :
	$(MAKE) fclean
	$(MAKE)

COMPILECOMMAND : 
	(printf [ && find . -name "*.part.json" | xargs cat && printf ]) > compile_commands.json

ifneq "$(MAKECMDGOALS)" "clean"
-include $(DEP)
endif
