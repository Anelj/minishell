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

int	ft_emptyvar_insert(char **string, char **s, char **ret)
{
	char	*tmp;

	if (*ret == *s)
		return (0);
	**ret = 0;
	tmp = *string;
	*string = ft_strjoin(tmp, *s);
	if (!(*string))
	{
		free(tmp);
		return (ft_set_exit_code_and_display_er(1));
	}
	*s = *string + ft_strlen(tmp) - 1;
	free(tmp);
	return (0);
}

int	ft_join_with_remain_str(char *tmp, char **s, char **string)
{
	char	*tmp1;
	size_t	l;

	tmp1 = ft_strjoin(tmp, *s);
	l = ft_strlen(tmp);
	free(*string);
	free(tmp);
	if (!tmp1)
	{
		g_exit_code = 1;
		perror("minishell: ");
		return (1);
	}
	*string = tmp1;
	*s = tmp1 + l - 1;
	return (0);
}

int	ft_insert_var_witin_quotes(char **s, char **string, t_env *env_s)
{
	char	*var;
	char	*tmp;
	char	*ret;

	ret = *s;
	var = NULL;
	if (ft_find_envvar(s, env_s, &var))
	{
		free(*string);
		return (1);
	}
	if (!var || !(*var))
		return (ft_emptyvar_insert(string, s, &ret));
	*ret = 0;
	tmp = ft_strjoin(*string, var);
	free(var);
	if (!tmp)
	{
		g_exit_code = 1;
		perror("minishell: ");
		free(*string);
		return (1);
	}
	return (ft_join_with_remain_str(tmp, s, string));
}

int	ft_var_within_quotes(char **str, char **string, t_env *env_s)
{
	char	*s;
	char	c;

	s = *str;
	c = ' ';
	if (*s && (*s == 39 || *s == 34))
	{
		c = *s;
		s++;
	}
	while (*s && *s != c)
	{
		if (*s == '$' && (ft_isalnum(*(s + 1)) || \
		*(s + 1) == '_' || *(s + 1) == '?') && c == 34)
		{
			if (ft_insert_var_witin_quotes(&s, string, env_s))
				return (1);
		}
		s++;
	}
	*str = s;
	return (0);
}
