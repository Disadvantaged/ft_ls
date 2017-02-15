/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 12:05:26 by dgolear           #+#    #+#             */
/*   Updated: 2017/02/15 19:16:46 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	xattr_or_acl(char *path)
{
	acl_t		acl;
	acl_entry_t	dummy;
	int			xattr;

	acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	if (acl == NULL || acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	if ((xattr = listxattr(path, NULL, 0, XATTR_NOFOLLOW)) < 0)
		xattr = 0;
	if (xattr > 0)
		return ('@');
	else if (acl != NULL)
		return ('+');
	else
		return (' ');
}

static char	check_types(struct stat statbuf)
{
	if (S_ISDIR(statbuf.st_mode))
		return ('d');
	else if (S_ISBLK(statbuf.st_mode))
		return ('b');
	else if (S_ISFIFO(statbuf.st_mode))
		return ('p');
	else if (S_ISREG(statbuf.st_mode))
		return ('-');
	else if (S_ISLNK(statbuf.st_mode))
		return ('l');
	else if (S_ISSOCK(statbuf.st_mode))
		return ('s');
	else if (S_ISCHR(statbuf.st_mode))
		return ('c');
	else
		return ('?');
}

static void	check_executable_permissions(struct stat statbuf, char *mod)
{
	if (statbuf.st_mode & S_IXUSR && statbuf.st_mode & S_ISUID)
		mod[3] = 's';
	else if (!(statbuf.st_mode & S_IXUSR) && statbuf.st_mode & S_ISUID)
		mod[3] = 'S';
	else if (statbuf.st_mode & S_IXUSR)
		mod[3] = 'x';
	else
		mod[3] = '-';
	if (statbuf.st_mode & S_IXGRP && statbuf.st_mode & S_ISGID)
		mod[6] = 's';
	else if (!(statbuf.st_mode & S_IXGRP) && statbuf.st_mode & S_ISGID)
		mod[6] = 'S';
	else if (statbuf.st_mode & S_IXGRP)
		mod[6] = 'x';
	else
		mod[6] = '-';
	if (statbuf.st_mode & S_IXOTH && statbuf.st_mode & S_ISVTX)
		mod[9] = 't';
	else if (!(statbuf.st_mode & S_IXOTH) && statbuf.st_mode & S_ISVTX)
		mod[9] = 'T';
	else if (statbuf.st_mode & S_IXOTH)
		mod[9] = 'x';
	else
		mod[9] = '-';
}

static char	*mode(char *path, struct stat statbuf)
{
	char		*mod;

	if ((mod = ft_strnew(12)) == NULL)
		exit(ft_printf("ft_ls: %s: %s\n", path, strerror(errno)) * 0 - 1);
	mod[0] = check_types(statbuf);
	mod[1] = statbuf.st_mode & S_IRUSR ? 'r' : '-';
	mod[2] = statbuf.st_mode & S_IWUSR ? 'w' : '-';
	mod[4] = statbuf.st_mode & S_IRGRP ? 'r' : '-';
	mod[5] = statbuf.st_mode & S_IWGRP ? 'w' : '-';
	mod[7] = statbuf.st_mode & S_IROTH ? 'r' : '-';
	mod[8] = statbuf.st_mode & S_IWOTH ? 'w' : '-';
	check_executable_permissions(statbuf, mod);
	mod[10] = xattr_or_acl(path);
	return (mod);
}

t_file		*get_file_data(char *path, t_option *options)
{
	struct stat		statbuf;
	t_file			*filet;

	if ((filet = (t_file *)malloc(sizeof(t_file))) == NULL)
		exit(ft_printf("ls: %s: %s", path, strerror(errno)) * 0 + errno);
	filet->path = ft_strdup(path);
	if (ft_strrchr(filet->path, '/') == NULL)
		filet->name = ft_strdup(filet->path);
	else
		filet->name = ft_strdup(ft_strrchr(filet->path, '/') + 1);
	if (lstat(filet->path, &statbuf) < 0)
		exit(ft_printf("ls: %s: %s", path, strerror(errno)) * 0 + errno);
	filet->statbuf = statbuf;
	filet->mode = mode(path, statbuf);
	if (options->flags[7].sign)
		filet->time = statbuf.st_atime;
	else
		filet->time = statbuf.st_mtime;
	filet->group = getgrgid(statbuf.st_gid);
	filet->pass = getpwuid(statbuf.st_uid);
	filet->nlink = statbuf.st_nlink;
	filet->size = statbuf.st_size;
	filet->blocks = statbuf.st_blocks;
	return (filet);
}
