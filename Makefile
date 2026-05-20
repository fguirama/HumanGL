# ---------- VARIABLE ----------------------------------------------------------------- #
INCS		:=	\
				humanGL.h\
				enum.h\
				class/Window.hpp\
				class/BodyPart.hpp\
				class/Character.hpp\
				class/Matrix4.hpp\
				class/MatrixStack.hpp\
				class/Vector4.hpp\
				class/Color.hpp

SRCS		:=	\
				class/Window.cpp\
				class/BodyPart.cpp\
				class/Character.cpp\
				class/Matrix4.cpp\
				class/MatrixStack.cpp\
				class/Vector4.cpp\
				class/Color.cpp\
				utils/draw.cpp\
				utils/animation.cpp\
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
-include $(DEPS)
.DEFAULT_GOAL = all

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(IRCLIB_A)
			$(CXX) $(FLAGS) -I/usr/include/SDL2 -D_REENTRANT -o $(NAME) $(OBJS) -lGLEW -lSDL2 -lGL

$(OBJS)		:	$(OBJS_D)%.o: $(SRCS_D)%.cpp | $(OBJS_D) $(DEPS_D)
			$(CXX) $(FLAGS) -I/usr/include/SDL2 -D_REENTRANT -I$(INCS_D) -c $< -o $@

$(OBJS_D)	:
			mkdir -p $(OBJS_D)
			mkdir -p $(OBJS_D)class/
			mkdir -p $(OBJS_D)utils/

$(DEPS_D)	:
			mkdir -p $(DEPS_D)
			mkdir -p $(DEPS_D)class/
			mkdir -p $(DEPS_D)utils/

leaks		:	all
			$(VALGRIND) ./$(NAME) $(ARGS)

run			:	all
			./$(NAME) $(ARGS)

debug		:
			$(MAKE) re DEBUG=yes

clean		:
			$(RM) $(OBJS) $(OBJS_D) $(DEPS_D)

fclean		:	clean
			$(RM) $(NAME)

re			:	fclean all

FORCE		:

.PHONY: all debug leaks run re clean fclean FORCE
