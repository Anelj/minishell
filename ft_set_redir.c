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

t_simple_command	*ft_set_redir_heredoc(
		t_simple_command *scmd, int *j, char **s)
{
	char	*j_str;
	int		hout;

	j_str = ft_itoa(*j);
	if (j_str)
		(scmd->redir)[*j].redir = ft_strjoin("/tmp/mgoliath_here_doc", j_str);
	if (!j_str || !((scmd->redir)[*j].redir))
	{
		free(j_str);
		ft_set_exit_code_and_display_er(1);
		ft_freescmd(scmd);
		return (NULL);
	}
	free(j_str);
	(scmd->redir)[*j].isin = 1;
	(scmd->redir)[*j].isdouble = 1;
	unlink((scmd->redir)[*j].redir);
	hout = ft_open((scmd->redir)[(*j)++].redir, 1, 1, -1);
	if (hout < 0 || ft_proccess_heredoc(hout, *(++s)))
	{
		ft_freescmd(scmd);
		return (NULL);
	}
	return (scmd);
}

t_simple_command	*ft_set_redir(t_simple_command *scmd, int *j, char **s)
{
	if (ft_is_spec(*s) == 0 || ft_is_spec(*s) == 1 || ft_is_spec(*s) == 4)
	{
		(scmd->redir)[*j].redir = ft_strdup(*(++s));
		if (!((scmd->redir)[*j].redir))
		{
			ft_set_exit_code_and_display_er(1);
			ft_freescmd(scmd);
			return (NULL);
		}
		if (ft_is_spec(*(s - 1)) == 0)
			(scmd->redir)[*j].isin = 1;
		else
			(scmd->redir)[*j].isin = 0;
		if (ft_is_spec(*(s - 1)) == 4)
			(scmd->redir)[(*j)++].isdouble = 1;
		else
			(scmd->redir)[(*j)++].isdouble = 0;
	}
	else if (ft_is_spec(*s) == 3)
	{
		if (!ft_set_redir_heredoc(scmd, j, s))
			return (NULL);
	}
	return (scmd);
}
