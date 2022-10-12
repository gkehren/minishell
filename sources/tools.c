#include "minishell.h"

static void	print_color_text(char *color, char *content)
{
	couleur(color);
	printf("%s", content);
	couleur("0");
}

void	print_token_lex(t_list *lst)
{
	t_token_lex	*tmp;

	while (lst)
	{
		tmp = (t_token_lex *)lst->content;
		if (tmp->token == WORD)
			print_color_text(VERT, "WORD");
		else if (tmp->token == PIPE)
			print_color_text(JAUNE, "PIPE");
		else if (tmp->token == IN)
			print_color_text(BLEU, "IN");
		else if (tmp->token == OUT)
			print_color_text(BLEU, "OUT");
		else if (tmp->token == IN_HEREDOC)
			print_color_text(BLEU, "IN_HEREDOC");
		else if (tmp->token == OUT_APPEND)
			print_color_text(BLEU, "OUT_APPEND");
		printf(" ");
		lst = lst->next;
	}
	printf("\n");
}

void	print_cmd(t_list *lst)
{
	t_cmd	*cmd;
	int		i;

	while (lst)
	{
		i = 0;
		cmd = (t_cmd *)lst->content;
		printf("FULL CMD : { ");
		while (cmd->full_cmd && cmd->full_cmd[i + 1])
		{
			printf("[%s] ", cmd->full_cmd[i]);
			i++;
		}
		if (cmd->full_cmd)
			printf("[%s]", cmd->full_cmd[i]);
		printf(" }\n");
		printf("argc : %d\n", cmd->argc);
		if (cmd->builtin != NULL)
			printf("builtin : 1\n");
		else
			printf("builtin : 0\n");
		print_token_lex(cmd->token_files);
		printf("\n\n");
		lst = lst->next;
	}
}
