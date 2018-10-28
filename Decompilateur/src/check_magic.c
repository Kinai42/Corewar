/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_magic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 14:48:00 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/02 14:48:02 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deasm.h"

int		check_magic(uint8_t t[BUFF_SIZE])
{
	if (t[0] != (unsigned char)0 || t[1] != (unsigned char)234 ||
			t[2] != (unsigned char)131 || t[3] != (unsigned char)243)
		return (0);
	return (1);
}
