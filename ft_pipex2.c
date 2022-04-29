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

void	ft_proccess_child(int tmpin, int tmpout, int fdin, t_command *cmd)
{
	close(tmpin);
	close(tmpout);
	close(fdin);
	ft_sig_return_def_behavior(cmd);
	ft_dup_redir((*(cmd->cur_scmds))->redir, cmd, 1);
	ft_execute_cmd(cmd, 1);
}

void	ft_exit_ers(int ret, t_command *cmd)
{
	if (ret == -2)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
	}
	if (ret == -3)
	{
		write(2, "minishell: exit: ", 17);
		write(2, ((*(cmd->cur_scmds))->args)[1], \
		ft_strlen(((*(cmd->cur_scmds))->args)[1]));
		write(2, ": numeric argument required\n", 28);
	}
}
