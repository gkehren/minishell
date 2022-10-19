#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

/*						PARSER						*/
t_list	*generate_cmd(t_list **token_list, t_list **venv);

/*						PARSER_CHECKER						*/
int		parser_checker(t_list **token_list);

/*						PARSER_TOOLS						*/
char	**new_full_cmd(char **full_cmd, char *cmd);
int		new_token_files(t_list **token_files, t_token_lex *token_redir, t_token_lex *token_word);
void	init_argc_cmd(t_list *cmd);

/*						CHECK_BUILTINS						*/
void	init_builtins_cmd(t_list *cmd);

#endif