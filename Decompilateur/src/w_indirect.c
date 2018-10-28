/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_indirect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 14:49:09 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/02 14:49:10 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deasm.h"

int		w_indirect(uint8_t buffer[BUFF_SIZE], int *i)
{
	uint8_t			tab[4];
	short			ret;

	tab[0] = buffer[*i];
	tab[1] = buffer[*i + 1];
	(*i) += 2;
	ret = tab[0] * 256 + tab[1];
	return (ret);
}
