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

int	ft_is_specn(char *s)
{
	if ((!ft_strncmp(s, "<<", 2)))
		return (3);
	else if ((!ft_strncmp(s, ">>", 2)))
		return (4);
	else if (!ft_strncmp(s, "<", 1))
		return (0);
	else if ((!ft_strncmp(s, ">", 1)))
		return (1);
	return (-1);
}

int	ft_is_spec(char *s)
{
	if ((!ft_strcmp(s, "DREDIN")))
		return (3);
	else if ((!ft_strcmp(s, "DREOUT")))
		return (4);
	else if (!ft_strcmp(s, "REDIN"))
		return (0);
	else if ((!ft_strcmp(s, "REOUT")))
		return (1);
	return (-1);
}

int	ft_issep_cmdn(char *s)
{
	if (!ft_strncmp(s, "|", 1))
		return (1);
	return (0);
}

int	ft_issep_cmd(char *s)
{
	if (!ft_strcmp(s, "PIPEX"))
		return (1);
	return (0);
}
