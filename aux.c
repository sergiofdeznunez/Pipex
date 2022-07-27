/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunez <snunez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:27:19 by snunez            #+#    #+#             */
/*   Updated: 2022/04/30 12:56:20 by snunez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	catch_oerror(char **cmd1, int error)
{
	if (error == -1)
	{
		ft_free_double_pointer((void **)cmd1);
		perror("Error");
		exit(EXIT_FAILURE);
	}
}

char	**take_cmd(char *line)
{
	char	**cmd;

	if (!line)
		return (NULL);
	cmd = ft_split(line, ' ');
	return (cmd);
}

int	check_cmd(char **cmd1)
{
	if (cmd1 == NULL)
	{
		printf("Error: command input");
		ft_free_double_pointer((void **)cmd1);
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
	ft_free_double_pointer((void **)aux);
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
