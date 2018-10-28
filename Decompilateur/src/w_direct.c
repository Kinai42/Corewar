/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_direct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 14:49:04 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/02 14:49:06 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deasm.h"

int		w_direct(uint8_t buffer[BUFF_SIZE], int *i)
{
	uint8_t		tab[4];
	int			ret;

	tab[0] = buffer[*i];
	tab[1] = buffer[*i + 1];
	tab[2] = buffer[*i + 2];
	tab[3] = buffer[*i + 3];
	*i += 4;
	ret = tab[0] * 16777216 + tab[1] * 65536 + tab[2] * 256 + tab[3];
	return (ret);
}
