/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlebecq <xlebecq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:10:58 by xlebecq           #+#    #+#             */
/*   Updated: 2024/08/07 14:11:32 by xlebecq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char *cmd, char **envp)
{
	char	*path;
	int		i;
	char	**dir_path;
	char	*join_path;

	i = 0;
	if (!envp || !envp[0])
		return (printf("Error: envp is NULL"), NULL);
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	dir_path = ft_split(envp[i] + 5, ':');
	i = -1;
	while (dir_path[++i])
	{
		join_path = ft_strjoin(dir_path[i], "/");
		path = ft_strjoin(join_path, cmd);
		free(join_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
	}
	free_2d_array(dir_path);
	return (NULL);
}

void	ft_pipe(char *arg, char **envp)
{
	char	**cmd;
	char	*path;
	int		i;

	cmd = ft_split(arg, ' ');
	if (!cmd)
		ft_perror_msg("Error", NULL);
	path = find_path(cmd[0], envp);
	if (!path)
	{	
		i = -1;
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		ft_perror_msg("Error", NULL);
	}
	if (execve(path, cmd, envp) == -1)
	{
		ft_perror_msg("Error: execve failed", NULL);
	}
}



void process_child(char **argv, int *fd)
{
	int input_file;

	input_file = open(argv[1], O_RDONLY);
	if(input_file == -1)
	{
		ft_perror_msg("Error opening input_file", fd);
	}
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		close (input_file);
		ft_perror_msg("Error redirecting stdout", fd);
	}
	if (dup2(input_file, STDIN_FILENO) == -1)
	{
		close (input_file);
		ft_perror_msg("Error, redirecting stdin", fd);
	}
	close (fd[0]);
	close (fd[1]);
	close (input_file);
}
int main(int argc, char **argv)
{
	int	fd[2];
	pid_t	pid;

	char *str = argv[0];

	printf("%s", str);
	
	if (argc != 5)
		ft_perror_msg("Error: invalid number of arguments.", NULL);
	
	if (pipe(fd) == -1)
	{
		ft_perror_msg("Error creating pipe", NULL);
	}
	pid = fork();
	if (pid == -1)
		ft_perror_msg("Error forking", fd);
	if (pid == 0)
		process_child(argv, fd);
	waitpid(pid, NULL, 0);
	close (fd[0]);
	close (fd[1]);
	return(EXIT_SUCCESS);
}
		
