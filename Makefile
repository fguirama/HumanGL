# ---------- VARIABLE ----------------------------------------------------------------- #
INCS		:=	\
				humanGL.h\
				class/Window.hpp\
				class/BodyPart.hpp\
				class/Character.hpp

SRCS		:=	\
				class/Window.cpp\
				class/BodyPart.cpp\
				class/Character.cpp\
				utils/draw.cpp\
				main.cpp

INCS_D		:=	incs/
SRCS_D		:=	srcs/
OBJS_D		:=	.objs/
DEPS_D		:=	.deps/

OBJS		:=	$(SRCS:%.cpp=$(OBJS_D)%.o)
DEPS		:=	$(SRCS:%.cpp=$(DEPS_D)%.d)

NAME		:=	humanGL#

# ---------- FLAGS -------------------------------------------------------------------- #
CXX			:=	c++
RM			:=	rm -rf
FLAGS		=	-Werror -Wall -Wextra -MMD -MP -std=c++17 -g3


# ---------- DEBUG -------------------------------------------------------------------- #
DEBUG		=	no

ifeq ($(DEBUG), yes)
	FLAGS	+=	-fsanitize=address -DDEBUG=true
endif

VALGRIND	:=	valgrind \
				--track-fds=yes --show-mismatched-frees=yes --read-var-info=yes --track-origins=yes -s \
				--leak-check=full --show-leak-kinds=all\

# ---------- RULES -------------------------------------------------------------------- #
-include $(DEPS)
.DEFAULT_GOAL = all

all			:	$(NAME)

bonus		:	all
			make -C ./bonus/

$(NAME)		:	$(OBJS) $(IRCLIB_A)
			$(CXX) $(FLAGS) -L/opt/homebrew/lib -lSDL2 -framework OpenGL -o $(NAME) $(OBJS)

$(OBJS)		:	$(OBJS_D)%.o: $(SRCS_D)%.cpp | $(OBJS_D) $(DEPS_D)
			$(CXX) $(FLAGS) -I/opt/homebrew/include -I$(INCS_D) -c $< -o $@

$(OBJS_D)	:
			mkdir -p $(OBJS_D)
			mkdir -p $(OBJS_D)class/
			mkdir -p $(OBJS_D)utils/

$(DEPS_D)	:
			mkdir -p $(DEPS_D)
			mkdir -p $(DEPS_D)class/
			mkdir -p $(DEPS_D)utils/

leaks		:	all
			$(VALGRIND) ./$(NAME)

run			:	all
			./$(NAME)

debug		:
			$(MAKE) re DEBUG=yes

clean		:
			$(RM) $(OBJS) $(OBJS_D) $(DEPS_D)

fclean		:	clean
			$(RM) $(NAME)

re			:	fclean all

FORCE		:

.PHONY: all debug bonus leaks run re clean fclean FORCE
