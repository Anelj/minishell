/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:31:14 by                   #+#    #+#             */
/*   Updated: 2022/03/03 17:17:16 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipe1(int *fds, int in, int out)
{
	int	stat;

	if (pipe(fds) < 0)
	{
		stat = 0;
		close(in);
		close(out);
		close(0);
		close(1);
		while (wait(&stat))
			stat++;
		g_exit_code = 1;
		perror("minishell: ");
		return (1);
	}
	return (0);
}

int	ft_open(char *file, int toread, int toappend, int toclose)
{
	int	fd;

	if (!toread && !toappend)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (!toread && toappend)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (toread && !toappend)
		fd = open(file, O_RDONLY);
	if (toread && toappend)
		fd = open(file, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0664);
	if (fd < 0)
	{
		if (toclose >= 0)
			close(toclose);
		g_exit_code = 1;
		write(2, "minishell ", 10);
		write(2, file, ft_strlen(file));
		write(2, ": ", 2);
		perror("");
		return (-1);
	}
	return (fd);
}

pid_t	ft_fork1(int in, int out)
{
	pid_t	pid;
	int		stat;

	pid = fork();
	if (pid < 0)
	{
		close(in);
		close(out);
		close(1);
		close(0);
		while (wait(&stat) > 0)
			stat++;
		g_exit_code = 1;
		perror("minishell: ");
	}
	return (pid);
}

int	ft_getexitcode(int stat, int exit)
{
	if (WIFSIGNALED(stat))
	{
		exit = 128 + WTERMSIG(stat);
	}
	else if (WIFEXITED(stat))
	{
		exit = WEXITSTATUS(stat);
	}
	return (exit);
}
