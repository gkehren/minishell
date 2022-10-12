#include "minishell.h"

void	child_process(int *fd, int *fdd, char **env, t_list *lcmd)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)lcmd->content;
	close(fd[0]);
	dup2((*fdd), STDIN_FILENO);
	if (lcmd->next != NULL)
		dup2(fd[1], STDOUT_FILENO);
	if (execve(path_command(cmd->full_cmd[0], env), cmd->full_cmd, env) == -1)
		exit(1);
}

void	child_process_out(int *fd, int *fdd, char **env, t_list *lcmd)
{
	t_cmd	*cmd;
	int		outfile;

	(void)fdd;
	cmd = (t_cmd *)lcmd->content;
	outfile = open(get_token_content(lcmd),
			O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (outfile == -1)
		exit(1);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	dup2(outfile, STDOUT_FILENO);
	if (execve(path_command(cmd->full_cmd[0], env), cmd->full_cmd, env) == -1)
		exit(1);
	close(outfile);
}

void	child_process_in(int *fd, int *fdd, char **env, t_list *lcmd)
{
	t_cmd	*cmd;
	int	infile;

	(void)fdd;
	cmd = (t_cmd *)lcmd->content;
	infile = open(get_token_content(lcmd), O_RDONLY, 0777);
	if (infile == -1)
		exit(1);
	close(fd[0]);
	dup2(infile, STDIN_FILENO);
	if (execve(path_command(cmd->full_cmd[0], env), cmd->full_cmd, env) == -1)
		exit(1);
	close(infile);
}

int	get_next_line(char **line)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	r = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	free(buffer);
	return (r);
}

void	child_process_heredoc(char **env, t_list *lcmd)
{
	char	*limiter;
	char	*line;
	pid_t	reader;
	int		fd[2];

	(void)env;
	limiter = get_token_content(lcmd);
	if (pipe(fd) == -1)
		exit(1);
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		while (get_next_line(&line))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}
