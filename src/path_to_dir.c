/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_to_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 12:14:41 by dgolear           #+#    #+#             */
/*   Updated: 2017/02/04 14:11:25 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_list	*create_dir(t_option *options, int pos)
{
	DIR			*directory;
	t_directory	*dirt;
	t_list		*node;

	if ((dirt = (t_directory*)malloc(sizeof(t_directory))) == NULL
		|| (node = (t_list *)malloc(sizeof(t_list))) == NULL
		|| (directory = opendir(options->paths[pos])) == NULL)
	{
		ft_printf("ft_ls: %s: %s\n", options->paths[pos], strerror(errno));
		exit(errno);
	}
	dirt->path = ft_strdup(options->paths[pos]);
	dirt->dir = directory;
	node->content = dirt;
	node->next = NULL;
	node->content_size = sizeof(dirt);
	return (node);
}

static	t_list	*create_file(t_option *options, int pos)
{
	t_file	*filet;
	t_list	*node;

	if ((node = (t_list *)malloc(sizeof(t_list))) == NULL)
	{
		ft_printf("ft_ls: %s: %s\n", options->paths[pos], strerror(errno));
		exit(errno);
	}
	filet = get_file_data(options->paths[pos], "");
	node->content = filet;
	node->next = NULL;
	node->content_size = sizeof(filet);
	return (node);
}

void			path_to_dir(t_option *options, t_list **dir, t_list **file)
{
	struct stat	statbuf;
	int			i;

	i = 0;
	while (i < options->cursize)
	{
		if (lstat(options->paths[i], &statbuf) < 0)
			exit(ft_printf("ft_ls: %s: %s\n",
						options->paths[i], strerror(errno)));
		if (statbuf.st_mode & S_IFDIR && !options->flags[9].sign)
			ft_lstadd(dir, create_dir(options, i));
		else
			ft_lstadd(file, create_file(options, i));
		i++;
	}
}
