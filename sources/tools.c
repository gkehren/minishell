#include "minishell.h"

static void	print_color_text(char *color, char *content)
{
	couleur(color);
	printf("%s", content);
	couleur("0");
}

void	print_token_lex(t_token_lex *lst)
{
	while (lst)
	{
		if (lst->token == WORD)
			print_color_text(VERT, "WORD");
		else if (lst->token == PIPE)
			print_color_text(JAUNE, "PIPE");
		else if (lst->token == IN)
			print_color_text(BLEU, "IN");
		else if (lst->token == OUT)
			print_color_text(BLEU, "OUT");
		else if (lst->token == IN_HEREDOC)
			print_color_text(BLEU, "IN_HEREDOC");
		else if (lst->token == OUT_APPEND)
			print_color_text(BLEU, "OUT_APPEND");
		printf(" ");
		lst = lst->next;
	}
	printf("\n");
}