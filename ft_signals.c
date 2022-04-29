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

void	int_handler1(void)
{
	printf("\n");
}

void	int_handler(void)
{
	rl_on_new_line();
	rl_redisplay();
	write(2, "  \n", 3);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_code = 130;
}

void	ft_initial_sig_override(t_env *env_s)
{
	if (signal(SIGINT, (void (*)(int)) int_handler) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		ft_free_env(env_s);
		perror("minishell: ");
		exit(1);
	}
}

void	ft_sigint_for_parent_process(char *s, t_env *env_s)
{
	if (signal(SIGINT, (void (*)(int)) int_handler1) == SIG_ERR)
	{
		free(s);
		ft_free_env(env_s);
		perror("minishell: ");
		exit(1);
	}
}

void	ft_sig_return_def_behavior(t_command *cmd)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR || \
		signal(SIGQUIT, SIG_DFL) == SIG_ERR)
	{
		ft_free_env(cmd->env_s);
		ft_freecmd(&cmd);
		perror("minishell: ");
		exit(1);
	}
}
