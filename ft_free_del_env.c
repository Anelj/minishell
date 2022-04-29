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

void	ft_free_lst(t_env_list **lst)
{
	t_env_list	*tmp;
	t_env_list	*tmp1;

	tmp = *lst;
	if (!tmp)
		return ;
	while (tmp)
	{
		tmp1 = tmp;
		free(tmp1->key);
		free(tmp1->val);
		tmp = tmp->next;
		free(tmp1);
	}
	*lst = NULL;
}

void	ft_free_ar(char ***ar)
{
	char	**tmp;

	tmp = *ar;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(*ar);
	*ar = NULL;
}

void	ft_free_env(t_env *env)
{
	ft_free_lst(&(env->env_lst));
	ft_free_ar(&(env->env_ar));
	free(env);
}

void	ft_del_env_lst_el(t_env_list *env_lst, t_env_list *env_lst_prev)
{
	env_lst_prev->next = env_lst->next;
	free(env_lst->key);
	free(env_lst->val);
	free(env_lst);
}

void	ft_del_env_ar_el(char **env_ar, char *env, size_t key_len)
{
	char	**env_ar_el;

	while (*env_ar && ft_strncmp(*env_ar, env, key_len))
		env_ar++;
	env_ar_el = env_ar;
	free(*env_ar_el);
	*env_ar_el = NULL;
	while (*(++env_ar))
	{
		*env_ar_el = *env_ar;
	}
	*(env_ar - 1) = NULL;
}
