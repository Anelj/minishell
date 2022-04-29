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

int	ft_replace_env_lst_el_val(t_env_list *env_lst, char *env, size_t key_len)
{
	free(env_lst->val);
	env_lst->val = ft_strdup(env + key_len + 1);
	if (!(env_lst->val))
		return (1);
	return (0);
}

void	ft_fill_env_ar_el(t_env *env_s, char *env_cpy, char	**tmp)
{
	int	i;

	i = 0;
	while (env_s->env_ar && env_s->env_ar[i])
	{
		tmp[i] = env_s->env_ar[i];
		i++;
	}
	tmp[i] = env_cpy;
	free(env_s->env_ar);
	env_s->env_ar = tmp;
	env_s->avail_nb_env_ar += 42;
	env_s->nb_keys = env_s->nb_keys + 1;
}

int	ft_insert_env_ar_el(t_env *env_s, char *env)
{
	char	*env_cpy;
	char	**tmp;

	env_cpy = ft_strdup(env);
	if (!env_cpy)
		return (1);
	if (env_s->avail_nb_env_ar > env_s->nb_keys + 1)
		env_s->env_ar[env_s->nb_keys++] = env_cpy;
	else
	{
		tmp = malloc(sizeof(char *) * (env_s->avail_nb_env_ar + 42));
		if (!tmp)
		{
			free(env_cpy);
			return (1);
		}
		ft_bzero(tmp, sizeof(char *) * (env_s->avail_nb_env_ar + 42));
		ft_fill_env_ar_el(env_s, env_cpy, tmp);
	}
	return (0);
}

int	ft_insert_env_helper(
		t_env *env_s, char *env, t_env_list *env_lst, size_t key_len)
{
	if (env_lst && env_lst->key && !ft_strncmp(env_lst->key, env, key_len)
		&& ft_strlen(env_lst->key) == key_len && \
		env_lst->val && ft_is_val_present(env, key_len))
	{
		if (ft_replace_env_ar_el(env_s->env_ar, env, key_len)
			|| ft_replace_env_lst_el_val(env_lst, env, key_len))
			return (1);
	}
	else if (env_lst && env_lst->key && !ft_strncmp(env_lst->key, env, \
		key_len) && ft_strlen(env_lst->key) == key_len && \
		!(env_lst->val) && ft_is_val_present(env, key_len))
	{
		if (ft_replace_env_lst_el_val(env_lst, env, key_len)
			|| ft_insert_env_ar_el(env_s, env))
			return (1);
	}
	else
		return (-1);
	return (0);
}

int	ft_insert_env(t_env *env_s, char *env)
{
	t_env_list	*env_lst;
	t_env_list	*env_lst_prev;
	size_t		key_len;
	int			ret;

	if (ft_validate_key(env, "export"))
		return (0);
	key_len = ft_get_key_len(env);
	ft_find_el_or_place_toinsert(env_s, env, &env_lst, &env_lst_prev);
	ret = ft_insert_env_helper(env_s, env, env_lst, key_len);
	if (ret >= 0)
		return (ret);
	if ((!env_lst || ft_strncmp(env_lst->key, env, key_len))
		&& !ft_is_val_present(env, key_len))
	{
		if (ft_insert_env_lst_el(env_s, env_lst_prev, env, key_len))
			return (1);
	}
	else if (ft_is_val_present(env, key_len))
		if (ft_insert_env_lst_el(env_s, env_lst_prev, env, key_len) \
		|| ft_insert_env_ar_el(env_s, env))
			return (1);
	return (0);
}
