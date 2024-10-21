/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sila <sila@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 13:35:26 by ssoukoun          #+#    #+#             */
/*   Updated: 2024/10/20 19:59:39 by sila             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lib/libft.h"
#include "STRUCT.h"
#include "pipex.h"


int error_case(int error)
{
    if(error == 1)
        printf("echec du 1er fichier");
    if(error == 10)
        printf("echec du pipe");
    if(error == 2)
        printf("environement vide et pas de chemin absolu");
    if(error == 5)
        printf("echec de l'ouverture du fichier");
    if(error == 3)
        printf("soit fichier innexistant ou illisible");
    if(error == 4)
        printf("soit fichier innexistant ou illisible ou peut pas ecrire");
    if(error == 9)
        printf("mort");
    
    return(exit(0), 0);
}

void ex_cmd_1(t_pipex *px)
{
    px->cmd1->pid = fork();
    if(px->cmd1->pid < 0)
        return(error_case(8), perror("fork2"));
    if(px->cmd1->pid == 0)
    {
    dup2(px->f1, STDIN_FILENO);
    dup2(px->pipfd[1], STDOUT_FILENO);
    close(px->f1);
    close(px->pipfd[1]);
    close(px->pipfd[0]);
    execve(px->cmd1->path, px->cmd1->cmd, px->env);
    }
}
void ex_cmd_2(t_pipex *px)
{
    px->cmd2->pid = fork();
    if(px->cmd2->pid < 0)
        return(error_case(8), perror("fork2"));
    if(px->cmd2->pid == 0)
    {
    dup2(px->f2, STDIN_FILENO);
    dup2(px->pipfd[0], STDOUT_FILENO);
    close(px->f2);
    close(px->pipfd[0]);
    close(px->pipfd[1]);
    execve(px->cmd2->path, px->cmd2->cmd, px->env);
    }
}

void ex(t_pipex *px)
{
    ex_cmd_1(px);  
    ex_cmd_2(px);
    close(px->pipfd[0]);
    close(px->pipfd[1]);
    waitpid(px->cmd1->pid, px->status, 0);
    waitpid(px->cmd2->pid, px->status, 0);
}