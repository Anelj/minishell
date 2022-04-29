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

int	ft_pwd(t_command *cmd)
{
	char	cwd[1024];

	(void)cmd;
	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
	{
		perror("minishell: ");
		return (1);
	}
	return (0);
}

int	ft_exit(t_command *cmd)
{
	char	**args;

	args = (*(cmd->cur_scmds))->args;
	if (!args[1])
		return (-1);
	else if (!args[2] && ft_isdigits(args[1]))
	{
		g_exit_code = ft_atoi(args[1]);
		return (-1);
	}
	else if (!ft_isdigits(args[1]))
	{
		g_exit_code = 2;
		return (-3);
	}
	else
	{
		g_exit_code = 1;
		return (-2);
	}
}

int	ft_unset(t_command *cmd)
{
	char		**args;
	t_env_list	*env_lst;
	t_env_list	*env_lst_prev;
	size_t		key_len;

	g_exit_code = 0;
	args = (*(cmd->cur_scmds))->args;
	while (*(++args))
	{
		if (!ft_validate_key(*args, "unset"))
		{
			key_len = ft_get_key_len(*args);
			if (ft_find_el_or_place_toinsert(cmd->env_s, *args, &env_lst, \
			&env_lst_prev))
			{
				if (env_lst->val)
					ft_del_env_ar_el(cmd->env_s->env_ar, *args, key_len);
				ft_del_env_lst_el(env_lst, env_lst_prev);
			}
		}
	}
	if (g_exit_code)
		return (1);
	return (0);
}

int	ft_echo(t_command *cmd)
{
	char	**args;
	int		i;
	int		fl;

	g_exit_code = 0;
	i = 1;
	args = (*(cmd->cur_scmds))->args;
	while (args[i] && !ft_strcmp(args[i], "-n"))
		i++;
	fl = i;
	while (args[i])
	{
		if (i == fl)
			printf("%s", args[i]);
		else
			printf(" %s", args[i]);
		i++;
	}
	if ((((*(cmd->cur_scmds))->args)[1] \
	&& ft_strcmp(((*(cmd->cur_scmds))->args)[1], "-n"))
		|| !((*(cmd->cur_scmds))->args)[1])
	{
		printf("\n");
	}
	return (0);
}

int	ft_env(t_command *cmd)
{
	char	**env_ar;

	g_exit_code = 0;
	env_ar = cmd->env_s->env_ar;
	while (*env_ar)
	{
		printf("%s\n", *env_ar);
		env_ar++;
	}
	return (0);
}
