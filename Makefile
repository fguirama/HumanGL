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

UNAME		=	$(shell uname -s)

ifeq ($(UNAME), Linux)
FLAGS_LIB	:=	-lGLEW -lSDL2 -lGL
FLAGS_INC	:=	-I/usr/include/SDL2 -D_REENTRANT
endif

ifeq ($(UNAME), Darwin)
FLAGS_LIB	:=	-L/opt/homebrew/lib -lGLEW -lSDL2 -framework OpenGL
FLAGS_INC	:=	-I/opt/homebrew/include
endif

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

$(NAME)		:	$(OBJS_D) $(OBJS)
#			$(CXX) $(FLAGS) -L/opt/homebrew/lib -lGLEW -lSDL2 -framework OpenGL -o $(NAME) $(OBJS) // todo test sur linux
#			$(CXX) $(FLAGS) -I/usr/include/SDL2 -D_REENTRANT -o $(NAME) $(OBJS) -lGLEW -lSDL2 -lGL
			$(CXX) $(FLAGS) $(FLAGS_LIB) -o $(NAME) $(OBJS)

-include $(DEPS)
$(OBJS_D)%.o:	%.cpp
			$(CXX) $(FLAGS) $(FLAGS_INC) -I$(INCS_D) -c $< -o $@

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
