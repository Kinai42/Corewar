/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_name.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 14:49:19 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/02 14:49:21 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deasm.h"

void	w_name(uint8_t buffer[BUFF_SIZE], int fd)
{
	int		i;

	i = 4;
	write(fd, ".name \"", 7);
	while (i < 132 && buffer[i])
		write(fd, &buffer[i++], 1);
	write(fd, "\"\n", 2);
}
