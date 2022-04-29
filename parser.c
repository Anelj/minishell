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

t_simple_command	*ft_create_scmd(char **s)
{
	t_simple_command	*scmd;

	scmd = malloc(sizeof(t_simple_command));
	if (!scmd)
	{
		ft_set_exit_code_and_display_er(1);
		return (NULL);
	}
	ft_bzero(scmd, sizeof(t_simple_command));
	scmd->args = malloc(sizeof(char *) * (ft_args_count(s) + 1));
	if (scmd->args)
		ft_bzero(scmd->args, sizeof(char *) * (ft_args_count(s) + 1));
	scmd->redir = \
			malloc(sizeof(t_redir) * (ft_out_count(s) + ft_in_count(s) + 1));
	if (scmd->redir)
		ft_bzero(scmd->redir, sizeof(t_redir) * (ft_out_count(s) + \
		ft_in_count(s) + 1));
	if (!scmd->args || !scmd->redir)
	{
		ft_set_exit_code_and_display_er(1);
		ft_freescmd(scmd);
		return (NULL);
	}
	return (scmd);
}

char	**ft_fill_scmd(char **s, t_simple_command *scmd)
{
	int	args_i;
	int	j;

	args_i = 0;
	j = 0;
	while (*s && !ft_issep_cmd(*s))
	{
		if (ft_is_spec(*s) != -1)
		{
			if (!ft_set_redir(scmd, &j, s))
				return (NULL);
			s++;
		}
		else
		{
			scmd->args[args_i] = ft_strdup(*s);
			if (!(scmd->args[args_i]))
				return (ft_freescmd_exit_code_ret_null(scmd));
			args_i++;
		}
		s++;
	}
	return (s);
}

int	ft_add_curr_cmd(t_command *cmd, char	**s)
{
	int					i;

	i = 0;
	while (i < cmd->nb_ofscmds)
	{
		*(cmd->scmds + i) = ft_get_scmd(&s);
		if (!(*(cmd->scmds + i)))
		{
			ft_freecmd(&cmd);
			return (1);
		}
		i++;
	}
	cmd->cur_scmds = (cmd->scmds);
	return (0);
}

t_command	*ft_parse(char **s1)
{
	t_command			*cmd;
	char				**s;

	s = s1;
	cmd = malloc(sizeof(t_command));
	if (!cmd)
	{
		g_exit_code = 1;
		perror("minishell: ");
		return (NULL);
	}
	cmd->scmds = malloc((ft_scmd_count(s) + 1) * sizeof(t_simple_command *));
	if (!(cmd->scmds))
	{
		free(cmd);
		g_exit_code = 1;
		perror("minishell: ");
		return (NULL);
	}
	ft_bzero(cmd->scmds, (ft_scmd_count(s) + 1) * sizeof(t_simple_command *));
	cmd->nb_ofavail_scmds = 10;
	cmd->nb_ofscmds = ft_scmd_count(s);
	if (ft_add_curr_cmd(cmd, s))
		return (NULL);
	return (cmd);
}
