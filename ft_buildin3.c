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

void	ft_export_print(t_env_list	*env)
{
	if (env->val)
		printf("declare -x %s=\"%s\"\n", env->key, env->val);
	else
		printf("declare -x %s NULL value\n", env->key);
}

int	ft_export(t_command *cmd)
{
	t_env_list	*env;
	int			i;

	i = 1;
	g_exit_code = 0;
	if (((*(cmd->cur_scmds))->args)[i])
	{
		while (((*(cmd->cur_scmds))->args)[i])
		{
			if (ft_insert_env(cmd->env_s, ((*(cmd->cur_scmds))->args)[i]))
				return (1);
			i++;
		}
		if (g_exit_code)
			return (1);
		return (0);
	}
	env = cmd->env_s->env_lst;
	while (env)
	{
		ft_export_print(env);
		env = env->next;
	}
	return (0);
}

void	ft_write_cd(char **args)
{
	g_exit_code = 1;
	write(2, "minishell: cd: ", 15);
	write(2, args[1], ft_strlen(args[1]));
	write(2, ": ", 2);
	perror("");
}

int	ft_cd(t_command *cmd)
{
	char	**args;
	char	cwd[1024];

	g_exit_code = 0;
	args = (*(cmd->cur_scmds))->args;
	if (!args[1])
		return (1);
	if (args[1] && (args[2]))
	{
		g_exit_code = 1;
		write(2, "minishell: cd: too many arguments\n", 34);
		return (1);
	}
	getcwd(cwd, sizeof(cwd));
	if (chdir(args[1]) < 0)
	{
		ft_write_cd (args);
		return (1);
	}
	if (ft_set_pwd_oldpwd(cmd, cwd))
	{
		perror("minishell: ");
		return (1);
	}
	return (0);
}
