/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 13:29:40 by dgolear           #+#    #+#             */
/*   Updated: 2017/02/28 16:54:07 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <sys/stat.h>
# include <dirent.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <sys/xattr.h>
# include <time.h>
# include <errno.h>
# include <sys/acl.h>
# include <sys/ioctl.h>
# define MAJOR(x)		((int32_t)(((u_int32_t)(x) >> 24) & 0xff))
# define MINOR(x)		((int32_t)((x) & 0xffffff))

typedef struct	s_flag
{
	char	letter;
	int		sign;
}				t_flag;

/*
** flags[0] - R(recursion)
** flags[1] - r(reverse)
** flags[2] - G(colored)
** flags[3] - l(list)
** flags[4] - t(last time modified instead of lexicographical order)
** flags[5] - a(all files including hidden)
** flags[6] - f(output is not sorted. This option turn on -a option)
** flags[7] - u(time of last access instead of last modification for -t or -l)
** flags[8] - g(user's name is ignored in -l)
** flags[9] - d(all directories are listed as simple files)
** flags[10] - 1(1 entry per line)
** flags[11] - S(sorting by size)
*/

enum			e_sort
{
	size,
	name,
	sec
};

typedef struct	s_option
{
	t_flag		flags[20];
	int			cursize;
	enum e_sort	sort;
	int			maxsize;
	char		**paths;
}				t_option;

typedef struct	s_directory
{
	char		*path;
	DIR			*dir;
	struct stat	statbuf;
	time_t		time;
}				t_directory;

typedef struct	s_file
{
	char			*path;
	char			*name;
	struct stat		statbuf;
	char			*mode;
	time_t			time;
	struct passwd	*pass;
	struct group	*group;
	nlink_t			nlink;
	off_t			size;
	blkcnt_t		blocks;
}				t_file;

struct			s_max
{
	int					size;
	unsigned long		passlen;
	unsigned long		name;
	unsigned long		grouplen;
	int					link;
	int					maj;
	int					min;
};

t_option		*check_options(int ac, char **av);
void			path_to_dir(t_option *options, t_list **dir, t_list **file);
t_file			*get_file_data(char *path, t_option *options);
void			ft_ls(t_option *options, t_list *files, t_list *dirs);
void			free_options(t_option *options);
void			free_dir(t_directory *dir);
void			free_dirs(t_list *dirs);
void			free_files(t_list *files);
void			sort_list(t_option *options, t_list **head);
void			print_files(t_option *options, t_list **files, int flag);
void			inner_ls(t_option *options, t_directory *data);
t_list			*create_file(char *path, t_option *options);
t_directory		*create_dir(char *path, t_option *options);
int				get_total(t_list *files);
t_list			*get_files(t_option *options, t_directory *data);

#endif
