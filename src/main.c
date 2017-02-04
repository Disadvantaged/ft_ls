/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 15:25:36 by dgolear           #+#    #+#             */
/*   Updated: 2017/02/04 16:09:36 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sort_files(t_list **file, t_option *options)
{
	if (options->flags[6])
		return ;
}

void	sort_dirs(t_list **dir, t_option *options)
{
	if (options->flags[6])
		return ;
}

int		main(int ac, char **av)
{
	t_option		*options;
	t_list			*dir;
	t_list			*file;

	options = check_options(ac, av);
	dir = NULL;
	file = NULL;
	path_to_dir(options, &dir, &file);
	sort_files(&file, options);
	sort_dirs(&dir, options);
	return (0);
}
