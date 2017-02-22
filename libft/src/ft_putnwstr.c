/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnwstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 14:07:43 by dgolear           #+#    #+#             */
/*   Updated: 2017/02/19 14:25:21 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putnwstr(wchar_t *s, int len)
{
	int		i;

	i = 0;
	while (*s && i < len)
	{
		if (*s <= 0x7F)
			i++;
		else if (*s <= 0x7FF)
			i += 2;
		else if (*s <= 0xFFFF)
			i += 3;
		else if (*s <= 0x10FFFF)
			i += 4;
		if (i <= len)
			ft_putwchar(*s++);
	}
	return (i);
}
