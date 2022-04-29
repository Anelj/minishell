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

int	ft_set_env_vals(t_env *env_s, int ret)
{
	t_env_list	*env_lst;
	t_env_list	*env_lst_prev;
	char		*env;
	char		*val;

	if (ft_find_el_or_place_toinsert(env_s, "SHLVL=", &env_lst, &env_lst_prev))
	{
		if (ft_isdigits(env_lst->val))
			val = ft_itoa(ft_atoi(env_lst->val) + 1);
		else
			return (0);
		if (!val)
			return (1);
		env = ft_strjoin("SHLVL=", val);
		if (!env)
		{
			free(val);
			return (1);
		}
		ret = ft_insert_env(env_s, env);
		free(val);
		free(env);
	}
	return (ret);
}

int	ft_setter(t_command *cmd, char *prev, char cwd[1024], char *pwd)
{
	char		*env;
	int			ret;

	if (ft_strcmp(pwd, "OLDPWD=") == 0)
		env = ft_strjoin("OLDPWD=", prev);
	else
		env = ft_strjoin("PWD=", cwd);
	if (!env)
		return (1);
	ret = ft_insert_env(cmd->env_s, env);
	free(env);
	return (ret);
}

int	ft_set_pwd_oldpwd(t_command *cmd, char *prev)
{
	t_env_list	*env_lst;
	t_env_list	*env_lst_prev;
	char		cwd[1024];
	int			ret;

	ret = 0;
	getcwd(cwd, sizeof(cwd));
	if (ft_find_el_or_place_toinsert(cmd->env_s, "PWD=", &env_lst, \
		&env_lst_prev))
	{
		ret = ft_setter(cmd, prev, cwd, "PWD=");
		if (ret == 1)
			return (1);
	}
	if (ft_find_el_or_place_toinsert(cmd->env_s, "OLDPWD=", &env_lst, \
		&env_lst_prev))
	{
		ret = ft_setter(cmd, prev, cwd, "OLDPWD=");
		if (ret == 1)
			return (1);
	}
	return (ret);
}

int	ft_isdigits(char *s)
{
	if (*s == '+' || *s == '-')
		s++;
	while (ft_isdigit((int)*s))
		s++;
	if (*s)
		return (0);
	return (1);
}
