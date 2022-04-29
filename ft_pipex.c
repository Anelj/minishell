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

int	ft_parent_wait_exec(int tmpin, int tmpout, pid_t child, t_command *cmd)
{
	int	stat;

	ft_freecmd(&cmd);
	ft_set_from_tmp_in_out(tmpin, tmpout);
	if (child >= 0)
		waitpid(child, &stat, 0);
	while (wait(0) > 0)
		child++;
	if (!g_exit_code)
	{
		g_exit_code = ft_getexitcode(stat, 0);
		if (g_exit_code == 131)
			printf("Quit: 3\n");
		return (0);
	}
	else
		return (1);
}

void	ft_execute(t_command *cmd, int ret, int tmpin, int tmpout)
{
	t_env	*env_s;

	env_s = cmd->env_s;
	ft_set_from_tmp_in_out(tmpin, tmpout);
	if (ret == -1 || ret == -2 || ret == -3)
	{
		printf("exit\n");
		ft_exit_ers(ret, cmd);
		if (ret != -2)
		{
			ft_freecmd(&cmd);
			ft_exit_program(env_s);
		}
	}
	ft_freecmd(&cmd);
}

int	ft_execute_buildin(int (*f)(t_command *), t_command *cmd, int is_from_child)
{
	int		ret;
	int		tmpin;
	int		tmpout;
	int		fdin;

	if (!is_from_child)
	{
		ft_set_tmp_in_and_out(&tmpin, &tmpout, &fdin);
		if (ft_dup_redir((*(cmd->cur_scmds))->redir, cmd, is_from_child))
		{
			ft_set_from_tmp_in_out(tmpin, tmpout);
			return (1);
		}
	}
	ret = f(cmd);
	if (!is_from_child)
	{
		ft_execute(cmd, ret, tmpin, tmpout);
		return (ret);
	}
	ft_exit_ers(ret, cmd);
	ft_free_env(cmd->env_s);
	ft_freecmd(&cmd);
	exit(g_exit_code);
}

int	ft_execute_inseparate_process(t_command *cmd, int is_from_child)
{
	if (is_from_child)
	{
		if (!((*(cmd->cur_scmds))->args) || !(*((*(cmd->cur_scmds))->args)))
			ft_execve_exit(cmd, 0);
		if (!ft_get_cmd((*(cmd->cur_scmds))->args, cmd->env_s))
		{
			ft_check_and_exit(-1, cmd, is_from_child);
		}
		execve(*((*(cmd->cur_scmds))->args), (*(cmd->cur_scmds))->args, \
		cmd->env_s->env_ar);
		ft_execve_exit(cmd, 1);
		return (1);
	}
	else
		return (ft_create_child_and_execute(cmd));
}

int	ft_create_child_and_execute(t_command *cmd)
{
	int		tmpin;
	int		tmpout;
	int		fdin;
	pid_t	child;

	ft_set_tmp_in_and_out(&tmpin, &tmpout, &fdin);
	while ((cmd->cur_scmds) && *(cmd->cur_scmds))
	{
		if (ft_dup_pipes(&fdin, cmd->cur_scmds - cmd->scmds == \
		cmd->nb_ofscmds - 1, tmpout, tmpin))
			return (ft_parent_wait_exec(tmpin, tmpout, -1, cmd));
		child = ft_fork1(tmpin, tmpout);
		if (child < 0)
			return (ft_parent_wait_exec(tmpin, tmpout, child, cmd));
		if (!child)
			ft_proccess_child(tmpin, tmpout, fdin, cmd);
		cmd->cur_scmds = cmd->cur_scmds + 1;
	}
	g_exit_code = 0;
	return (ft_parent_wait_exec(tmpin, tmpout, child, cmd));
}
