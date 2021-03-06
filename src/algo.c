/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 18:17:34 by dgolear           #+#    #+#             */
/*   Updated: 2017/03/05 11:37:06 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				get_total(t_list *files)
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
	return (total);
}

t_list			*get_files(t_option *options, t_directory *data)
{
	t_list			*files;
	struct dirent	*dr;
	char			*path;
	char			*temp;

	files = NULL;
	while ((dr = readdir(data->dir)) != NULL)
	{
		if (dr->d_name[0] == '.' && options->flags[5].sign == 0)
			continue ;
		temp = ft_strjoin(data->path, "/");
		path = ft_strjoin(temp, dr->d_name);
		ft_lstaddlast(&files, create_file(path, options));
		ft_strdel(&path);
		ft_strdel(&temp);
	}
	sort_list(options, &files);
	return (files);
}

static void		recursion(t_list *files, t_option *options)
{
	t_file			*info;
	t_list			*node;
	t_directory		*dir;

	node = files;
	while (node != NULL)
	{
		info = node->content;
		if (options->flags[0].sign && S_ISDIR(info->statbuf.st_mode)
		&& ft_strcmp("..", info->name) && ft_strcmp(".", info->name))
		{
			ft_printf("\n%s:\n", info->path);
			if ((dir = create_dir(info->path, options)) == NULL)
			{
				ft_dprintf(STDERR_FILENO,
						"ls: %s: %s\n", info->name, strerror(errno));
				node = node->next;
				continue ;
			}
			inner_ls(options, dir);
			free_dir(dir);
		}
		node = node->next;
	}
}

void			inner_ls(t_option *options, t_directory *data)
{
	t_list			*files;

	files = get_files(options, data);
	if (options->flags[3].sign && files != NULL)
		ft_printf("total %d\n", get_total(files));
	print_files(options, &files, 0);
	if (options->flags[0].sign)
		recursion(files, options);
	free_files(files);
}

void			ft_ls(t_option *options, t_list *files, t_list *dirs)
{
	t_list	*node;
	char	*path;

	print_files(options, &files, 1);
	if (files != NULL && dirs != NULL)
		ft_printf("\n");
	node = dirs;
	while (node != NULL)
	{
		path = ((t_directory *)node->content)->path;
		if (ft_lstlen(dirs) > 1 || files != NULL || errno != 0)
			ft_printf("%s:\n", path);
		inner_ls(options, (t_directory *)node->content);
		if (node->next != NULL)
			ft_printf("\n");
		node = node->next;
	}
}
