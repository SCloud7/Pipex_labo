/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sila <sila@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:22:56 by ssoukoun          #+#    #+#             */
/*   Updated: 2024/10/20 21:59:06 by sila             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lib/libft.h"
#include "STRUCT.h"
#include "pipex.h"


void	free_tab(char **tablo)
{
	int	i;

	i = 0;
	while (tablo[i])
		free(tablo[i]);
	free(tablo);
	tablo = NULL;
}

char	**findpath(char **env)
{
	int		i;
	char	**paths;
	char	*line;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) != 0)
		{
			line = ft_substr(env[i], 5, ft_strlen(env[i]));
			paths = ft_split(env[i], ':');
			free(line);
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*final_cmd(char *argv, char **env, int error)
{
	char	**argss;
	char	*cmd;
	char	**paths;
	int		i;

	if(error)
		return(error_case(error), NULL);
	i = 0;
	paths = findpath(env);
	argss = ft_split(argv, ' ');
	while (paths && paths[i])
	{
		cmd = ft_strjoin(paths[i], "/");
		cmd = ft_strjoin(cmd, argss[0]);
		if (access(cmd, X_OK))
			return (cmd);
		i++;
	}
	return (free_tab(paths), free_tab(argss), error = 5, NULL);
}

t_cmd	*init_cmd(char *argv, char **env, int error)
{
	t_cmd	*c1;

	c1 = calloc(1, sizeof(t_cmd));
	if (c1 == NULL)
		return (error = 1, NULL);
	if (env == NULL)
	{
		if (ft_strncmp(argv, "/", 1))
		{
			c1->cmd = ft_split(argv, ' ');
			c1->path = c1->cmd[0];
			if (access(c1->argv, X_OK) == -1)
				return (error = 4, NULL);
			else
				return (c1);
		}
		return (error = 2, NULL);
	}
	c1->argv = argv;
	c1->cmd = ft_split(argv, ' ');
	c1->path = final_cmd(argv, env, error);
	return (c1);
}

int	init_file(char *argv, int error, int fd)
{
	int f1;

	if(error != 0)
		return(error_case(error));
	if (fd == 1)
	{
		f1 = open(argv, O_WRONLY);
		if (access(argv, F_OK | R_OK) == -1)
			return(error_case(3));
	}
	if (fd == 2)
	{
		f1 = open(argv, O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (access(argv, F_OK | R_OK | W_OK) == -1)
			return(error_case(9));
	}
	if (f1 == -1)
		return(error_case(5));
	return(f1);
}

t_pipex	*init_pipex(char **argv, char **env)
{
	t_pipex *pipex;

	pipex = calloc(1, sizeof(t_pipex));
	if (pipex == NULL)
		return (NULL);
	if (pipe(pipex->pipfd) == -1)
		return (pipex->error = 10, NULL);
	pipex->error = 0;
	pipex->f1 = init_file(argv[1], pipex->error, 1);
	//if (pipex->error)
        //return (pipex);
	pipex->cmd1 = init_cmd(argv[2], env, pipex->error);
	pipex->cmd2 = init_cmd(argv[3], env, pipex->error);
	pipex->f2 = init_file(argv[4], pipex->error, 2);

	return (pipex);
}