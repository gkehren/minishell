NAME = minishell

SRC_PATH = sources/
OBJ_PATH = obj/

SRC_NAME = 	minishell.c						\
			basics/basic_list.c				\
			basics/basic_list2.c			\
			basics/basic_str.c				\
			basics/basic_str2.c				\
			basics/ft_split.c				\
			basics/ft_itoa.c				\
			builtins/env/handle_env.c		\
			builtins/env/handle_env2.c		\
			builtins/env/parsing_export.c	\
			builtins/env/env_tools.c		\
			builtins/env/unset.c			\
			builtins/env/env.c				\
			builtins/env/export.c			\
			builtins/pwd.c 					\
			builtins/cd.c 					\
			builtins/echo.c 				\
			builtins/exit.c					\
			expanser/clean_expand.c 		\
			expanser/clean_expand2.c		\
			expanser/expand_word.c			\
			expanser/expand_word2.c			\
			expanser/expanser.c 			\
			lexer/lexer.c					\
			lexer/token_creation.c 			\
			parser/parser.c 				\
			parser/parser_checker.c 		\
			parser/parser_tools.c 			\
			utils/utils.c 					\
			utils/handle_struct.c			\
			utils/check_char.c				\
			utils/free.c					\
			tools.c 						\
			exec/exec.c 					\
			exec/utils.c					\

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
