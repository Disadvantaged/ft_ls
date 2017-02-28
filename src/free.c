/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 15:38:57 by dgolear           #+#    #+#             */
/*   Updated: 2017/02/27 17:19:33 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_options(t_option *options)
{
	int		i;

	if (options == NULL)
		return ;
	i = 0;
	while (i < options->cursize)
	{
		ft_strdel(&options->paths[i]);
		i++;
	}
	free(options->paths);
	free(options);
	options = NULL;
}

void	free_dir(t_directory *dr)
{
	ft_strdel(&dr->path);
	closedir(dr->dir);
	free(dr);
}

void	free_dirs(t_list *dirs)
{
	t_list		*temp;
	t_list		*node;

	node = dirs;
	if (node == NULL)
		return ;
	while (node != NULL)
	{
		temp = node;
		node = node->next;
		free_dir(temp->content);
		free(temp);
	}
	dirs = NULL;
}

void	free_files(t_list *files)
{
	t_list	*temp;
	t_list	*node;
	t_file	*file;

	node = files;
	if (node == NULL)
		return ;
	while (node != NULL)
	{
		temp = node;
		node = node->next;
		file = temp->content;
		ft_strdel(&file->path);
		ft_strdel(&file->name);
		ft_strdel(&file->mode);
		free(temp->content);
		free(temp);
	}
	files = NULL;
}
