/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 18:15:06 by dgolear           #+#    #+#             */
/*   Updated: 2017/03/04 11:46:20 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_option	*g_options;

static intmax_t	filecmp(const void *a, const void *b)
{
	int		cmp;
	t_file	*fa;
	t_file	*fb;

	fa = (t_file *)a;
	fb = (t_file *)b;
	cmp = 0;
	if (g_options->sort == size)
		cmp = fb->size - fa->size;
	else if (g_options->sort == sec)
	{
		if ((cmp = fb->time - fa->time) == 0 && g_options->flags[7].sign)
			cmp = fb->statbuf.st_atimespec.tv_nsec
				- fa->statbuf.st_atimespec.tv_nsec;
		if ((cmp = fb->time - fa->time) == 0 && !g_options->flags[7].sign)
			cmp = fb->statbuf.st_mtimespec.tv_nsec
				- fa->statbuf.st_mtimespec.tv_nsec;
	}
	if (cmp == 0)
		cmp = ft_strcmp(fa->path, fb->path);
	return (g_options->flags[1].sign ? 0 - cmp : cmp);
}

void			sort_list(t_option *options, t_list **head)
{
	g_options = options;
	ft_lstsort(head, &filecmp);
}
