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

char	*ft_find_cmdpath_inpath(char *envPATH, char *cmdname)
{
	char	**paths;
	char	*cmdpath;
	int		i;

	paths = ft_splitpath(envPATH + 5, ':');
	i = 0;
	while (ft_strcmp(cmdname, "") && paths && paths[i])
	{
		cmdpath = ft_strjoin(paths[i], cmdname);
		if (cmdpath && !access(cmdpath, 1))
		{
			free(cmdname);
			ft_freestrs(paths);
			return (cmdpath);
		}
		free(cmdpath);
		i++;
	}
	write(2, "minishell: ", 11);
	write(2, cmdname, ft_strlen(cmdname));
	write(2, ": command not found\n", 20);
	g_exit_code = 127;
	ft_freestrs(paths);
	return (NULL);
}

char	*ft_is_cmd_executable(char *cmdname)
{
	if (!access(cmdname, 1))
		return (cmdname);
	write(2, "minishell: ", 11);
	write(2, cmdname, ft_strlen(cmdname));
	write(2, ": ", 2);
	perror("");
	if (!ft_strncmp(strerror(errno), "Permission denied", 17))
		g_exit_code = 126;
	else
		g_exit_code = 127;
	return (NULL);
}

char	*ft_path(char *cmdname, t_env *env_s)
{
	char	**env;

	env = env_s->env_ar;
	if (ft_is_path(cmdname))
	{
		return (ft_is_cmd_executable(cmdname));
	}
	while (*env)
	{
		if (!ft_strcmp(*env, "PATH") || !ft_strcmp(*env, "PATH="))
			return (ft_is_cmd_executable(cmdname));
		if (!ft_strncmp(*env, "PATH=", 5))
			return (ft_find_cmdpath_inpath(*env, cmdname));
		env++;
	}
	return (ft_is_cmd_executable(cmdname));
}

char	**ft_get_cmd(char **cmd, t_env *env_s)
{
	char	*execcmd;

	if (cmd && cmd[0])
		execcmd = ft_path(cmd[0], env_s);
	if (!cmd || !(cmd[0]) || !execcmd)
	{
		return (NULL);
	}
	cmd[0] = execcmd;
	return (cmd);
}
