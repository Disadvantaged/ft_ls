/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 16:42:31 by dgolear           #+#    #+#             */
/*   Updated: 2017/01/15 17:01:17 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_sign(intmax_t val, t_param *params)
{
	params->width--;
	if (val < 0)
		return (ft_putstr("-"));
	else
	{
		if (params->flags[0].sign)
			return (ft_putstr("+"));
		else
			return (ft_putstr(" "));
	}
}
