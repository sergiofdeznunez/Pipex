/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunez <snunez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:27:19 by snunez            #+#    #+#             */
/*   Updated: 2022/04/21 12:01:41 by snunez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	catch_oerror(char **cmd1, char **cmd2, int error)
{
	if (error == -1)
	{
		ft_free_double_pointer((void **)cmd1);
		ft_free_double_pointer((void **)cmd2);
		perror("Error:");
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

char	**get_routes(char **cmd, char **envp)
{
	char	**routes;
	char	**aux;
	char	*tmp;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			aux = ft_split(envp[i], '=');
			routes = ft_split(aux[1], ':');
		}
		i++;
	}
	free(aux);
	i = 0;
	while (routes[i])
	{
		tmp = ft_strjoin(routes[i], "/");
		routes[i] = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		i++;
	}
	return (routes);
}
