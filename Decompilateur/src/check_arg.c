/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 14:47:43 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/27 18:14:37 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deasm.h"

static int			check_bin(char *argv)
{
	int len;

	len = ft_strlen(argv);
	if (len > 4 && argv[len - 1] == 'r' && argv[len - 2] == 'o' &&
			argv[len - 3] == 'c' && argv[len - 4] == '.')
		return (1);
	ft_print(2, "Error : expected a .cor file\n");
	return (0);
}

int					check_arg(int argc, char **argv, int *opt, int *k)
{
	int		i;

	*opt = 0;
	i = 1;
	while (argv[i] && (!ft_strcmp(argv[i], "-v") || !ft_strcmp(argv[i], "-i"))
			&& i <= 2)
	{
		if (argv[i][0] == '-' && argv[i][1] == 'v' && !argv[i][2])
			*opt = (*opt | FLAG_V);
		else
			*opt = (*opt | FLAG_I);
		i++;
	}
	if (i == argc)
	{
		ft_print(2, "Usage : %s [option] [file.cor ...]\n", argv[0]);
		ft_print(2, "Options :\n\t-v : Verbose mode\n\t-i :");
		ft_print(2, " Write address of instructions in file file_deasm.s\n");
		return (0);
	}
	*k = i - 1;
	while (argv[i])
		if (!check_bin(argv[i++]) || argc == 1)
			return (0);
	return (1);
}
