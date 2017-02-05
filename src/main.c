/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 15:25:36 by dgolear           #+#    #+#             */
/*   Updated: 2017/02/05 16:02:03 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

intmax_t	name_compare(const void *a, const void *b)
{
	char	*as;
	char	*bs;

	as = ((t_file *)a)->path;
	bs = ((t_file *)b)->path;
	return (ft_strcmp(as, bs));
}

intmax_t	time_compare(const void *a, const void *b)
{
	time_t	atime;
	time_t	btime;

	atime = ((t_file *)a)->time;
	btime = ((t_file *)b)->time;
	if (atime == btime)
		return (ft_strcmp(((t_file *)a)->path, ((t_file *)b)->path));
	else
		return ((int)(atime - btime));
}

static void	sort_list(t_option *options, t_list **head)
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

int			main(int ac, char **av)
{
	t_option		*options;
	t_list			*dir;
	t_list			*file;
	t_list			*node;

	options = check_options(ac, av);
	dir = NULL;
	file = NULL;
	path_to_dir(options, &dir, &file);
	node = file;
	while (node != NULL)
	{
		ft_printf("%s\n", ((t_file *)node->content)->path);
		node = node->next;
	}
	sort_list(options, &dir);
	sort_list(options, &file);
	node = file;
	while (node != NULL)
	{
		ft_printf("%s\n", ((t_file *)node->content)->path);
		node = node->next;
	}
	return (0);
}
