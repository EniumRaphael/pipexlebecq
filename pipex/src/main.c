/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlebecq <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:54:45 by xlebecq           #+#    #+#             */
/*   Updated: 2024/06/27 01:51:44 by xlebecq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error_msg(char *msg, int *fd)
{
	if (fd != NULL)
	{
		if (fd[0] != -1)
			close (fd[0]);
		if (fd[1] != -1)
			close (fd[1]);
	}
	ft_printf ("%s\n", msg);
	exit(EXIT_FAILURE);
}

void	ft_perror_msg(char *msg)
{
//	if (fd != NULL)
//	{
//		if (fd[0] != -1)
//			close(fd[0]);
//		if (fd[1] != -1)
//			close(fd[1]);
//	}
	perror(msg);
	exit(EXIT_FAILURE);
}

char	*find_path(char *cmd, char **envp)
{
	char	*path;
	int		i;
	char	**dir_path;
	char	*join_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	dir_path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (dir_path[i])
	{
		join_path = ft_strjoin(dir_path[i], "/");
		path = ft_strjoin(join_path, cmd);
		free(join_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = 0;
	while (dir_path[i])
	{
		free(dir_path[i]);
		i++;
	}
	free(dir_path);
	return (NULL);
}
void	ft_pipe(char *arg, char **envp)
{
	char	**cmd;
	char	*path;
	int		i;

	i = -1;
	cmd = ft_split(arg, ' ');
	if (!cmd)
		ft_perror_msg("Error");
	path = find_path(cmd[0], envp);
	if (!path)
	{	
		while (cmd[i++])
			free(cmd[i]);
		free(cmd);
		ft_perror_msg("Error");
	}
	if (execve(path, cmd, envp) == -1)
	{
		ft_perror_msg("Error: execve failed");
	}
}

void	ft_process_child(char **argv, int *fd, char **envp)
{
	int	input_file;

	input_file = open (argv[1], O_RDONLY);
	if (input_file == -1)
	{
		ft_perror_msg("Error opening input_file");
	}
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		ft_perror_msg("Error redirecting stdout");
	if (dup2(input_file, STDIN_FILENO) == -1)
		ft_perror_msg("Error redirecting stdin");
	close(fd[0]);
	close(fd[1]);
	close(input_file);
	ft_pipe(argv[2], envp);
	exit (EXIT_SUCCESS);
}

void	ft_process_parent(char **argv, int *fd, char **envp)
{
	int	output_file;

	output_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output_file == -1)
		ft_perror_msg("Error opening output_file");
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_perror_msg("Error redirecting stdin");
	if (dup2(output_file, STDOUT_FILENO) == -1)
		ft_perror_msg("Error redirecting stdout");	
	close(fd[0]);
	close(fd[1]);
	close(output_file);
	ft_pipe(argv[3], envp);
}
int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	pid_t	pid;

	fd[0] = -1;
	fd[1] = -1;

	if (argc != 5)
		ft_perror_msg("Error: invalid number of arguments.");
    if (pipe(fd) == -1)
	{
        ft_perror_msg("Error creating pipe");
	}
	pid = fork();
	if (pid == -1)
		ft_perror_msg("Error forking");
	if (pid == 0)
		ft_process_child(argv, fd, envp);
	waitpid(pid, NULL, 0);
	ft_process_parent(argv, fd, envp);
	return(EXIT_SUCCESS);
}
