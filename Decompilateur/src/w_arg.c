/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_arg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 14:48:57 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/02 14:48:58 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deasm.h"

static void			check(int nb[3], uint8_t buffer[BUFF_SIZE], int fd)
{
	if (is_direct_char(nb[2], nb[3] + 1) == 4)
		ft_printc(fd, "\%%d", w_direct(buffer, &nb[0]));
	else
		ft_printc(fd, "\%%d", w_indirect(buffer, &nb[0]));
}

void				w_arg(uint8_t tab[3], int nb[4], uint8_t buffer[BUFF_SIZE],
		int fd)
{
	if (tab[nb[3]] == REGISTER)
		ft_printc(fd, "r%c", buffer[nb[0]++]);
	else if (tab[nb[3]] == DIRECT)
		check(nb, buffer, fd);
	else if (tab[nb[3]] == INDIRECT)
		ft_printc(fd, "%d", w_indirect(buffer, &nb[0]));
}
