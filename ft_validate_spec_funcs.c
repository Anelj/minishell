/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:31:14 by                   #+#    #+#             */
/*   Updated: 2022/03/26 14:03:50 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_newline_token(char *spliteds, char *spliteds2)
{
	if ((!ft_strcmp(spliteds, "PIPEX") || \
		!ft_strcmp(spliteds, "REDIN") ||!ft_strcmp(spliteds, "DREDIN") \
		|| !ft_strcmp(spliteds, "REOUT") || \
		!ft_strcmp(spliteds, "DREOUT")) && spliteds2 == NULL)
	{
		g_exit_code = 2;
		write(2, \
			"minishell: syntax error near unexpected token 'newline'\n", 57);
		return (1);
	}
	return (0);
}

int	ft_check_bracket1_token(char *spliteds, char *spliteds2)
{
	if ((!ft_strcmp(spliteds, "REDIN") || !ft_strcmp(spliteds, \
			"DREDIN") || !ft_strcmp(spliteds, "REOUT") || \
			!ft_strcmp(spliteds, "DREOUT")) && spliteds2 != NULL \
			&& !ft_strcmp(spliteds2, "REDIN"))
	{
		g_exit_code = 2;
		write(2, "minishell: syntax error near unexpected token `<'\n", 50);
		return (1);
	}
	return (0);
}

int	ft_check_bracket2_token(char *spliteds, char *spliteds2)
{
	if ((!ft_strcmp(spliteds, "REDIN") || !ft_strcmp(spliteds, \
			"DREDIN") || !ft_strcmp(spliteds, "REOUT") || \
			!ft_strcmp (spliteds, "DREOUT")) && spliteds2 != NULL \
			&& !ft_strcmp(spliteds2, "DREDIN"))
	{
		g_exit_code = 2;
		write(2, "minishell: syntax error near unexpected token `<<'\n", 51);
		return (1);
	}
	return (0);
}

int	ft_check_bracket3_token(char *spliteds, char *spliteds2)
{
	if ((!ft_strcmp(spliteds, "REDIN") || !ft_strcmp(spliteds, \
			"DREDIN") || !ft_strcmp(spliteds, "REOUT") || \
			!ft_strcmp (spliteds, "DREOUT")) && spliteds2 != NULL \
			&& !ft_strcmp(spliteds2, "REOUT"))
	{
		g_exit_code = 2;
		write(2, "minishell: syntax error near unexpected token `>'\n", 50);
		return (1);
	}
	return (0);
}

int	ft_check_bracket4_token(char *spliteds, char *spliteds2)
{
	if ((!ft_strcmp(spliteds, "REDIN") || !ft_strcmp(spliteds, \
			"DREDIN") || !ft_strcmp(spliteds, "REOUT") || \
			!ft_strcmp(spliteds, "DREOUT")) && spliteds2 != NULL \
			&& !ft_strcmp(spliteds2, "DREOUT"))
	{
		g_exit_code = 2;
		write(2, "minishell: syntax error near unexpected token `>>'\n", 51);
		return (1);
	}
	return (0);
}
