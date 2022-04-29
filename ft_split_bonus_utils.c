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

void	ft_fill_str_with_char_and_move_to_nextch(char **strs, char **s)
{
	**strs = **s;
	*s = *s + 1;
	*strs = *strs + 1;
}

void	ft_quotesfill(char *s, char **strs1, int len)
{
	char	*strs;
	char	c;

	strs = *strs1;
	while (*s && len--)
	{
		if (*s && (*s == 39 || *s == 34))
		{
			c = *s;
			len++;
			s++;
			while (*s && *s != c && len--)
			{
				ft_fill_str_with_char_and_move_to_nextch(&strs, &s);
			}
			if (*s == 39 || *s == 34)
				s++;
		}
		else
		{
			ft_fill_str_with_char_and_move_to_nextch(&strs, &s);
		}
	}
}

int	ft_token_qoutes_fill(
		char **strs, char const **s_tosplit, char const	*s, int l)
{
	if (*s_tosplit > s - l)
	{
		ft_tokenfill((char *)*s_tosplit, strs);
	}
	else if (*s_tosplit != s - l)
	{
		ft_quotesfill((char *)*s_tosplit, strs, l);
	}
	*s_tosplit = s;
	return (1);
}

int	ft_tokenfill(char *s, char **strs)
{
	if (ft_is_specn(s) == 0)
		*strs = ft_memcpy(*strs, "REDIN", 5);
	else if (ft_is_specn(s) == 3)
		*strs = ft_memcpy(*strs, "DREDIN", 6);
	if (ft_is_specn(s) == 1)
		*strs = ft_memcpy(*strs, "REOUT", 5);
	else if (ft_is_specn(s) == 4)
		*strs = ft_memcpy(*strs, "DREOUT", 6);
	else if (ft_issep_cmdn(s))
		*strs = ft_memcpy(*strs, "PIPEX", 5);
	if (*strs == NULL)
		return (1);
	return (0);
}

void	ft_count_chars_within_qoutes(int *lw, char const **s, int *lwq)
{
	*lw = ft_quotes(s, lw);
	if (!(*lw))
		*lwq = 1;
	else
		*lwq = 0;
}
