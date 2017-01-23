/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 13:29:40 by dgolear           #+#    #+#             */
/*   Updated: 2017/01/23 19:21:21 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
#define FT_LS_H

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

typedef struct	s_option
{
	t_flag	flags[10];
	int		cursize;
	int		maxsize;
	char	**paths;

}				t_option;

t_option	*check_options(int ac, char **av);
void		path_to_dir(t_option *options);
void		ft_ls(t_option *options);
void		free_options(t_option *options);

#endif
