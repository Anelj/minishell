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

int	ft_str_len_after_spec_met(
		int lw, int lwq, char const **s_tosplit, char const *s)
{
	if (lw != 0 || lwq)
	{
		*s_tosplit = s;
		return (lw);
	}
	if (ft_is_specn((char *) s) == 3 || ft_is_specn((char *) s) == 4)
	{
		*s_tosplit = s + 2;
		return (6);
	}
	*s_tosplit = s + 1;
	return (5);
}

int	ft_str_len_after_ws_met(char const **s_tosplit, char const *s, int lw)
{
	*s_tosplit = s;
	return (lw);
}

int	ft_str_len_in_s_tosplit(char const **s_tosplit, char c)
{
	int			lw;
	int			lwq;
	char const	*s;

	s = *s_tosplit;
	if (!*s)
		return (0);
	lw = 0;
	lwq = 0;
	while (*s)
	{
		if (*s == 39 || *s == 34)
			ft_count_chars_within_qoutes(&lw, &s, &lwq);
		else if ((ft_is_specn((char *) s) >= 0 || ft_issep_cmdn((char *) s)))
			return (ft_str_len_after_spec_met(lw, lwq, s_tosplit, s));
		else if (*s == c && (lw != 0 || lwq))
			return (ft_str_len_after_ws_met(s_tosplit, s, lw));
		else if (*s != c)
			lw++;
		s++;
	}
	if (lw != 0 || lwq)
		*s_tosplit = s;
	return (lw);
}

void	ft_countstrs_after_spec_met(int *lw, int *lwq, int *l, char const **str)
{
	char const	*s;

	s = *str;
	if (*lw != 0 || *lwq)
	{
		*l = *l + 1;
		*lwq = 0;
	}
	if (ft_is_specn((char *) s) == 3 || ft_is_specn((char *) s) == 4)
		s++;
	*str = s;
	*l = *l + 1;
	*lw = 0;
}
