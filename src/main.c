/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 15:25:36 by dgolear           #+#    #+#             */
/*   Updated: 2017/02/15 17:22:16 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			main(int ac, char **av)
{
	t_option		*options;
	t_list			*dir;
	t_list			*file;

	options = check_options(ac, av);
	dir = NULL;
	file = NULL;
	path_to_dir(options, &dir, &file);
	sort_list(options, &file);
	sort_list(options, &dir);
	ft_ls(options, file, dir);
	free_options(options);
	return (0);
}
