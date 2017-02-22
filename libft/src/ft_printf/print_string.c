/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 16:30:18 by dgolear           #+#    #+#             */
/*   Updated: 2017/02/19 13:21:44 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	min(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

static int	print_width(char *s, t_param *params)
{
	int		printed;
	int		len;
	int		width;

	width = params->width;
	len = ft_strlen(s);
	if (params->precision != NO_PRECISION)
		len = min(len, params->precision);
	if (len == 0 && width == 1)
		width = 0;
	printed = 0;
	while (width > len)
	{
		if (params->flags[2].sign)
			ft_putchar('0');
		else
			ft_putchar(' ');
		width--;
		printed++;
	}
	return (printed);
}

static int	print_s(t_param *params, char *s)
{
	int		printed;

	printed = 0;
	if (params->precision == NO_PRECISION)
		printed += ft_putstr(s);
	else
		printed += ft_putnstr(s, params->precision);
	return (printed);
}

int			print_string(t_param *params, va_list ap, char letter)
{
	char	*s;
	int		printed;

	if (params->mod == l)
		return (print_wstring(params, ap, letter));
	s = NULL;
	printed = 0;
	if ((s = va_arg(ap, char *)) == NULL)
		s = "(null)";
	if (params->flags[1].sign == 0)
		printed += print_width(s, params);
	printed += print_s(params, s);
	if (params->flags[1].sign != 0)
		printed += print_width(s, params);
	return (printed);
}
