/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 18:17:34 by dgolear           #+#    #+#             */
/*   Updated: 2017/02/12 12:12:12 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				get_total(t_list *files, t_list *dirs)
{
	t_list		*node;
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

void			get_files_and_dirs(t_option *options,
		t_directory *data, t_list **d, t_list **f)
{
	t_list			*files;
	t_list			*dirs;
	struct dirent	*dr;
	struct stat		stat;
	char			*path;

	files = NULL;
	dirs = NULL;
	while ((dr = readdir(data->dir)) != NULL)
	{
		if (dr->d_name[0] == '.' && options->flags[5].sign == 0)
			continue ;
		path = ft_strjoin(data->path, dr->d_name);
		lstat(path, &stat);
		if (S_ISDIR(stat.st_mode) && options->flags[0].sign &&
!(ft_strcmp("..", dr->d_name) == 0) && !(ft_strcmp(".", dr->d_name) == 0))
			ft_lstaddlast(&dirs, create_dir(path, options));
		ft_lstaddlast(&files, create_file(path, options));
		ft_strdel(&path);
	}
	sort_list(options, &files);
	sort_list(options, &dirs);
	*d = dirs;
	*f = files;
}

void			recursion(t_option *options, t_list *dirs)
{
	t_list			*node;
	char			*path;

	node = dirs;
	while (node != NULL)
	{
		path = ((t_directory *)node->content)->path;
		ft_printf("%.*s:\n", (int)ft_strlen(path) - 1, path);
		inner_ls(options, node->content);
		if (node->next != NULL)
			ft_printf("\n");
		node = node->next;
	}
}

void			inner_ls(t_option *options, t_directory *data)
{
	t_list			*files;
	t_list			*dirs;

	dirs = NULL;
	files = NULL;
	get_files_and_dirs(options, data, &dirs, &files);
	if (options->flags[3].sign)
		ft_printf("total %d\n", get_total(files, dirs));
	print_files(options, &files);
	free_files(files);
	if (dirs != NULL)
	{
		ft_printf("\n");
		recursion(options, dirs);
	}
	free_dirs(dirs);
}

void			ft_ls(t_option *options, t_list *files, t_list *dirs)
{
	t_list	*node;
	char	*path;

	if (files != NULL)
	{
		print_files(options, &files);
		if (dirs != NULL)
			ft_printf("\n");
		free_files(files);
	}
	if (dirs != NULL)
	{
		node = dirs;
		while (node != NULL)
		{
			path = ((t_directory *)node->content)->path;
			if (ft_lstlen(dirs) > 1)
				ft_printf("%.*s:\n", (int)ft_strlen(path) - 1, path);
			inner_ls(options, (t_directory *)node->content);
			if (node->next != NULL)
				ft_printf("\n");
			node = node->next;
		}
		free_dirs(dirs);
	}
}
