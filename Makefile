# ---------- VARIABLE ----------------------------------------------------------------- #
SRCS		:=	\
				srcs/class/Window.cpp\
				srcs/class/BodyPart.cpp\
				srcs/class/Character.cpp\
				srcs/class/Matrix4.cpp\
				srcs/class/MatrixStack.cpp\
				srcs/class/Vector4.cpp\
				srcs/class/Color.cpp\
				srcs/utils/draw.cpp\
				srcs/utils/animation.cpp\
				srcs/main.cpp

INCS_D		:=	incs/
SRCS_D		:=	srcs/
OBJS_D		:=	.objs/
OBJS		=	$(addprefix $(OBJS_D), $(SRCS:.cpp=.o))
DEPS		=	$(addprefix $(OBJS_D), $(SRCS:.cpp=.d))

NAME		:=	humanGL#

# ---------- FLAGS -------------------------------------------------------------------- #
CXX			:=	c++
RM			:=	rm -rf
FLAGS		=	-Werror -Wall -Wextra -MMD -MP -std=c++20 -g3


# ---------- DEBUG -------------------------------------------------------------------- #
DEBUG		=	no

ifeq ($(DEBUG), yes)
	FLAGS	+=	-fsanitize=address -DDEBUG=true
endif

VALGRIND	:=	valgrind \
				--track-fds=yes --show-mismatched-frees=yes --read-var-info=yes --track-origins=yes -s \
				--leak-check=full --show-leak-kinds=all\

# ---------- RULES -------------------------------------------------------------------- #
.DEFAULT_GOAL = all

all			:	$(NAME)

$(NAME)		:	$(OBJS)
			$(CXX) $(FLAGS) -I/usr/include/SDL2 -D_REENTRANT -o $(NAME) $(OBJS) -lGLEW -lSDL2 -lGL

-include $(DEPS)
$(OBJS_D)%.o:	%.cpp | $(OBJS_D)
			$(CXX) $(FLAGS) -I/usr/include/SDL2 -D_REENTRANT -I$(INCS_D) -c $< -o $@

$(OBJS_D)	:
			mkdir -p $(OBJS_D)
			mkdir -p $(OBJS_D)srcs/
			mkdir -p $(OBJS_D)srcs/class/
			mkdir -p $(OBJS_D)srcs/utils/

leaks		:	all
			$(VALGRIND) ./$(NAME) $(ARGS)

run			:	all
			./$(NAME) $(ARGS)

debug		:
			$(MAKE) re DEBUG=yes

clean		:
			$(RM) $(OBJS_D)

fclean		:	clean
			$(RM) $(NAME)

re			:	fclean all

FORCE		:

.PHONY: all debug leaks run re clean fclean FORCE
