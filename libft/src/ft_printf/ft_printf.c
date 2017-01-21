/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/23 16:00:34 by dgolear           #+#    #+#             */
/*   Updated: 2017/01/21 12:27:59 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		g_len = 0;

void	find_color(const char *format, int *i)
{
	int		j;
	char	*str;
	char	*tmp;
	char	temp[2];
	int		color;

	temp[1] = '\0';
	str = ft_strnew(1);
	j = *i + 1;
	while (format[j] && format[j] != '}')
	{
		tmp = str;
		temp[0] = format[j];
		str = ft_strjoin(str, temp);
		ft_strdel(&tmp);
		j++;
	}
	color = enable_color(str);
	if (color != NO_COLOR)
		*i = j + 1;
	ft_strdel(&str);
}

int		enable_color(char *str)
{
	if (!ft_strcmp(str, "black"))
		ft_putstr(BLACK);
	else if (!ft_strcmp(str, "red"))
		ft_putstr(RED);
	else if (!ft_strcmp(str, "green"))
		ft_putstr(GREEN);
	else if (!ft_strcmp(str, "yellow"))
		ft_putstr(YELLOW);
	else if (!ft_strcmp(str, "blue"))
		ft_putstr(BLUE);
	else if (!ft_strcmp(str, "magenta"))
		ft_putstr(MAGENTA);
	else if (!ft_strcmp(str, "white"))
		ft_putstr(WHITE);
	else if (!ft_strcmp(str, "cyan"))
		ft_putstr(CYAN);
	else if (!ft_strcmp(str, "eoc"))
		ft_putstr(RESET);
	else
		return (NO_COLOR);
	return (0);
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	int			i;

	i = 0;
	g_len = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '{')
		{
			find_color(format, &i);
			continue;
		}
		if (format[i++] != '%')
		{
			ft_putchar(format[i - 1]);
			g_len++;
		}
		else
			check(format, &i, ap);
	}
	va_end(ap);
	return (g_len);
}

int		check(const char *format, int *pos, va_list ap)
{
	int			length;
	t_param		*params;

	length = 0;
	if ((params = (t_param*)ft_memalloc(sizeof(t_param))) == NULL
		|| (params->flags = check_flags(format, pos)) == NULL)
		return (0);
	if ((params->width = check_width(format, pos, ap)) < 0)
	{
		params->flags[1].sign = 1;
		params->width *= -1;
	}
	params->precision = check_precision(format, pos, ap);
	if (params->precision != NO_PRECISION)
		params->flags[2].sign = 0;
	params->mod = check_length(format, pos);
	if ((length = conversion(format, pos, params, ap)) == -1)
		return (0);
	free(params->flags);
	free(params);
	g_len += length;
	return (0);
}

int		print_len(t_param *params, va_list ap, char letter)
{
	int		*pointer;

	if (params || letter)
		;
	pointer = va_arg(ap, int *);
	*pointer = g_len;
	return (0);
}
