/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_charchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 13:47:27 by dgolear           #+#    #+#             */
/*   Updated: 2017/01/15 16:10:15 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_width(t_param *params)
{
	int		width;

	width = params->width;
	if (width == 0)
		params->width = 1;
	while (width > 1)
	{
		if (params->flags[2].sign)
			ft_putchar('0');
		else
			ft_putchar(' ');
		width--;
	}
}

int			print_char(t_param *params, va_list ap, char letter)
{
	char	c;
	wchar_t	c1;

	if (letter == 'c')
		c = va_arg(ap, int);
	else
		c1 = va_arg(ap, wchar_t);
	if (params->flags[1].sign)
	{
		if (letter == 'c')
			ft_putchar(c);
		else
			ft_putwchar(c1);
		print_width(params);
	}
	else
	{
		print_width(params);
		if (letter == 'c')
			ft_putchar(c);
		else
			ft_putwchar(c1);
	}
	return (params->width);
}
