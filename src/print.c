/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 11:49:51 by dgolear           #+#    #+#             */
/*   Updated: 2017/02/12 13:21:45 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

struct s_max	get_max(t_list **files)
{
	t_list			*node;
	struct s_max	max;

	node = *files;
	max.size = ft_nbrlen(((t_file *)node->content)->size);
	max.passlen = ft_strlen(((t_file *)node->content)->pass->pw_name);
	max.grouplen = ft_strlen(((t_file *)node->content)->group->gr_name);
	max.link = ft_nbrlen(((t_file *)node->content)->nlink);
	max.name = ft_strlen(((t_file *)node->content)->name);
	while (node != NULL)
	{
		if (ft_nbrlen(((t_file *)node->content)->size) > max.size)
			max.size = ft_nbrlen(((t_file *)node->content)->size);
		if (ft_strlen(((t_file *)node->content)->pass->pw_name) > max.passlen)
			max.passlen = ft_strlen(((t_file *)node->content)->pass->pw_name);
		if (ft_strlen(((t_file *)node->content)->group->gr_name) > max.grouplen)
			max.grouplen = ft_strlen(((t_file *)node->content)->group->gr_name);
		if (ft_nbrlen(((t_file *)node->content)->nlink) > max.size)
			max.link = ft_nbrlen(((t_file *)node->content)->nlink);
		if (ft_strlen(((t_file *)node->content)->name) > max.name)
			max.name = ft_strlen(((t_file *)node->content)->name);
		node = node->next;
	}
	return (max);
}

void			print_long(t_file *data, struct s_max max, t_option *options)
{
	char	*tim;
	char	buffer[100];
	int		size;

	tim = ctime(&data->time) + 4;
	ft_printf("%s %*d ", data->mode, max.link, data->nlink);
	if (!options->flags[8].sign)
		ft_printf("%-*s  ", max.passlen, data->pass->pw_name);
	ft_printf("%-*s  %*d ", max.grouplen, data->group->gr_name,
			max.size, data->size);
	if (time(0) - data->time > 15778463)
		ft_printf("%.7s%.5s ", tim, tim + 15);
	else
		ft_printf("%.7s%.5s ", tim, tim + 7);
	if (S_ISLNK(data->statbuf.st_mode))
	{
		size = readlink(data->path, buffer, 99);
		if (size != -1)
			buffer[size] = '\0';
		else
			exit(ft_printf("ft_ls: %s", strerror(errno)) * 0 + errno);
		ft_printf("%s -> %s\n", data->name, buffer);
	}
	else
		ft_printf("%s\n", data->name);
}

void			print_columns(t_file *data, struct s_max max,
				t_option *options, int num)
{
	struct winsize	w;
	int				i;

	i = 0;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

}

void			print_files(t_option *options, t_list **files)
{
	t_list			*node;
	t_file			*data;
	struct s_max	max;

	if (*files == NULL)
		return ;
	max = get_max(files);
	node = *files;
	if (!options->flags[3].sign && !options->flags[10].sign)
		print_columns(data, max, options, ft_lstlen(node));
	else
		while (node != NULL)
		{
			data = node->content;
			if (options->flags[3].sign)
				print_long(data, max, options);
			else if (options->flags[10].sign)
				ft_printf("%s\n", data->name);
			node = node->next;
		}
}
