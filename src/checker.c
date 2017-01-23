/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 15:08:47 by dgolear           #+#    #+#             */
/*   Updated: 2017/01/23 19:23:22 by dgolear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_option	*set_default(void)
{
	int			i;
	t_option	*options;

	i = 0;
	if ((options = (t_option*)malloc(sizeof(t_option))) == NULL
		|| (options->paths = (char **)malloc(sizeof(char *) * 10)) == NULL)
	{
		ft_printf("ft_ls: %s", strerror(errno));
		exit (-1);
	}
	options->flags[0].letter = 'R';
	options->flags[1].letter = 'r';
	options->flags[2].letter = 'G';
	options->flags[3].letter = 'l';
	options->flags[4].letter = 't';
	options->flags[5].letter = 'a';
	options->flags[6].letter = 'f';
	options->flags[7].letter = 'u';
	options->flags[8].letter = 'g';
	options->flags[9].letter = 'd';
	while (i < 10)
		options->flags[i++].sign = 0;
	options->cursize = 0;
	options->maxsize = 10;
	return (options);
}

void		check_flags(t_option *options, char *str)
{
	int		i;
	int		j;

	i = 0;
	if (!str[++i])
	{
	ft_printf("ft_ls: -: No such file or directory\n");
	exit (-1);
	}
	while (str[i])
	{
		j = 0;
		while (j < 10)
		{
			if (options->flags[j].letter == str[i])
			{
				options->flags[j].sign = 1;
				break;
			}
			j++;
		}
		if (j == 10)
		{
			ft_printf("ls: illegal option -- %c\nusage: \
					ls [-RrGltafugd] [file ...]", str[i]);
			exit(-1);
		}
		i++;
	}
}

void	add_dir(t_option *options, char *str)
{
	if (options->cursize == options->maxsize)
	{
		options->maxsize = options->maxsize * options->maxsize;

	}
	options->paths[options->cursize] = str;
	options->cursize++;
}

t_option	*check_options(int ac, char **av)
{
	int		i;
	t_option	*options;

	i = 1;
	options = set_default();
	if (ac == 1)
		return (options);
	else
		while (i < ac)
		{
			if (av[i][0] == '-')
				check_flags(options, av[i]);
			else
				add_dir(options, av[i]);
			i++;
		}
	return (options);
}
