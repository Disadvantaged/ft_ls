/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 13:29:40 by dgolear           #+#    #+#             */
/*   Updated: 2017/01/21 12:33:19 by dgolear          ###   ########.fr       */
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

typedef struct	s_color
{
	int		up_r;
	int		r;
	int		up_g;
	int		l;
	int		t;
	int		a;
	int		f;
	int		u;
	int		g;
	int		d;
	t_list	*files;

}				t_color;

#endif
