/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunez <snunez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:27:19 by snunez            #+#    #+#             */
/*   Updated: 2022/04/18 12:34:24 by snunez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
//TODO: ADD THIS FT TO THE LIBFT
int	catch_error(int error)
{
	if (error == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	return (0);
}
//TODO: ADD THIS FT TO THE LIBFT
void	catch_verror(int error)
{
	if (error == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
}

int	check_cmds(char **cmd1, char **cmd2)
{
	if (cmd1 == NULL || cmd2 == NULL)
	{
		printf("Error: command input");
		ft_free_double_pointer((void **)cmd1);
		ft_free_double_pointer((void **)cmd2);
		return (-1);
	}
	return (0);
}