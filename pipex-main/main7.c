/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:37:52 by ssoukoun          #+#    #+#             */
/*   Updated: 2024/10/21 16:55:35 by ssoukoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"STRUCT.h"
#include "./lib/libft.h"
#include <fcntl.h>
#include <sys/wait.h>

char *find_path(char **envp)
{
    int i;

    i = 0;
    while(envp[i] != NULL && ft_strncmp(envp[i], "PATH", 5) != 0)
        i++;
    if (ft_strncmp(envp[i], "PATH", 5) == 0)
        return(envp[i] + 5);
    return(NULL);
}
char *find_cmd(char *argv, char **envp)
{
    char **chemins;
    char **argss;
    char *cmd;
    char *tmp;
    int i;

    i = -1;
    chemins = ft_split(find_path(envp), ':');
    argss = (ft_split(argv, ' '));
    while (chemins[i] && access(cmd, X_OK) == -1)
    {
        free(cmd);
        cmd = NULL;
        tmp = ft_strjoin(chemins[i], "/");
        cmd = ft_strjoin(tmp, argss[0]);
        free(tmp);
        tmp = NULL;
    }
    if (access(cmd, X_OK) == 0)
        execve(cmd, argss, envp);
    free(cmd);
    cmd = NULL;
    return(NULL);
}

char *ex(char *argv, char **envp)
{
    char **argss;

    argss = ft_split(argv, ' ');
    if (envp == NULL)
    {
        if (argv[0] == '/' && access(argv, X_OK) == 0)
            execve(argv, argss, envp);
        return(free(argss), argss = NULL, NULL);  
    }
    return(find_cmd(argv, envp));
}
void parent(char *argv, char **envp, int *pipe_fd)
{
    int fd;
    
    fd = open(argv, O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd < 0)
    {
        printf("probleme avec les fichiers\n");
        exit(0);
    }
    dup2(pipe_fd[0], STDIN_FILENO);
    dup2(fd, STDOUT_FILENO);
    close(pipe_fd[1]);
    ex(argv, envp);
}
void enfant(char *argv, char **envp, int *pipe_fd)
{
    int fd;
    
    fd = open(argv, O_RDONLY, 644);
    if (fd < 0)
    {
        printf("probleme avec les fichiers\n");
        exit(0);
    }
    dup2(fd, STDIN_FILENO);
    dup2(pipe_fd[1], STDOUT_FILENO);
    close(pipe_fd[0]);
    ex(argv, envp);
}
void pipex(char** argv, char **envp)
{
    int pipe_fd[2];
    int id;
    int id2;
    int status;
    
    status = 0;
    pipe(pipe_fd);
    id = fork();
    if (id == 0)
        enfant(argv[2], envp, pipe_fd);
    id2 = fork();
    if (id2 == 0)
        parent(argv[3], envp, pipe_fd);
    
}
int main(int argc, char **argv, char** envp)
{
    if (argc != 5)
    {
        printf("incorrect numbers of arguments\n");
        return(0);        
    }
    pipex(argv, envp);
}
