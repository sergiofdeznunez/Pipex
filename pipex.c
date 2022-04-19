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
	cmd = ft_strsplit(line, ' ');
	return (cmd);
}

void	execute(char **cmd/*, **envp??)*/)
{
}

int	main(int argc, char **argv/*, **envp??*/)
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
		if (cmd1 == NULL || cmd2 == NULL)
			return (printf("Error: command input\n"));
		pid = catch_error(fork());
		if (pid == 0) /* hijo 1*/
		{
			infile = open(argv[1], O_RDONLY); /*manage error*/
			catch_verror(close(pipes[READ_END]));
			catch_verror(dup2(infile, STDIN_FILENO));
			catch_verror(dup2(pipes[WRITE_END], STDOUT_FILENO));
			execute(cmd1);
			catch_verror(close(pipes[WRITE_END]));
			catch_verror(close(infile));
			free(cmd1);
		}
		else
		{
			pid = catch_error(fork());
			if (pid == 0) /* hijo 2 */
			{
				dest = open(FILE_NAME, O_WRONLY); /* manage error*/
				catch_verror(dup2(pipes[READ_END], STDIN_FILENO));
				catch_verror(dup2(dest, STDOUT_FILENO));
				execute(cmd2);
				catch_verror(close(pipes[READ_END]));
				catch_verror(close(dest));
				free(cmd2);
			}

		}
		wait(&status);
		wait(&status);
	}
	else
		printf("usage: ./pipex <file1> \"cmd1\" \"cmd2\" <file2>\n");
}