/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 15:25:36 by dgolear           #+#    #+#             */
/*   Updated: 2017/01/25 16:42:54 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	int			i;
	t_option	*options;

	i = 0;
	options = check_options(ac, av);
	while (i < options->cursize)
		ft_printf("%s\n", options->paths[i++]);
	return (0);
}
