/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 18:17:34 by dgolear           #+#    #+#             */
/*   Updated: 2017/02/08 18:23:29 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_ls(t_option *options, t_list *files, t_list *dirs)
{
	t_list	*node;

	if (files != NULL)
		print_files(&files);
//	free_files(&files);
	if (dirs != NULL)
		ft_printf("\n");
	node = dirs;
	while (node != NULL)
	{
		inner_ls(options, node);
		if (node->next != NULL)
			ft_printf("\n");
	}
}
