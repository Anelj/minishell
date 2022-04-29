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

int	ft_getbuffer(int out, char **buffer)
{
	*buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!(*buffer))
	{
		g_exit_code = 1;
		perror("minishell: ");
		return (ft_return_after_processing_heredoc(0, *buffer, out));
	}
	(*buffer)[BUFFER_SIZE] = '\0';
	return (0);
}

int	ft_fullbuffer(size_t nbytes, int out, char *buffer, char *limiter)
{
	if (nbytes == 0)
	{
		write(out, buffer, BUFFER_SIZE);
		return (ft_proccess_heredoc(out, limiter));
	}
	return (0);
}
