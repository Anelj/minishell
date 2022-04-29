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

int	ft_args_count(char **s)
{
	int		count;

	count = 0;
	while (*s && !ft_issep_cmd(*s))
	{
		if (ft_is_spec(*s) != -1)
		{
			s++;
		}
		else
		{
			count++;
		}
		s++;
	}
	if (!count)
		return (1);
	return (count);
}

int	ft_in_count(char **s)
{
	int	count;

	count = 0;
	while (*s && !ft_issep_cmd(*s))
	{
		if (ft_is_spec(*s) == 0 || ft_is_spec(*s) == 3)
		{
			count++;
		}
		s++;
	}
	return (count);
}

int	ft_out_count(char **s)
{
	int	count;

	count = 0;
	while (*s && !ft_issep_cmd(*s))
	{
		if (ft_is_spec(*s) == 1 || ft_is_spec(*s) == 4)
		{
			count++;
		}
		s++;
	}
	return (count);
}

int	ft_scmd_count(char **s)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (ft_issep_cmd(*s))
		{
			count++;
		}
		s++;
	}
	return (count + 1);
}

t_simple_command	*ft_get_scmd(char ***s1)
{
	char				**s;
	t_simple_command	*scmd;

	s = *s1;
	scmd = ft_create_scmd(s);
	if (!scmd)
		return (NULL);
	s = ft_fill_scmd(s, scmd);
	if (!s)
		return (NULL);
	if (!(*s))
		*s1 = s;
	else
		*s1 = s + 1;
	return (scmd);
}
