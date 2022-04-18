/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunez <snunez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:27:25 by snunez            #+#    #+#             */
/*   Updated: 2022/04/18 12:34:21 by snunez           ###   ########.fr       */
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
#ifndef FILE_NAME
# define FILE_NAME "file.txt"
#endif
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

int		catch_error(int error);
void	catch_verror(int error);
#endif