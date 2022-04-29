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

int	ft_return_after_processing_heredoc(int flag, char *buffer, int out)
{
	close(out);
	free(buffer);
	if (!flag)
	{
		return (1);
	}
	return (0);
}

int	ft_getcbytes(char *buf, size_t nbytes, char *buffer, int out)
{
	int	cbytes;

	write(1, "> ", 2);
	cbytes = read(0, buf, nbytes);
	if (cbytes < 0)
	{
		g_exit_code = 1;
		perror("minishell: ");
		ft_return_after_processing_heredoc(0, buffer, out);
		return (cbytes);
	}
	buf[cbytes] = '\0';
	return (cbytes);
}

static int	ft_write_and_ret(char *buffer, char *buf, int out)
{
	write(out, buffer, buf - buffer);
	return (ft_return_after_processing_heredoc(1, buffer, out));
}

int	ft_proccess_heredoc(int out, char *limiter)
{
	int		cbytes;
	char	*buffer;
	char	*buf;
	size_t	nbytes;
	int		lim_size;

	if (ft_getbuffer(out, &buffer))
		return (1);
	buf = buffer;
	nbytes = BUFFER_SIZE;
	lim_size = ft_strlen(limiter);
	while (1)
	{
		cbytes = ft_getcbytes(buf, nbytes, buffer, out);
		if (!cbytes || (cbytes - 1 == lim_size
				&& !ft_strncmp(limiter, buf, cbytes - 1)))
			return (ft_write_and_ret(buffer, buf, out));
		if (cbytes < 0)
			return (1);
		nbytes = nbytes - cbytes;
		if (ft_fullbuffer(nbytes, out, buffer, limiter))
			return (1);
		buf = buf + cbytes;
	}
}
