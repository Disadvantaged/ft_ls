/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 15:25:36 by dgolear           #+#    #+#             */
/*   Updated: 2017/02/28 16:36:50 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			main(int ac, char **av)
{
	t_option		*options;
	t_list			*dir;
	t_list			*file;

	errno = 0;
	options = check_options(ac, av);
	dir = NULL;
	file = NULL;
	path_to_dir(options, &dir, &file);
	if (!options->flags[6].sign)
	{
		sort_list(options, &file);
		sort_list(options, &dir);
	}
	ft_ls(options, file, dir);
	free_options(options);
	free_files(file);
	free_dirs(dir);
	return (0);
}
