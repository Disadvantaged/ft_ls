/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 16:30:18 by dgolear           #+#    #+#             */
/*   Updated: 2017/01/17 17:28:40 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	min(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

static int	print_width(char *s, wchar_t *s1, char letter, t_param *params)
{
	int		printed;
	int		len;
	int		width;

	width = params->width;
	if (letter == 's')
		len = ft_strlen(s);
	else
		len = ft_wstrlen(s1);
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

int			print_s(t_param *params, char *s, wchar_t *s1, char letter)
{
	int		printed;

	printed = 0;
	if (letter == 's')
	{
		if (params->precision == NO_PRECISION)
			printed += ft_putstr(s);
		else
			printed += ft_putnstr(s, params->precision);
	}
	else
	{
		if (params->precision == NO_PRECISION)
			printed += ft_putwstr(s1);
		else
			printed += ft_putnwstr(s1, params->precision);
	}
	return (printed);
}

int			print_string(t_param *params, va_list ap, char letter)
{
	char	*s;
	wchar_t	*s1;
	int		printed;

	printed = 0;
	if (letter == 'S')
		s1 = va_arg(ap, wchar_t *);
	else
	{
		if ((s = va_arg(ap, char *)) == NULL)
			s = ft_strdup("(null)");
	}
	if (params->flags[1].sign == 0)
	{
		printed += print_width(s, s1, letter, params);
		printed += print_s(params, s, s1, letter);
	}
	else
	{
		printed += print_s(params, s, s1, letter);
		printed += print_width(s, s1, letter, params);
	}
	return (printed);
}
