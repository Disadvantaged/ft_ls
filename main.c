/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 15:13:07 by dgolear           #+#    #+#             */
/*   Updated: 2017/01/19 17:50:09 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft/includes/libft.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <errno.h>

int		main(int ac, char **av)
{
/*	struct dirent	*dir;
	DIR				*directory;
	char			*path;
	char			*s;
	struct stat		buf;
	struct passwd	*pass;

	if ((directory = opendir(av[1])) == NULL && errno != ENOTDIR)
	{
		ft_printf("ls: %s: %s\n", av[1], strerror(errno));
		return (-1);
	}
	else if (errno == ENOTDIR)
	{
		ft_printf("%s\n", av[1]);
		return (0);
	}
	path = ft_strnew(20);
	path = ft_strcat(av[1], "/");
	while ((dir = readdir(directory)) != NULL)
	{
		if (ft_strcmp(dir->d_name, ".") == 0 || ft_strcmp(dir->d_name, "..") == 0)
			continue;
		s = ft_strjoin(path, dir->d_name);
		stat(s, &buf);
		pass = getpwuid(buf.st_uid);
		printf("%4lld %2u %7s ", buf.st_size,
			buf.st_nlink, pass->pw_name);
		if (S_ISDIR(buf.st_mode))
			ft_printf("{red}%s{eoc}\n", dir->d_name);
		else
			ft_printf("{blue}%s{eoc}\n", dir->d_name);
		ft_strdel(&s);
	}
*/
ft_printf("{blue} {eoc}%s");
}
