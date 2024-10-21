/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sila <sila@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:43:11 by ssoukoun          #+#    #+#             */
/*   Updated: 2024/10/20 19:41:07 by sila             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lib/libft.h"
#include "STRUCT.h"
#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
    t_pipex *pipex;
    
    if(argc != 5 || !argv[0] || !argv[1] || !argv[2] || !argv[3])
        return(printf("pas le bon nombre d'arguments"), 0);
    pipex = init_pipex(argv, envp);
    if(pipex || pipex->error != 0)
        return(error_case(pipex->error));
    ex(pipex);
    return(free(pipex), 0);
}