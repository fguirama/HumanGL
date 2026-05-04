# ---------- VARIABLE ----------------------------------------------------------------- #
INCS		:=	\
				class/x.hpp\
				humandGL.h\

SRCS		:=	\
				class/x.cpp\
				utils/x.cpp\
				main.cpp\

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
IFLAGS		:=	-I$(INCS_D) -I$(IRCLIB_I)
DFLAGS		=	-MMD -MP -MT $@ -MF $(DEPS_D)$*.d
CFLAGS		=	-Wall -Wextra -Werror -std=c++98 -g3 $(IFLAGS)


# ---------- DEBUG -------------------------------------------------------------------- #
DEBUG		=	no

ifeq ($(DEBUG), yes)
	CFLAGS	+=	-fsanitize=address -DDEBUG=true
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
			$(CXX) $(CFLAGS) -o $(NAME) $(OBJS) $(IRCLIB_A)

$(OBJS)		:	$(OBJS_D)%.o: $(SRCS_D)%.cpp | $(OBJS_D) $(DEPS_D)
			$(CXX) $(CFLAGS) $(DFLAGS) -c $< -o $@

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
			$(MAKE) clean -C $(IRCLIB_D)

fclean		:	clean
			$(RM) $(NAME)
			$(MAKE) fclean -C $(IRCLIB_D)

re			:	fclean all

FORCE		:

.PHONY: all debug bonus leaks run re clean fclean FORCE
