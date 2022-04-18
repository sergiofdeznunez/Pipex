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

int	main(int argc, char **argv)
{
	int		pipes[2];
	int		infile, dest, status;
	pid_t	pid, pid2;
	char	**cmd1; /*need to be taken*/
	char	**cmd2; /*need to be taken*/

	if (argc == 5)
	{
		pipe(pipes);
		pid = catch_error(fork());

		if (pid == 0) /* hijo */
		{
			catch_verror(close(pipes[READ_END]));
			catch_verror(dup2(infile, STDIN_FILENO));
			catch_verror(dup2(pipes[WRITE_END], STDOUT_FILENO));
			catch_verror(close(pipes[WRITE_END]));
			execve(cmd1);
		}
		else
		{

		}
	}

}