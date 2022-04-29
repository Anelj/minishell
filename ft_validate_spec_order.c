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

int	ft_check_pipe_token(char *spliteds, char *spliteds2, int i)
{
	if ((i == 0 && !ft_strcmp(spliteds, "PIPEX")) || (((!ft_strcmp \
		(spliteds, "PIPEX") || !ft_strcmp(spliteds, "REDIN") || \
		!ft_strcmp(spliteds, "DREDIN") || !ft_strcmp(spliteds, "REOUT") || \
		!ft_strcmp(spliteds, "DREOUT")) \
		&& spliteds2 != NULL) && !ft_strcmp (spliteds2, "PIPEX")))
	{
		g_exit_code = 2;
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
		return (1);
	}
	return (0);
}

int	ft_validate_spec_order(char **spliteds)
{
	int		i;

	i = 0;
	while (spliteds[i])
	{
		if ((ft_check_pipe_token(spliteds[i], spliteds[i + 1], i)))
			return (1);
		if ((ft_check_newline_token(spliteds[i], spliteds[i + 1])))
			return (1);
		if ((ft_check_bracket1_token(spliteds[i], spliteds[i + 1])))
			return (1);
		if ((ft_check_bracket2_token(spliteds[i], spliteds[i + 1])))
			return (1);
		if ((ft_check_bracket3_token(spliteds[i], spliteds[i + 1])))
			return (1);
		if ((ft_check_bracket4_token(spliteds[i], spliteds[i + 1])))
			return (1);
		i++;
	}
	return (0);
}
