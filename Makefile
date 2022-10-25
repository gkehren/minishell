NAME = minishell

SRC_PATH = sources/
OBJ_PATH = obj/

SRC_NAME = 	minishell.c						\
			monitor.c						\
			tools.c 						\
			basics/basic_list.c				\
			basics/basic_list2.c			\
			basics/basic_str.c				\
			basics/basic_str2.c				\
			basics/ft_split.c				\
			basics/ft_itoa.c				\
			basics/ft_atoi.c				\
			basics/get_next_line_utils.c 	\
			basics/get_next_line.c 			\
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
			parser/check_builtins.c 		\
			signals/signals.c 				\
			utils/utils.c 					\
			utils/handle_struct.c			\
			utils/check_char.c				\
			utils/free.c					\
			utils/print_error.c  			\
			exec/exec.c 					\
			exec/utils.c					\
			exec/child.c 					\
			exec/builtins_exec.c 			\
			exec/files.c 					\
			exec/files2.c 					\
			exec/heredoc.c 					\
			exec/heredoc2.c 				\
			exec/parent.c 					\
			exec/path.c 					\

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
