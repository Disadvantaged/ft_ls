/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 15:17:53 by dgolear           #+#    #+#             */
/*   Updated: 2017/02/19 12:53:54 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_conv	g_conv[] =
{
	{'d', &print_int},
	{'D', &print_int},
	{'i', &print_int},
	{'%', &print_percent},
	{'n', &print_len},
	{'s', &print_string},
	{'S', &print_wstring},
	{'c', &print_char},
	{'C', &print_wchar},
	{'p', &print_adress},
	{'u', &print_unsigned},
	{'U', &print_unsigned},
	{'o', &print_unsigned},
	{'O', &print_unsigned},
	{'x', &print_unsigned},
	{'X', &print_unsigned},
};

int		g_num = 16;

int	print_percent(t_param *params, va_list ap, char letter)
{
	int		width;

	if (ap || letter)
		;
	if (params->width == 0)
		params->width = 1;
	width = params->width;
	if (params->flags[1].sign)
		ft_putchar('%');
	while (width > 1)
	{
		if (params->flags[2].sign)
			ft_putchar('0');
		else
			ft_putchar(' ');
		width--;
	}
	if (!params->flags[1].sign)
		ft_putchar('%');
	return (params->width);
}

int	conversion(const char *format, int *pos, t_param *params, va_list ap)
{
	int		i;
	int		printed;

	i = 0;
	while (i < g_num)
	{
		if (format[*pos] == g_conv[i].spec)
		{
			(*pos)++;
			return (g_conv[i].fun(params, ap, g_conv[i].spec));
		}
		i++;
	}
	if (params->width > 1)
		printed = params->width - 1;
	else
		printed = 0;
	if (params->flags[1].sign && params->width > 1)
		printed += ft_putchar(format[(*pos)++]);
	while (params->width > 1)
		if (!params->flags[2].sign)
			params->width -= ft_putstr(" ");
		else
			params->width -= ft_putstr("0");
	return (printed);
}
