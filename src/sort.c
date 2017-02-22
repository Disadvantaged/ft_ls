/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 18:15:06 by dgolear           #+#    #+#             */
/*   Updated: 2017/02/22 16:10:01 by dgolear          ###   ########.fr       */
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
	char	*as;
	char	*bs;

	as = ((t_file *)a)->path;
	bs = ((t_file *)b)->path;
	atime = ((t_file *)a)->time;
	btime = ((t_file *)b)->time;
	if (atime == btime)
		return (ft_strcmp(as, bs));
	else
		return (atime - btime);
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
	if (options->flags[1].sign || options->flags[4].sign)
		ft_lstrev(head);
	if (options->flags[1].sign && options->flags[4].sign)
		ft_lstrev(head);
}
