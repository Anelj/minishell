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

int	ft_insert_splitedvar_withquotes(char **spl_var, size_t *l, char **tmp)
{
	char	*q;
	int		i;

	i = 0;
	while (spl_var[i])
	{
		*l = *l + ft_strlen(spl_var[i]) + 2;
		q = "\"";
		if (i != 0)
		{
			q = " \"";
			*l = *l + 1;
		}
		if (ft_strjoin_inserting_var(tmp, q, spl_var, i)
			|| ft_strjoin_inserting_var(tmp, spl_var[i], spl_var, i))
			return (1);
		q = "\"";
		if (ft_strjoin_inserting_var(tmp, q, spl_var, i))
			return (1);
		free(spl_var[i++]);
	}
	free(spl_var);
	return (0);
}

int	ft_process_found_var_char(char **s, char **string, t_env *env_s)
{
	char	*var;
	char	**spl_var;
	char	*tmp;
	size_t	l;
	char	*s1;

	s1 = *s;
	var = NULL;
	if (ft_find_envvar(s, env_s, &var))
		return (ft_freestr_reter(*string));
	if (!var || !(*var))
		return (ft_emptyvar_insert(string, s, &s1));
	if (ft_split_var(&spl_var, var, *string))
		return (1);
	*s1 = 0;
	if (ft_get_len_and_strdup_str_before_var_char(&l, string, &tmp, spl_var))
		return (1);
	if (ft_insert_splitedvar_withquotes(spl_var, &l, &tmp)
		|| ft_strjoin_inserting_var(&tmp, *s, NULL, 0))
		return (ft_freestr_reter(*string));
	free(*string);
	*string = tmp;
	*s = tmp + l - 1;
	return (0);
}

int	ft_insert_var(char **string, t_env *env_s)
{
	char	*s;

	if (!*string)
		return (0);
	s = *string;
	while (*s)
	{
		if (*s == 39 || *s == 34)
		{
			if (ft_var_within_quotes(&s, string, env_s))
				return (1);
		}
		else if (*s == '$' && (ft_isalnum(*(s + 1)) || *(s + 1) == '_' \
		|| *(s + 1) == '?'))
		{
			if (ft_process_found_var_char(&s, string, env_s))
				return (1);
		}
		s++;
	}
	return (0);
}

int	ft_freestr_reter(char *string)
{
	free(string);
	return (1);
}
