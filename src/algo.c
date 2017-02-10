/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 18:17:34 by dgolear           #+#    #+#             */
/*   Updated: 2017/02/10 18:26:48 by dgolear          ###   ########.fr       */
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

	if (*files == NULL)
		return ;
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

int				get_total(t_list *files, t_list *dirs)
{
	t_list		*node;
	t_file		*file;
	t_directory	*dr;
	int			total;

	total = 0;
	node = files;
	while (node != NULL)
	{
		total += ((t_file *)node->content)->statbuf.st_blocks;
		node = node->next;
	}
	node = dirs;
	while (node != NULL)
	{
		total += ((t_directory *)node->content)->statbuf.st_blocks;
		node = node->next;
	}
	return (total);
}

void			inner_ls(t_option *options, t_directory *data)
{
	t_list			*files;
	t_list			*dirs;
	struct dirent 	*dr;
	char			*path;

	dirs = NULL;
	files = NULL;
	errno = 0;
	while ((dr = readdir(data->dir)) != NULL)
	{
		path = ft_strjoin(data->path, dr->d_name);
		if (dr->d_type == 4 && options->flags[0].sign)
			ft_lstaddlast(&dirs, create_dir(path, options));
		else
			ft_lstaddlast(&files, create_file(path, options));
		ft_strdel(&path);
	}
	if (errno)
		exit(errno + 0 * ft_printf("ft_ls: %s\n", strerror(errno)));
	sort_list(options, &files);
	sort_list(options, &dirs);
	ft_printf("total %d\n", get_total(files, dirs));
	print_files(options, &files);
//	free_files(&files);
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
		if (ft_lstlen(dirs) > 1)
			ft_printf("%s:\n", ((t_directory *)node->content)->path);
		inner_ls(options, (t_directory *)node->content);
		if (node->next != NULL)
			ft_printf("\n");
		node = node->next;
	}
}
