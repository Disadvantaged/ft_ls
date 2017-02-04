/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 15:13:07 by dgolear           #+#    #+#             */
/*   Updated: 2017/02/04 13:08:42 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include <dirent.h>
#include <sys/xattr.h>
#include <sys/stat.h>
#include <sys/acl.h>
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
	int				size;
	char			*path;
	struct stat		buf;
	struct passwd	*pass;
	acl_t			acl;
	acl_entry_t		dummy;
	struct group	*grp;
	char			buffer[100];

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
	stat(av, &buf);
	while ((dir = readdir(directory)) != NULL)
	{
		if (dir->d_name[0] == '.')
			continue;
		s = ft_strjoin(path, dir->d_name);

/* ************************************************************************** */
		/* extended attributes and access control lists */
		acl = acl_get_link_np(s, ACL_TYPE_EXTENDED);
		if (listxattr(s, NULL, 0, 0) > 0)
			ft_printf("@");
		else if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) != -1)
			ft_printf("+");
		else
			ft_printf(" ");
/* ************************************************************************** */
		lstat(s, &buf);
		pass = getpwuid(buf.st_uid);
		grp = getgrgid(buf.st_gid);
		time = ft_strsplit(ctime(&buf.st_mtime), ' ');
		ft_printf("%3u %7s  %s %5lld %s %2s %.5s %s", buf.st_nlink,
			pass->pw_name, grp->gr_name, buf.st_size, time[1],
			time[2], time[3], dir->d_name);
		if (S_ISLNK(buf.st_mode))
		{
			size = readlink(s, buffer, 99);
			if (size != -1)
				buffer[size] = '\0';
			else
			{
				ft_printf("ft_ls: %s", strerror(errno));
				exit(-1);
			}
			ft_printf(" -> %s", buffer);
		}
		ft_printf("\n");
		ft_strdel(&s);
	}
	closedir(directory);
}

int		main(int ac, char **av)
{
	ft_ls(av[ac - 1]);
}
