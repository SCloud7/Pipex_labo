/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   STRUCT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:16:46 by ssoukoun          #+#    #+#             */
/*   Updated: 2024/10/21 19:10:55 by ssoukoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "./lib/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <wait.h>

typedef struct s_cmd
{
	char	**cmd;
	char	*path;
	pid_t	pid;
}			t_cmd;

typedef struct s_pipex
{
	t_cmd	*cmd1;
	t_cmd	*cmd2;
	char		*f1;
	char		*f2;
	char	**env;
	int		error;
	int		*status;
	int		pipfd[2];
}			t_pipex;

#endif