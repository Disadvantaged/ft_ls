/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 13:29:40 by dgolear           #+#    #+#             */
/*   Updated: 2017/01/27 13:24:35 by dgolear          ###   ########.fr       */
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
*/

typedef struct	s_option
{
	t_flag	flags[10];
	int		cursize;
	int		maxsize;
	char	**paths;

}				t_option;

typedef struct	s_directory
{
	char	*path;
	DIR		*dir;
}				t_directory;

typedef struct	s_file
{
	char		*path;
	struct stat file;
}				t_file;

t_option		*check_options(int ac, char **av);
void			path_to_dir(t_option *options, t_list **dir, t_list **file);
void			ft_ls(t_option *options);
void			free_options(t_option *options);

#endif
