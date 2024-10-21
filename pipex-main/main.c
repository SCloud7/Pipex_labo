/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:43:11 by ssoukoun          #+#    #+#             */
/*   Updated: 2024/10/21 19:56:04 by ssoukoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

int main(int argc, char **argv, char **envp)
{
    t_pipex *pipex;
    
    if(argc != 5 || !argv[0] || !argv[1] || !argv[2] || !argv[3])
        return(printf("pas le bon nombre d'arguments"), 0);
    pipex = init_pipex(argv, envp);
    if(pipex == NULL || pipex->error != 0)
        error_case(&pipex);
    // ex(pipex);
    return(free_pipex(&pipex), 0);
}
