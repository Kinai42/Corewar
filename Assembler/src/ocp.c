/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 17:31:23 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/27 17:31:25 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		ft_ncpy(char *dst, const char *src, int n, int begin)
{
	int			i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dst[begin + i] = src[i];
		i++;
	}
	while (i < n)
	{
		dst[begin + i] = '\0';
		i++;
	}
	return (n);
}

int				is_ocp(int op)
{
	if (op == 1 || op == 9 || op == 12 || op == 15)
		return (0);
	return (1);
}

void			write_ocp(int fd, t_asm *s, int i)
{
	static char	params[8];
	int			p;
	int			j;
	int			val;

	p = 0;
	j = 0;
	while (j < s->cmd[i]->nb_args)
	{
		if (s->cmd[i]->args[j][0] == 'r')
			p += ft_ncpy(params, "01", 2, p);
		if (s->cmd[i]->args[j][0] == DIRECT_CHAR)
			p += ft_ncpy(params, "10", 2, p);
		else if (ft_isdigit(s->cmd[i]->args[j][0]))
			p += ft_ncpy(params, "11", 2, p);
		j++;
	}
	while (p < 8)
		params[p++] = '0';
	val = ft_atoi_bin(params);
	write(fd, &val, 1);
}
