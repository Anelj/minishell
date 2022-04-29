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

int	ft_check_env_lst_el(char *env, size_t key_len, t_env_list	*env_el)
{
	size_t		len;

	len = ft_strlen(env);
	env_el->val = ft_strdup(env + key_len + 1);
	if (!(env_el->val))
	{
		free(env_el->key);
		free(env_el);
		g_exit_code = 1;
		perror("minishell: ");
		return (0);
	}
	env_el->val_len = len - key_len - 1;
	return (1);
}

t_env_list	*ft_create_env_lst_el(char *env, size_t key_len)
{
	t_env_list	*env_el;

	env_el = malloc(sizeof(t_env_list));
	if (!env_el)
	{
		ft_set_exit_code_and_display_er(1);
		return (NULL);
	}
	ft_bzero(env_el, sizeof(t_env_list));
	env_el->key = malloc(key_len + 1);
	if (!(env_el->key))
	{
		free(env_el);
		ft_set_exit_code_and_display_er(1);
		return (NULL);
	}
	env_el->key = ft_memcpy(env_el->key, env, key_len);
	env_el->key[key_len] = 0;
	env_el->key_len = key_len;
	if (!ft_is_val_present(env, key_len))
		return (env_el);
	if (!ft_check_env_lst_el(env, key_len, env_el))
		return (NULL);
	return (env_el);
}

int	ft_insert_env_lst_el(t_env *env_s, t_env_list *env_lst, char *env, size_t
key_len)
{
	t_env_list	*env_el;
	t_env_list	*tmp;

	env_el = ft_create_env_lst_el(env, key_len);
	if (!env_el)
		return (1);
	if (env_lst)
	{
		tmp = env_lst->next;
		env_lst->next = env_el;
	}
	else
	{
		tmp = env_s->env_lst;
		env_s->env_lst = env_el;
	}
	env_el->next = tmp;
	return (0);
}

int	ft_replace_env_ar_el(char **env_ar, char *env, size_t key_len)
{
	char	*env_cpy;

	env_cpy = ft_strdup(env);
	if (!env_cpy)
		return (1);
	while (*env_ar && ft_strncmp(*env_ar, env, key_len))
		env_ar++;
	free(*env_ar);
	*env_ar = env_cpy;
	return (0);
}

t_env	*ft_init_env(char **env)
{
	t_env	*env_s;

	env_s = malloc(sizeof(t_env));
	if (!env_s)
	{
		g_exit_code = 1;
		perror("minishell: ");
		return (NULL);
	}
	ft_bzero((void *)env_s, sizeof(t_env));
	while (*env)
	{
		if (ft_insert_env(env_s, *env))
		{
			ft_free_env(env_s);
			return (NULL);
		}
		env++;
	}
	return (env_s);
}
