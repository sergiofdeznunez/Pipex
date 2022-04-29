
  
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunez <snunez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:27:25 by snunez            #+#    #+#             */
/*   Updated: 2022/04/21 12:07:14 by snunez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
#ifndef READ_END
# define READ_END 0
#endif
#ifndef WRITE_END
# define WRITE_END 1
#endif
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "./Libft-Mia-/libft.h"

void	catch_oerror(char **cmd1, char **cmd2, int error);
int		check_cmds(char **cmd1, char **cmd2);
char	**get_routes(char **cmd, char **envp);
#endif