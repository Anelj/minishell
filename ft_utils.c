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

int	ft_set_exit_code_and_display_er(int code)
{
	g_exit_code = code;
	perror("minishell: ");
	return (1);
}

int	ft_strdup_helper(char **string, char **tmp)
{
	*tmp = ft_strdup(*string);
	if (!(*tmp))
	{
		g_exit_code = 1;
		perror("minishell: ");
		return (1);
	}
	return (0);
}

int	ft_strjoin_inserting_var(char **s, char *s1, char **spl_var, int i)
{
	char	*tmp;

	tmp = *s;
	*s = ft_strjoin(tmp, s1);
	free(tmp);
	if (!(*s))
	{
		while (spl_var && spl_var[i])
			free(spl_var[i++]);
		free(spl_var);
		return (1);
	}
	return (0);
}

void	ft_dup2_close(int fd1, int fd2)
{
	dup2(fd1, fd2);
	close(fd1);
}

void	ft_exit_program(t_env *env_s)
{
	clear_history();
	ft_free_env(env_s);
	exit(g_exit_code);
}
