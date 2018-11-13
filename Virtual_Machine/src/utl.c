/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 15:14:05 by tberthie          #+#    #+#             */
/*   Updated: 2018/11/10 11:30:47 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_player		*get_champ(t_env *env, int number)
{
	int		i;

	i = ft_parrlen((void**)env->player);
	while (i--)
		if (env->player[i]->nbr == number)
			return (env->player[i]);
	return (0);
}

void			hex_dump(unsigned char hex)
{
	ft_putchar(hex < 16 ? '0' : ("0123456789ABCDEF")[hex % 16]);
	hex = hex >= 16 ? hex / 16 : hex;
	ft_putchar(("0123456789ABCDEF")[hex % 16]);
}

unsigned int	rev_int(unsigned int nb)
{
	unsigned int	new;
	unsigned int	bytes;

	new = 0;
	bytes = 4;
	while (bytes)
	{
		bytes--;
		new |= ((nb >> 8 * bytes) & 0xff) << (8 * (3 - bytes));
	}
	return (new);
}

unsigned int	multi_color(unsigned int color, double ratio)
{
	unsigned int new;

	ratio = ratio > 1 ? 1 : ratio;
	new = (unsigned char)((color >> 16 & 0xff) * ratio) << 16;
	new += (unsigned char)((color >> 8 & 0xff) * ratio) << 8;
	new += (unsigned char)(color & 0xff) * ratio;
	return (new);
}
