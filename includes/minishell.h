/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:32:00 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/28 00:14:21 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <limits.h>
# include <errno.h>
# include <signal.h>

/*						INCLUDE OTHER HEADER						*/
# include "struct.h"
# include "lexer.h"
# include "basics.h"
# include "free.h"
# include "utils.h"
# include "builtins.h"
# include "expanser.h"
# include "parser.h"
# include "exec.h"
# include "signals.h"
# include "monitor.h"

# define BUFFER_SIZE 42

extern t_global	g_global;

#endif
