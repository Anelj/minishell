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

int	ft_dup_redir_fdout(t_redir *redir)
{
	int	fdout;

	if (!(redir->isdouble))
		fdout = ft_open(redir->redir, 0, 0, -1);
	else
		fdout = ft_open(redir->redir, 0, 1, -1);
	return (fdout);
}

int	ft_dup_redir(t_redir *redir, t_command *cmd, int is_from_child)
{
	int	fdin;
	int	fdout;

	while (redir->redir)
	{
		if (redir->isin)
		{
			fdin = ft_open(redir->redir, 1, 0, -1);
			if (redir->isdouble)
				unlink(redir->redir);
			if (ft_check_and_exit(fdin, cmd, is_from_child))
				return (1);
			ft_dup2_close(fdin, 0);
		}
		else if (!(redir->isin))
		{
			fdout = ft_dup_redir_fdout(redir);
			if (ft_check_and_exit(fdout, cmd, is_from_child))
				return (1);
			ft_dup2_close(fdout, 1);
		}
		redir++;
	}
	return (0);
}

int	ft_dup_pipes(int *fdin, int is_last_scmd, int tmpout, int tmpin)
{
	int	fdout;
	int	fdpipe[2];

	dup2(*fdin, 0);
	close(*fdin);
	if (is_last_scmd)
		fdout = dup(tmpout);
	else
	{
		if (ft_pipe1(fdpipe, tmpin, tmpout))
		{
			return (1);
		}
		fdout = fdpipe[1];
		*fdin = fdpipe[0];
	}
	dup2(fdout, 1);
	close(fdout);
	return (0);
}

void	ft_set_from_tmp_in_out(int tmpin, int tmpout)
{
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpout);
	close(tmpin);
}

void	ft_set_tmp_in_and_out(int *tmpin, int *tmpout, int *fdin)
{
	*tmpin = dup(0);
	*tmpout = dup(1);
	*fdin = dup(*tmpin);
}
