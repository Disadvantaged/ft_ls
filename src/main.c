/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 15:25:36 by dgolear           #+#    #+#             */
/*   Updated: 2017/01/27 16:10:55 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	t_option		*options;
	t_list			*dir;
	t_list			*file;
	t_list			*node;
	struct dirent	*directory;
	int				i;

	options = check_options(ac, av);
	dir = NULL;
	file = NULL;
	path_to_dir(options, &dir, &file);
	node = file;
	i = ft_lstlen(file);
	while (node != NULL)
	{
		if (node->next != NULL)
			ft_printf("%s\t", ((t_file*)node->content)->path);
		else
			ft_printf("%s\n", ((t_file*)node->content)->path);
		node = node->next;
	}
	node = dir;
	i = ft_lstlen(dir);
	while (node != NULL)
	{
		if (file != NULL || i > 1)
			ft_printf("\n%s:\n", ((t_directory *)node->content)->path);
		while ((directory = readdir(((t_directory *)node->content)->dir)) != NULL)
		{
			if (directory->d_name[0] == '.' && !options->flags[5].sign)
				continue ;
				ft_printf("%s\t", directory->d_name);
		}
		node = node->next;
	}
	return (0);
}
