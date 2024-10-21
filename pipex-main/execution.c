/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 13:35:26 by ssoukoun          #+#    #+#             */
/*   Updated: 2024/10/21 18:29:00 by ssoukoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void error_case(t_pipex **pipex_var)
{
    int error;
    error = -1;
    
    if (!pipex_var || !(*pipex_var))
    {
        printf("Generation de ma structure a echouer");
        exit(1);
    }
    error = (*pipex_var)->error;
    if(error == 1)
        printf("echec du 1er fichier");
    else if(error == 10)
        printf("echec du pipe");
    else if(error == 2)
        printf("environement vide et pas de chemin absolu");
    else if(error == 5)
        printf("echec de l'ouverture du fichier");
    else if(error == 3)
        printf("soit fichier innexistant ou illisible");
    else if(error == 4)
        printf("soit fichier innexistant ou illisible ou peut pas ecrire");
    else if(error == 9)
        printf("le deuxieme fd a pas les droits");
    free(pipex_var);
    exit(0);
}

void ex_cmd_1(t_pipex *px)
{
    px->cmd1->pid = fork();
    if(px->cmd1->pid == -1)
        return(px->error = 8, error_case(&px), perror("fork2"));
    dup2(px->f1, STDIN_FILENO);
    dup2(px->pipfd[0], STDOUT_FILENO);
    //close(px->f1);
    close(px->pipfd[1]);
    close(px->pipfd[0]);
    //close(px->f1);
    execve(px->cmd1->path, px->cmd1->cmd, px->env);
}
void ex_cmd_2(t_pipex *px)
{
    px->cmd2->pid = fork();
    if(px->cmd2->pid == -1)
        return(px->error = 8, error_case(&px), perror("fork2"));
    dup2(px->pipfd[1], STDIN_FILENO);
    dup2(px->f2, STDOUT_FILENO);
    //close(px->f2);
    close(px->pipfd[0]);
    close(px->pipfd[1]);
    //close(px->f1);
    //printf("c %i", px->cmd2->pid);
    execve(px->cmd2->path, px->cmd2->cmd, px->env);
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
