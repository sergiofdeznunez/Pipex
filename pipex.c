/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunez <snunez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:27:19 by snunez            #+#    #+#             */
/*   Updated: 2022/04/11 14:13:52 by snunez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child()
{}

void	second_child()
{}

int	main(int argc, char **argv)
{
	int		end[2];
	int		dest;
	int		pid;
	int		status;

	if (argc == 5)
	{
		pipe(end);
		pid = catch_error(fork());
	}

}