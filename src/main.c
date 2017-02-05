/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 15:25:36 by dgolear           #+#    #+#             */
/*   Updated: 2017/02/05 13:06:17 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sort_files_and_dirs(t_options *options, t_list *dir, t_list *file)
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
	sort_files_and_dirs(options, &dir, &file);
	return (0);
}
