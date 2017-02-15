/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 11:49:51 by dgolear           #+#    #+#             */
/*   Updated: 2017/02/15 19:23:41 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

struct s_max	init_max(void)
{
	struct s_max	max;

	max.passlen = 0;
	max.grouplen = 0;
	max.link = 0;
	max.name = 0;
	max.size = 0;
	max.maj = 0;
	max.min = 0;
	return (max);
}

struct s_max	get_max(t_list **files)
{
	t_list			*n;
	struct s_max	max;

	n = *files;
	max = init_max();
	while (n != NULL)
	{
		if (ft_nbrlen(((t_file *)n->content)->size) > max.size)
			max.size = ft_nbrlen(((t_file *)n->content)->size);
		if (ft_strlen(((t_file *)n->content)->pass->pw_name) > max.passlen)
			max.passlen = ft_strlen(((t_file *)n->content)->pass->pw_name);
		if (ft_strlen(((t_file *)n->content)->group->gr_name) > max.grouplen)
			max.grouplen = ft_strlen(((t_file *)n->content)->group->gr_name);
		if (ft_nbrlen(((t_file *)n->content)->nlink) > max.link)
			max.link = ft_nbrlen(((t_file *)n->content)->nlink);
		if (ft_strlen(((t_file *)n->content)->name) > max.name)
			max.name = ft_strlen(((t_file *)n->content)->name);
		if (ft_nbrlen(MAJOR(((t_file *)n->content)->statbuf.st_rdev)) > max.maj)
			max.maj = ft_nbrlen(MAJOR(((t_file *)n->content)->statbuf.st_rdev));
		if (ft_nbrlen(MINOR(((t_file *)n->content)->statbuf.st_rdev)) > max.min)
			max.min = ft_nbrlen(MINOR(((t_file *)n->content)->statbuf.st_rdev));
		n = n->next;
	}
	return (max);
}

void			print_long(t_file *data, struct s_max max, t_option *options)
{
	char	*tim;
	char	buffer[256];
	int		size;

	tim = ctime(&data->time) + 4;
	ft_printf("%s %*d ", data->mode, max.link, data->nlink);
	if (!options->flags[8].sign)
		ft_printf("%-*s  ", max.passlen, data->pass->pw_name);
	ft_printf("%-*s  ", max.grouplen, data->group->gr_name);
	if (data->mode[0] == 'c' || data->mode[0] == 'b')
		ft_printf("%*d, %*d", max.maj + 1, MAJOR(data->statbuf.st_rdev),
		max.min, MINOR(data->statbuf.st_rdev));
	else
		ft_printf("%*d", ((max.maj + max.min > max.size + 1))
		? max.maj + max.min + 3 : max.size, data->size);
	ft_printf(" %.7s%.5s %s", tim,
		(time(0) - data->time > 15778463) ? tim + 15 : tim + 7, data->name);
	if (S_ISLNK(data->statbuf.st_mode))
	{
		if ((size = readlink(data->path, buffer, 255)) == -1)
			exit(ft_printf("ft_ls: %s", strerror(errno)) * 0 + errno);
		buffer[size] = '\0';
		ft_printf(" -> %s", buffer);
	}
	ft_printf("\n");
}

void			print_files(t_option *options, t_list **files)
{
	t_list			*node;
	t_file			*data;
	struct s_max	max;

	if (*files == NULL)
		return ;
	if (options->flags[3].sign)
		ft_printf("total %d\n", get_total(*files));
	max = get_max(files);
	node = *files;
	while (node != NULL)
	{
		data = node->content;
		if (options->flags[3].sign)
			print_long(data, max, options);
		else
			ft_printf("%s\n", data->name);
		node = node->next;
	}
}
