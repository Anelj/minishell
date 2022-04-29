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

void	ft_freescmd(t_simple_command *scmd)
{
	int	i;

	i = 0;
	while ((scmd->args)[i])
		free((scmd->args)[i++]);
	free((scmd->args));
	i = 0;
	while ((scmd->redir)[i].redir)
	{
		free((scmd->redir)[i].redir);
		i++;
	}
	free(scmd->redir);
	free(scmd);
}

void	ft_freecmd(t_command **cmd)
{
	t_command			*tmp;
	int					i;

	if (!cmd)
		return ;
	tmp = *cmd;
	i = 0;
	while (tmp && (tmp->scmds) && (tmp->scmds)[i])
	{
		ft_freescmd((tmp->scmds)[i++]);
	}
	if (tmp)
		free(tmp->scmds);
	free(tmp);
	*cmd = NULL;
}

void	ft_execve_exit(t_command *cmd, int ex_code)
{
	close(0);
	close(1);
	ft_free_env(cmd->env_s);
	ft_freecmd(&cmd);
	exit(ex_code);
}

char	**ft_freescmd_exit_code_ret_null(t_simple_command *scmd)
{
	g_exit_code = 1;
	perror("minishell: ");
	ft_freescmd(scmd);
	return (NULL);
}

int	ft_check_and_exit(int fd, t_command *cmd, int is_from_child)
{
	if (fd < 0 && is_from_child)
	{
		close(0);
		close(1);
		ft_free_env(cmd->env_s);
		ft_freecmd(&cmd);
		exit(g_exit_code);
	}
	else if (fd < 0)
	{
		ft_freecmd(&cmd);
		return (1);
	}
	return (0);
}
