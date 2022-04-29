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

int	ft_split_var(char ***spl_var, char *var, char *string)
{
	*spl_var = ft_split(var, ' ');
	free(var);
	if (!(*spl_var))
	{
		free(string);
		g_exit_code = 1;
		perror("minishell: ");
		return (1);
	}
	return (0);
}

int	ft_get_len_and_strdup_str_before_var_char(
		size_t *l, char **string, char **tmp, char **spl_var)
{
	*l = ft_strlen(*string);
	if (ft_strdup_helper(string, tmp))
	{
		ft_freestrs(spl_var);
		free(*string);
		return (1);
	}
	return (0);
}

int	ft_env_is_digit_or_exit_code(char **s, char **var)
{
	*s = *s + 2;
	if (*(*s - 1) == '?')
	{
		*var = ft_itoa(g_exit_code);
		if (!(*var))
		{
			g_exit_code = 1;
			perror("minishell: ");
			return (1);
		}
		return (0);
	}
	return (0);
}

int	ft_env_value(t_env_list *env_lst, char **var)
{
	if (!env_lst || !(env_lst->val))
		return (0);
	*var = ft_strdup(env_lst->val);
	if (!(*var))
	{
		g_exit_code = 1;
		perror("minishell: ");
		return (1);
	}
	return (0);
}

int	ft_find_envvar(char **s, t_env *env_s, char **var)
{
	char		*tmp;
	int			i;
	t_env_list	*env_lst;

	tmp = *s;
	env_lst = env_s->env_lst;
	if (ft_isdigit(*(*s + 1)) || *(*s + 1) == '?')
	{
		return (ft_env_is_digit_or_exit_code(s, var));
	}
	tmp++;
	i = 0;
	while (tmp[i] && (ft_isalnum(tmp[i]) || tmp[i] == '_'))
		i++;
	if (!i)
		return (0);
	while (env_lst && env_lst->key && (ft_strncmp(env_lst->key, tmp, i) \
			|| (int)ft_strlen(env_lst->key) != i))
	{
		env_lst = env_lst->next;
	}
	*s = *s + i + 1;
	return (ft_env_value(env_lst, var));
}
