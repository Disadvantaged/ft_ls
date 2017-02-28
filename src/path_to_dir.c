/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_to_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 12:14:41 by dgolear           #+#    #+#             */
/*   Updated: 2017/02/27 18:29:17 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_directory	*create_dir(char *path, t_option *options)
{
	DIR			*directory;
	t_directory	*dirt;
	struct stat	statbuf;

	if ((dirt = (t_directory*)malloc(sizeof(t_directory))) == NULL)
		return (NULL);
	if ((directory = opendir(path)) == NULL || lstat(path, &statbuf) < 0)
	{
		free(dirt);
		return (NULL);
	}
	dirt->path = ft_strdup(path);
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
	t_file	*file;
	t_list	*node;

	if ((node = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	if ((file = get_file_data(path, options)) == NULL)
	{
		free(node);
		return (NULL);
	}
	node->next = NULL;
	node->content = file;
	node->content_size = sizeof(file);
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
		options->flags[3].sign ? lstat(options->paths[i], &statbuf)
		: stat(options->paths[i], &statbuf);
		node = (t_list *)malloc(sizeof(t_list));
		node->next = NULL;
		node->content = (S_ISDIR(statbuf.st_mode) && !options->flags[9].sign)
		? (void *)create_dir(options->paths[i], options) :
		(void *)get_file_data(options->paths[i], options);
		if (node->content == NULL)
		{
			free(node);
			ft_printf("ls: %s: %s\n", options->paths[i++], strerror(errno));
			continue;
		}
		ft_lstaddlast(S_ISDIR(statbuf.st_mode) && !options->flags[9].sign
			? dir : file, node);
		i++;
	}
}
