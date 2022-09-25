#ifndef MINISHELL_H
# define MINISHELL_H

/*						INCLUDE BASIC HEADER						*/
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <string.h>

/*						INCLUDE OTHER HEADER						*/
# include "couleurs.h"
# include "struct.h"
# include "lexer.h"
# include "basics.h"
# include "free.h"
# include "tools.h"
# include "utils.h"
# include "builtins.h"

#endif