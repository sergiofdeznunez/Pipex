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
	printf("entro a execute\n");
	if (execve(cmd[0], cmd, envp) == -1)
	{
		printf("entro a buscar rutas\n");
		routes = get_routes(cmd, envp);
		while (routes[j])
		{
			printf("ruta-> %s\n", routes[j]);
			j++;
		}
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
		cmd2 = take_cmd(argv[3]);
		catch_verror(check_cmds(cmd1, cmd2));
		printf("me separo\n");
		pid = catch_error(fork());
		printf("pid = %d\n", pid);
		if (pid == 0) /* hijo 1*/
		{
			printf("entro hijo 1\n");
			printf("access = %d\n", access(argv[1], R_OK));
			if (access(argv[1], R_OK) == 0)
			{
				printf("entro al if hijo1\n");
				infile = open(argv[1], O_RDONLY);
				catch_oerror(cmd1, cmd2, infile);
				printf("abro archivo infile\n");
				catch_verror(close(pipes[READ_END]));
				printf("cierro READ_END\n");
				catch_verror(dup2(STDIN_FILENO, infile));
				printf("infile = stdin\n");
				catch_verror(dup2(STDOUT_FILENO, pipes[WRITE_END]));
				printf("WRITE_END = stdout\n");
				printf("seteo pipes\n");
				execute(cmd1, envp);
				printf("ejecuto cmd1\n");
				catch_verror(close(pipes[WRITE_END]));
				catch_verror(close(infile));
				printf("cierro pipes\n");
				ft_free_double_pointer((void **)cmd1);
				printf("salgo hijo 1\n");
			}
			else
				perror("Error: invalid <file1>");
		}
		else
		{
			printf("entro padre\n");
			waitpid(pid, &status, 0);
			pid = catch_error(fork());
			if (pid == 0) /* hijo 2 */
			{
				printf("entro hijo 2\n");
				dest = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
				catch_oerror(cmd1, cmd2, dest);
				catch_verror(dup2(pipes[READ_END], STDIN_FILENO));
				catch_verror(dup2(dest, STDOUT_FILENO));
				execute(cmd2, envp);
				catch_verror(close(pipes[READ_END]));
				catch_verror(close(dest));
				ft_free_double_pointer((void **)cmd2);
			}
		}
		waitpid(pid, &status, 0);
	}
	else
		printf("usage: ./pipex <file1> \"cmd1\" \"cmd2\" <file2>\n");
}
