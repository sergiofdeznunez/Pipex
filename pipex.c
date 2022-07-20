/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunez <snunez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:27:19 by snunez            #+#    #+#             */
/*   Updated: 2022/04/30 13:19:02 by snunez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void leaks(void)
{
	system("leaks pipex");
}

void	execute(char **cmd, char **envp)
{
	char	**routes;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (execve(cmd[0], cmd, envp) == -1)
	{
		routes = get_routes(cmd, envp);
		while (routes[j])
			j++;
		while (routes[i])
		{
			execve(routes[i], cmd, envp);
			i++;
		}
		ft_free_double_pointer((void **)routes);
		ft_free_double_pointer((void **)cmd);
		perror("Error: command not found");
		exit(EXIT_FAILURE);
	}
}

void	first_child(char **argv, int pipes[], char **envp)
{
	int		infile;
	char	**cmd1;

	cmd1 = take_cmd(argv[2]);
	catch_verror(check_cmd(cmd1));
	catch_verror(close(pipes[READ_END]));
	if (access(argv[1], R_OK) == 0)
	{
		infile = open(argv[1], O_RDONLY);
		catch_oerror(cmd1, infile);
		catch_verror(dup2(infile, STDIN_FILENO));
		catch_verror(close(infile));
		catch_verror(dup2(pipes[WRITE_END], STDOUT_FILENO));
		catch_verror(close(pipes[WRITE_END]));
		execute(cmd1, envp);
	}
	ft_free_double_pointer((void **)cmd1);
}

void	second_child(char **argv, int pipes[], char **envp)
{
	pid_t	pid;
	int		dest;
	char	**cmd2;

	cmd2 = take_cmd(argv[3]);
	printf("cmd2 = %p\n",  cmd2);
	catch_verror(check_cmd(cmd2));
	catch_verror(close(pipes[WRITE_END]));
	pid = catch_error(fork());
	if (pid == 0)
	{
		dest = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		printf("dest = %p\n", &dest);
		catch_oerror(cmd2, dest);
		catch_verror(dup2(pipes[READ_END], STDIN_FILENO));
		catch_verror(close(pipes[READ_END]));
		catch_verror(dup2(dest, STDOUT_FILENO));
		execute(cmd2, envp);
	}
	else
	{
		ft_free_double_pointer((void **)cmd2);
		catch_verror(close(pipes[READ_END]));
		//system("leaks pipex");
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		pipes[2];
	int		status;
	pid_t	pid;

	if (argc == 5)
	{
		pipe(pipes);
		//printf("pipes = %p\n", &pipes);
		pid = catch_error(fork());
		//printf("pid = %d\n", pid);
		if (!pid)
		{
			if (access(argv[1], R_OK) == 0)
				first_child(argv, pipes, envp);
		}
		else
			second_child(argv, pipes, envp);
		//ft_free_double_pointer((void **)cmd2)
		//system("leaks pipex");
		waitpid(pid, &status, 0);
		waitpid(pid, &status, 0);
		//exit(EXIT_SUCCESS);
	}
	else
		printf("usage: ./pipex <file1> \"cmd1\" \"cmd2\" <file2>\n");
	atexit(leaks);
}
