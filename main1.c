/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:31:14 by                   #+#    #+#             */
/*   Updated: 2022/03/26 14:03:50 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* A static variable for holding the line. */
//static char	*line_read = (char *) NULL;
int			g_exit_code = 0;

char	*ft_gets(void)
{
	static char	*line_read;

	line_read = (char *) NULL;
	if (line_read)
	{
		free(line_read);
		line_read = (char *) NULL;
	}
		line_read = readline("minishell> ");
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

int	ft_execute_cmd(t_command *cmd, int is_from_child)
{
	char	*scmd_name;

	if ((*(cmd->cur_scmds))->args && *((*(cmd->cur_scmds))->args) && \
		(cmd->nb_ofscmds == 1 || (cmd->nb_ofscmds > 1 && is_from_child)))
	{
		scmd_name = ((*(cmd->cur_scmds))->args)[0];
		if (!ft_strcmp(scmd_name, "export"))
			return (ft_execute_buildin(&ft_export, cmd, is_from_child));
		else if (!ft_strcmp(scmd_name, "unset"))
			return (ft_execute_buildin(&ft_unset, cmd, is_from_child));
		else if (!ft_strcmp(scmd_name, "env"))
			return (ft_execute_buildin(&ft_env, cmd, is_from_child));
		else if (!ft_strcmp(scmd_name, "echo"))
			return (ft_execute_buildin(&ft_echo, cmd, is_from_child));
		else if (!ft_strcmp(scmd_name, "cd"))
			return (ft_execute_buildin(&ft_cd, cmd, is_from_child));
		else if (!ft_strcmp(scmd_name, "exit"))
			return (ft_execute_buildin(&ft_exit, cmd, is_from_child));
		else if (!ft_strcmp(scmd_name, "pwd"))
			return (ft_execute_buildin(&ft_pwd, cmd, is_from_child));
	}
	return (ft_execute_inseparate_process(cmd, is_from_child));
}

void	ft_fill_and_execute_cmd(char **spliteds, t_env *env_s)
{
	t_command	*cmd;

	cmd = ft_parse(spliteds);
	ft_freestrs(spliteds);
	if (cmd)
	{
		cmd->env_s = env_s;
		ft_execute_cmd(cmd, 0);
	}
}

void	ft_process_read_line(char *s, t_env *env_s)
{
	char	**spliteds;

	if (s)
	{
		if (!ft_insert_var(&s, env_s))
		{
			spliteds = ft_advance_split(s, ' ');
			free(s);
			if (spliteds && *spliteds && !ft_validate_spec_order(spliteds))
				ft_fill_and_execute_cmd(spliteds, env_s);
			else
				free(spliteds);
		}
	}
	else
	{
		g_exit_code = 1;
		perror("minishell: ");
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*s;
	t_env	*env_s;

	(void)argc;
	(void)argv;
	g_exit_code = 0;
	env_s = ft_init_env(env);
	if (!env_s || ft_set_env_vals(env_s, 0))
		exit(g_exit_code);
	s = "";
	while (1)
	{
		ft_initial_sig_override(env_s);
		s = ft_gets();
		if (!s)
			break ;
		ft_sigint_for_parent_process(s, env_s);
		ft_process_read_line(ft_strdup(s), env_s);
	}
	printf("exit\n");
	ft_exit_program(env_s);
}
