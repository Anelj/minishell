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

static void	norm_operations(int *l, int *lw, int *lwq)
{
	*l += 1;
	*lw = 0;
	*lwq = 0;
}

static int	ft_countstrs(char const *s, char c, int lw, int lwq)
{
	int	l;

	if (!*s)
		return (0);
	l = 0;
	while (*s)
	{
		if (*s == 39 || *s == 34)
			ft_count_chars_within_qoutes(&lw, &s, &lwq);
		else if ((ft_is_specn((char *) s) >= 0 || ft_issep_cmdn((char *) s)))
			ft_countstrs_after_spec_met(&lw, &lwq, &l, &s);
		else if (*s == c && (lw != 0 || lwq))
		{
			norm_operations(&l, &lw, &lwq);
		}
		else if (*s != c)
			lw++;
		if (lw < 0)
			return (lw);
	s++;
	}
	if (lw != 0 || lwq)
		l++;
	return (l);
}

static int	ft_fill(char **strs, char const **s_tosplit)
{
	int			l;
	int			i;
	char const	*s;

	s = *s_tosplit;
	l = ft_str_len_in_s_tosplit(&s, ' ');
	*strs = (char *)malloc(sizeof(char) * (l + 1));
	if (*strs == NULL)
	{
		ft_set_exit_code_and_display_er(1);
		return (-1);
	}
	(*strs)[l] = '\0';
	i = 0;
	if (*s_tosplit > s - l || *s_tosplit != s - l)
		return (ft_token_qoutes_fill(strs, s_tosplit, s, l));
	*s_tosplit = s;
	s = s - l;
	while (l--)
	{
		(*strs)[i] = *s;
		i++;
		s++;
	}
	return (1);
}

static char	**ft_fillstrs(char **ss, char const *s, int l)
{
	int		i;
	char	**strs;

	strs = ss;
	while (l-- && *s)
	{
		while (*s == ' ')
			s++;
		i = ft_fill(strs, &(s));
		if (i == 1)
			strs++;
		else if (i == -1)
			return (ft_split_freestrs(strs, ss));
	}
	return (ss);
}

char	**ft_advance_split(char const *s, char c)
{
	int		l;
	char	**strs;
	int		lw;
	int		lwq;

	lw = 0;
	lwq = 0;
	l = ft_countstrs(s, c, lw, lwq);
	if (l < 0)
		return (NULL);
	strs = (char **)malloc(8 * (l + 1));
	if (strs == NULL)
	{
		g_exit_code = 1;
		perror("minishell: ");
		return (NULL);
	}
	strs[l] = NULL;
	return (ft_fillstrs(strs, s, l));
}
