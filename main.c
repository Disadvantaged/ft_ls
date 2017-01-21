/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 15:13:07 by dgolear           #+#    #+#             */
/*   Updated: 2017/01/21 12:32:32 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <errno.h>
#include <time.h>
#include <grp.h>

void	ft_ls	(char *av)
{
	struct dirent	*dir;
	DIR				*directory;
	char			*s;
	char			**time;
	char			*path;
	struct stat		buf;
	struct passwd	*pass;
	struct group	*grp;

	if ((directory = opendir(av)) == NULL && errno != ENOTDIR)
	{
		ft_printf("ls: %s: %s\n", av, strerror(errno));
		return ;
	}
	else if (errno == ENOTDIR)
	{
		ft_printf("%s\n", av);
		return ;
	}
	path = ft_strnew(20);
	path = ft_strcat(av, "/");
	while ((dir = readdir(directory)) != NULL)
	{
		if (dir->d_name[0] == '.')
			continue;
		s = ft_strjoin(path, dir->d_name);
		stat(s, &buf);
		pass = getpwuid(buf.st_uid);
		grp = getgrgid(buf.st_gid);
		time = ft_strsplit(ctime(&buf.st_mtime), ' ');
		ft_printf("%3u %7s  %s %5lld %s %2s %.5s %s\n", buf.st_nlink,
			pass->pw_name, grp->gr_name, buf.st_size, time[1], time[2], time[3], dir->d_name);
		ft_strdel(&s);
	}
	closedir(directory);
}

int		main(int ac, char **av)
{
	ft_ls(av[ac - 1]);
}
