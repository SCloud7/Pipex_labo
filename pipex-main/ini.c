/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:22:56 by ssoukoun          #+#    #+#             */
/*   Updated: 2024/10/21 19:10:27 by ssoukoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lib/libft.h"
#include "STRUCT.h"
# include "pipex.h"

void	free_tab(char **tablo)
{
	int	i;

	i = 0;
	while (tablo[i])
		free(tablo[i]);
	free(tablo);
	tablo = NULL;
}
int ft_strnstri(const char *haystack, const char *needle, size_t len)
{
	size_t  i;
	size_t  a;

	i = 0;
	if (!*needle)
		return (-1);
	while (haystack[i] && i < len)
	{
		a = 0;
		while (haystack[i + a] && needle[a] && haystack[i + a] && len > i + a
			&& haystack[i + a] == needle[a])
			a++;
		if (!needle[a])
			return (1);
		i++;
	}
	return (-1);
}

char	**findpath(char **env)
{
	int		i;
	char	**paths;
	char	*line;

	i = 0;
	while (env[i])
	{
		if (ft_strnstri(env[i], "PATH", 4) == 1)
		{
			line = ft_substr(env[i], 5, ft_strlen(env[i]));
			paths = ft_split(line, ':');
			free(line);
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*final_cmd(char *argv, char **env, int *error)
{
	char	**argss;
	char	*cmd;
	char	**paths;
	int		i;
	char 	*tmp;

	if(error != 0)
		return(NULL);
	i = 0;
	paths = findpath(env);
	argss = ft_split(argv, ' ');
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		cmd = ft_strjoin(tmp, argss[0]);
		free(tmp);
		//printf("%s \n", cmd);
		if (access(cmd, F_OK) && access(cmd, X_OK))
		{
			printf("ICI == %s \n", cmd);
			return (cmd);
		}
		i++;
	}
	
	return (free_tab(paths), free_tab(argss), *error = 5, NULL);
}

t_cmd	*init_cmd(char *argv, char **env, int *error)
{
	t_cmd	*c1;

	c1 = calloc(1, sizeof(t_cmd));
	if (c1 == NULL)
		return (*error = 1, NULL);
	if (env == NULL)
	{
		if (ft_strncmp(argv, "/", 1))
		{
			c1->cmd = ft_split(argv, ' ');
			c1->path = c1->cmd[0];
			if (access(argv, X_OK) == -1)
				return (*error = 4, NULL);
			else
				return (c1);
		}
		return (*error = 2, NULL);
	}
	c1->cmd = ft_split(argv, ' ');
	c1->path = final_cmd(argv, env, error);
	return (c1);
}

char	*init_file(char *argv, int f1ouf2 , int *error)
{
	// si f1 alors verifier lexistance et lecriture
	// si f2 alors verifier si on peut le cree ou quil existe et quon peut ecrire
}

t_pipex	*init_pipex(char **argv, char **env)
{
	(void) argv;
	(void) env;
	t_pipex *pipex;

	pipex = calloc(1, sizeof(t_pipex));
	if (pipex == NULL)
		return (NULL);
	if (pipe(pipex->pipfd) == -1)
		return (pipex->error = 10, NULL);
	pipex->error = 0;
	// a refaire meiux anticiper comment gerer ces ca derreur et sa structure en cas dechec sans 
	// pipex->f1 = init_file(argv[1], pipex->error, 1);
	// pipex->f2 = init_file(argv[4], pipex->error, 2);
	// pipex->cmd1 = init_cmd(argv[2], env, pipex->error);
	// pipex->cmd2 = init_cmd(argv[3], env, pipex->error);
	if (pipex->error)
        return (pipex);
	return (pipex);
}

void	free_pipex(t_pipex	**pipex_var)
{
	if (pipex_var == NULL || *pipex_var == NULL)
		return ;
	if ((*pipex_var)->cmd1)
		free((*pipex_var)->cmd1);
	(*pipex_var)->cmd1 = NULL;
	if ((*pipex_var)->cmd1)
		free((*pipex_var)->cmd2);
	(*pipex_var)->cmd2 = NULL;
	close((*pipex_var)->pipfd[0]);
	close((*pipex_var)->pipfd[1]);
	free(*pipex_var);
	pipex_var = NULL;
	return ;
}