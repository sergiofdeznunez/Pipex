/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunez <snunez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:27:19 by snunez            #+#    #+#             */
/*   Updated: 2022/04/18 13:51:43 by snunez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child()
{}

void	second_child()
{}

char	**take_cmd(char *line)
{
	char	**cmd;

	if(!line)
		return (NULL);
	cmd = ft_split(line, ' ');
	return (cmd);
}

void	execute(char **cmd, char **envp)
{
	char **routes;
	int i;

	i = 0;
	if (execve(cmd[0], cmd, envp) == -1)
	{
		routes = get_routes(cmd, envp);
		while (routes[i])
		{
			execve(routes[i], cmd, envp);
			i++;
		}
		ft_free_double_pointer((void **)routes);
		ft_free_double_pointer((void **)cmd);
		perror("Error: command not found\n");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		pipes[2];
	int		infile, dest, status;
	pid_t	pid;
	char	**cmd1;
	char	**cmd2;

	if (argc == 5)
	{
		pipe(pipes);
		cmd1 = take_cmd(argv[2]);
		cmd2 = take_cmd(argv[4]);
		catch_verror(check_cmds(cmd1, cmd2));
		pid = catch_error(fork());
		if (pid == 0) /* hijo 1*/
		{
			if (access(argv[1], R_OK))
			{
				infile = open(argv[1], O_RDONLY);
				catch_oerror(cmd1, cmd2, infile);
				catch_verror(close(pipes[READ_END]));
				catch_verror(dup2(infile, STDIN_FILENO));
				catch_verror(dup2(pipes[WRITE_END], STDOUT_FILENO));
				execute(cmd1, envp);
				catch_verror(close(pipes[WRITE_END]));
				catch_verror(close(infile));
				ft_free_double_pointer((void **)cmd1);
			}
			else
				perror("Error: invalid <file1>");
		}
		else
		{
			pid = catch_error(fork());
			if (pid == 0) /* hijo 2 */
			{
				dest = open(FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				catch_oerror(cmd1, cmd2, dest);
				catch_verror(dup2(pipes[READ_END], STDIN_FILENO));
				catch_verror(dup2(dest, STDOUT_FILENO));
				execute(cmd2, envp);
				catch_verror(close(pipes[READ_END]));
				catch_verror(close(dest));
				ft_free_double_pointer((void **)cmd2);
			}
		}
		wait(&status);
		wait(&status);
	}
	else
		printf("usage: ./pipex <file1> \"cmd1\" \"cmd2\" <file2>\n");
}
