/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 18:15:06 by dgolear           #+#    #+#             */
/*   Updated: 2017/02/08 18:16:05 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static intmax_t	name_compare(const void *a, const void *b)
{
	char	*as;
	char	*bs;

	as = ((t_file *)a)->path;
	bs = ((t_file *)b)->path;
	return (ft_strcmp(as, bs));
}

static intmax_t	time_compare(const void *a, const void *b)
{
	time_t	atime;
	time_t	btime;

	atime = ((t_file *)a)->time;
	btime = ((t_file *)b)->time;
	ft_printf("%jd %jd\n", atime, btime);
	if (atime == btime)
		return (ft_strcmp(((t_file *)a)->path, ((t_file *)b)->path));
	else
		return (btime - atime);
}

void			sort_list(t_option *options, t_list **head)
{
	intmax_t	(*compare)(const void *, const void *);

	if (options->flags[6].sign)
		return ;
	if (options->flags[4].sign)
		compare = &time_compare;
	else
		compare = &name_compare;
	ft_lstsort(head, compare);
	if (options->flags[1].sign)
		ft_lstrev(head);
}
