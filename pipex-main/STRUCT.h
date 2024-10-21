/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   STRUCT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sila <sila@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:16:46 by ssoukoun          #+#    #+#             */
/*   Updated: 2024/10/20 18:54:54 by sila             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H

#include <unistd.h>
#include <fcntl.h>
#include <wait.h>

typedef struct s_cmd
{
	char *argv;
	char **cmd;
	char *path;
	int pid;
} t_cmd;

typedef struct s_pipex
{
	t_cmd *cmd1;
	t_cmd *cmd2;
	int f1;
	int f2;
	char **env;
	int error;
	int *status;
	int pipfd[2];
} t_pipex;

#endif