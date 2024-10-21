/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sila <sila@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:46:58 by ssoukoun          #+#    #+#             */
/*   Updated: 2024/10/20 19:26:21 by sila             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PIPEX_H
# define PIPEX_H

#include "./lib/libft.h"
#include "STRUCT.h"


t_cmd	*init_cmd(char *argv, char **env, int error);
int	init_file(char *argv, int error, int fd);
t_pipex	*init_pipex(char **argv, char **env);

char	*final_cmd(char *argv, char **env, int error);
char	**findpath(char **env);
void	free_tab(char **tablo);
void ex_cmd_2(t_pipex *px);
void ex_cmd_1(t_pipex *px);
void ex(t_pipex *px);

int error_case(int error);

#endif