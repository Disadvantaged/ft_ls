/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_to_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 12:14:41 by dgolear           #+#    #+#             */
/*   Updated: 2017/02/15 18:12:44 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_directory	*create_dir(char *path, t_option *options)
{
	DIR			*directory;
	t_directory	*dirt;
	struct stat	statbuf;

	if ((dirt = (t_directory*)malloc(sizeof(t_directory))) == NULL
		|| (directory = opendir(path)) == NULL || lstat(path, &statbuf) < 0)
		exit(ft_printf("ft_ls: %s: %s", path, strerror(errno)) * 0 + 1);
	if (path[ft_strlen(path) - 1] == '/')
		dirt->path = ft_strdup(path);
	else
		dirt->path = ft_strjoin(path, "/");
	dirt->dir = directory;
	dirt->statbuf = statbuf;
	if (options->flags[7].sign)
		dirt->time = statbuf.st_atime;
	else
		dirt->time = statbuf.st_mtime;
	return (dirt);
}

t_list		*create_file(char *path, t_option *options)
{
	t_file	*filet;
	t_list	*node;

	if ((node = (t_list *)malloc(sizeof(t_list))) == NULL)
	{
		ft_printf("ft_ls: %s: %s\n", path, strerror(errno));
		exit(errno);
	}
	filet = get_file_data(path, options);
	node->content = filet;
	node->next = NULL;
	node->content_size = sizeof(filet);
	return (node);
}

void		path_to_dir(t_option *options, t_list **dir, t_list **file)
{
	struct stat	statbuf;
	t_list		*node;
	int			i;

	i = 0;
	while (i < options->cursize)
	{
		if (lstat(options->paths[i], &statbuf) < 0)
			exit(1 + 0 * ft_printf("ft_ls: %s: %s\n", options->paths[i],
			strerror(errno)));
		if (S_ISDIR(statbuf.st_mode) && !options->flags[9].sign)
		{
			node = (t_list *)malloc(sizeof(t_list));
			node->next = NULL;
			node->content = create_dir(options->paths[i], options);
			ft_lstaddlast(dir, node);
		}
		else
			ft_lstaddlast(file, create_file(options->paths[i], options));
		i++;
	}
}
