/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunez <snunez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:27:19 by snunez            #+#    #+#             */
/*   Updated: 2022/04/21 11:50:11 by snunez           ###   ########.fr       */
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

	if (!line)
		return (NULL);
	cmd = ft_split(line, ' ');
	return (cmd);
}

void	execute(char **cmd, char **envp)
{
	char **routes;
	int i;
	int j = 0;

	i = 0;
	if (execve(cmd[0], cmd, envp) == -1)
	{
		routes = get_routes(cmd, envp);
		while (routes[j])
		{
			j++;
		}
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

int	main(int argc, char **argv, char **envp)
{
	int		pipes[2];
	int		infile;
	int		dest;
	int		status;
	pid_t	pid;
	char	**cmd1;
	char	**cmd2;

	if (argc == 5)
	{
		pipe(pipes);
		cmd1 = take_cmd(argv[2]);
		cmd2 = take_cmd(argv[3]);
		catch_verror(check_cmds(cmd1, cmd2));
		pid = catch_error(fork());
		//printf("pid = %d\n", pid);
		if (!pid) /* hijo 1*/
		{
			//printf("entro hijo 1\n");
			catch_verror(close(pipes[READ_END]));
			if (access(argv[1], R_OK) == 0)
			{
				infile = open(argv[1], O_RDONLY);
				catch_oerror(cmd1, cmd2, infile);
				catch_verror(dup2(infile, STDIN_FILENO));
				catch_verror(close(infile));
				catch_verror(dup2(pipes[WRITE_END], STDOUT_FILENO));
				catch_verror(close(pipes[WRITE_END]));
				execute(cmd1, envp);
			}
			else
			{
				printf("Error: invalid <file1>. ");
				catch_verror(-1);//¿¿catch_oerr??
			}
		 }
		else
		{
			catch_verror(close(pipes[WRITE_END]));
			pid = catch_error(fork());
			if (pid == 0) /* hijo 2 */
			{
				dest = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
				catch_oerror(cmd1, cmd2, dest);
				catch_verror(dup2(pipes[READ_END], STDIN_FILENO));
				catch_verror(close(pipes[READ_END]));
				catch_verror(dup2(dest, STDOUT_FILENO));
				execute(cmd2, envp);
			}
			else
				catch_verror(close(pipes[READ_END]));
		}
		waitpid(pid, &status, 0);
		waitpid(pid, &status, 0);
		ft_free_double_pointer((void **)cmd1);
		ft_free_double_pointer((void **)cmd2);
	}
	else
		printf("usage: ./pipex <file1> \"cmd1\" \"cmd2\" <file2>\n");
}
