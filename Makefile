NAME = minishell

SRC_PATH = sources/
OBJ_PATH = obj/

SRC_NAME = 	minishell.c						\
			basics/basic_list.c				\
			basics/basic_list2.c			\
			basics/basic_str.c				\
			basics/ft_split.c				\
			builtins/env/handle_env.c		\
			builtins/env/handle_env2.c		\
			builtins/env/parsing_export.c	\
			builtins/env/env_tools.c		\
			builtins/env/unset.c			\
			builtins/env/env.c				\
			builtins/env/export.c			\
			clean/free.c					\
			lexer/lexer.c					\
			lexer/token_creation.c 			\
			utils/utils.c 					\
			utils/handle_struct.c			\
			tools.c 						\

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = -I includes

CC = cc
FLAGS = -Wall -Wextra -Werror -g
LIBS = -lreadline
RM = @rm -rf

all: $(NAME)

$(NAME): $(OBJ)
		@echo "Build $(NAME)"
		@$(CC) $(FLAGS) $(INC) $(OBJ) -o $(NAME) $(LIBS)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
		mkdir -p $(@D)
		$(CC) $(FLAGS) $(INC) -o $@ -c $<

skiperror: $(OBJS)
			$(CC) -o $(NAME) $(SRCS) -lpthread

fsa:	$(OBJS)
		$(CC) -fsanitize=address $(FLAGS) -o $@ $(SRCS)

clean:
		$(RM) $(OBJ_PATH)

fclean:	clean
		$(RM) $(NAME)

re:	fclean
	make all

.PHONY: all clean fclean re