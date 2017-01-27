/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_to_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 12:14:41 by dgolear           #+#    #+#             */
/*   Updated: 2017/01/27 14:23:10 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	path_to_dir(t_option *options, t_list **dir, t_list **file)
{
	int			i;
	struct stat	statbuf;
	DIR			*directory;
	t_directory	*dirt;
	t_file		*filet;
	t_list		*node;

	if (dir || file)
		;
	i = 0;
	while (i < options->cursize)
	{
		if (stat(options->paths[i], &statbuf) < 0)
			exit(ft_printf("ft_ls: %s: %s\n",
						options->paths[i], strerror(errno)));
		if (statbuf.st_mode & S_IFDIR && !options->flags[9].sign)
		{
			if ((directory = opendir(options->paths[i])) == NULL)
				exit(ft_printf("ft_ls: %s: %s\n",
						options->paths[i], strerror(errno)));
			if ((dirt = (t_directory*)malloc(sizeof(t_directory))) == NULL)
				exit(ft_printf("ft_ls: %s", strerror(errno)));
			node = ft_lstnew(&dirt, sizeof(dirt));
			((t_directory *)node->content)->path = ft_strdup(options->paths[i]);
			((t_directory *)node->content)->dir = directory;
			ft_lstadd(dir, node);
			
		}
		else
		{
			if ((filet = (t_file*)malloc(sizeof(t_file))) == NULL
			|| (node = (t_list *)malloc(sizeof(t_list))) == NULL)
				exit(ft_printf("ft_ls: %s", strerror(errno)));
			filet->path = ft_strdup(options->paths[i]);
			filet->file = statbuf;
			node->content = filet;
			node->next = NULL;
			ft_lstadd(file, node);
		}
		i++;
	}
}
