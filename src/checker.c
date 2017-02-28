/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgolear <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 15:08:47 by dgolear           #+#    #+#             */
/*   Updated: 2017/02/27 14:41:24 by dgolear          ###   ########.fr       */
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
		exit(ft_printf("ls: %s", strerror(errno)));
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
	options->flags[10].letter = '1';
	options->flags[11].letter = 'S';
	while (i < 12)
		options->flags[i++].sign = 0;
	options->cursize = 0;
	options->maxsize = 10;
	return (options);
}

static int	check_flags(t_option *options, char *str)
{
	int		i;
	int		j;

	i = 1;
	if (str[1] == '\0' || str[0] != '-')
		return (1);
	if (ft_strcmp("--\0", str) == 0)
		return (2);
	while (str[i] != '\0')
	{
		j = 0;
		while (j < 12)
			if (options->flags[j].letter == str[i])
			{
				options->flags[j].sign = 1;
				break ;
			}
			else
				j++;
		if (j == 12)
			exit(ft_printf("ls: illegal option -- %c\nusage: ls [-ABCFGHLOPRST\
UWabcdefghiklmnopqrstuwx1] [file ...]\n"));
		i++;
	}
	return (0);
}

static int	add_dir(t_option *options, char *str)
{
	char		**arr;
	int			i;

	if (options->cursize == options->maxsize)
	{
		i = 0;
		options->maxsize = options->maxsize * 2;
		if ((arr = (char**)malloc(sizeof(char*) * options->maxsize)) == NULL)
			exit(ft_printf("ls: %s", strerror(errno)));
		while (i < options->cursize)
		{
			arr[i] = ft_strdup(options->paths[i]);
			ft_strdel(&options->paths[i++]);
		}
		free(options->paths);
		options->paths = arr;
	}
	options->paths[options->cursize++] = ft_strdup(str);
	return (1);
}

t_option	*check_options(int ac, char **av)
{
	int			i;
	int			flag;
	t_option	*options;

	flag = 0;
	i = 1;
	options = set_default();
	while (i < ac)
	{
		if (!flag)
			flag = check_flags(options, av[i]);
		if (flag == 1)
			flag = add_dir(options, av[i]);
		if (flag == 2)
			flag = 1;
		i++;
	}
	if (options->flags[8].sign)
		options->flags[3].sign = 1;
	if (options->flags[6].sign)
		options->flags[5].sign = 1;
	if (options->cursize == 0)
		options->paths[options->cursize++] = ft_strdup(".");
	return (options);
}
