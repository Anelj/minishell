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

int	ft_validate_key(char *env, char *cmdname)
{
	size_t	l;

	l = ft_get_key_len(env);
	if (l == 0 || ft_isdigit(env[0]) || \
	((env[l]) && !ft_strcmp("unset", cmdname))
		|| ((env[l]) && env[l] != '='))
	{
		write(2, "minishell: ", 11);
		write(2, cmdname, ft_strlen(cmdname));
		write(2, ": '", 3);
		write(2, env, ft_strlen(env));
		write(2, "': not a valid identifier\n", 26);
		g_exit_code = 1;
		return (1);
	}
	return (0);
}

size_t	ft_get_key_len(char *env)
{
	size_t	l;

	l = 0;
	while (env && env[l] && (env[l] == '_' || ft_isalnum(env[l])))
		l++;
	return (l);
}

int	ft_is_val_present(char *env, size_t l)
{
	if (env && env[l] == '=')
		return (1);
	return (0);
}

int	ft_find_el_or_place_toinsert(t_env *env_s, char *env,
	t_env_list **env_lst, t_env_list	**env_lst_prev)
{
	size_t	key_len;

	key_len = ft_get_key_len(env);
	*env_lst = env_s->env_lst;
	*env_lst_prev = NULL;
	while (env_lst && *env_lst && (*env_lst)->key && \
	ft_strncmp((*env_lst)->key, env, key_len) < 0)
	{
		*env_lst_prev = *env_lst;
		*env_lst = (*env_lst)->next;
	}
	return (env_lst && *env_lst && (*env_lst)->key && \
			!ft_strncmp((*env_lst)->key, env, key_len) \
			&& key_len == ft_strlen((*env_lst)->key));
}
