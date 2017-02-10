/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 18:17:34 by dgolear           #+#    #+#             */
/*   Updated: 2017/02/10 17:11:59 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

struct s_max	get_max(t_list **files)
{
	t_list			*node;
	struct s_max	max;

	node = *files;
	max.size = ft_nbrlen(((t_file *)node->content)->size);
	max.namelen = ft_strlen(((t_file *)node->content)->pass->pw_name);
	max.grouplen = ft_strlen(((t_file *)node->content)->group->gr_name);
	max.link = ft_nbrlen(((t_file *)node->content)->nlink);
	while (node != NULL)
	{
		if (ft_nbrlen(((t_file *)node->content)->size) > max.size)
			max.size = ft_nbrlen(((t_file *)node->content)->size);
		if (ft_strlen(((t_file *)node->content)->pass->pw_name) > max.namelen)
			max.namelen = ft_strlen(((t_file *)node->content)->pass->pw_name);
		if (ft_strlen(((t_file *)node->content)->group->gr_name) > max.grouplen)
			max.grouplen = ft_strlen(((t_file *)node->content)->group->gr_name);
		if (ft_nbrlen(((t_file *)node->content)->nlink) > max.size)
			max.link = ft_nbrlen(((t_file *)node->content)->nlink);
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
		ft_printf("%-*s  ", max.namelen, data->pass->pw_name);
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
		ft_printf("%s -> %s\n", data->path, buffer);
	}
	else
		ft_printf("%s\n", data->path);
}

void			print_files(t_option *options, t_list **files)
{
	t_list			*node;
	t_file			*data;
	struct s_max	max;

	max = get_max(files);
	node = *files;
	while (node != NULL)
	{
		data = node->content;
		if (options->flags[3].sign)
			print_long(data, max, options);
		else
			ft_printf("%s\n", data->path);
		node = node->next;
	}
}

void			ft_ls(t_option *options, t_list *files, t_list *dirs)
{
	t_list	*node;

	if (files != NULL)
		print_files(options, &files);
//	free_files(&files);
	if (dirs != NULL)
		ft_printf("\n");
	node = dirs;
	while (node != NULL)
	{
//		inner_ls(options, node);
//		if (node->next != NULL)
//			ft_printf("\n");
		node = node->next;
	}
}
