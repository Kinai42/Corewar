/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_comment.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 14:49:00 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/02 14:49:02 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deasm.h"

void	w_comment(uint8_t buffer[BUFF_SIZE], int fd)
{
	int i;

	i = 140;
	write(fd, ".comment \"", 10);
	while (i < 2192 && buffer[i])
		write(fd, &buffer[i++], 1);
	write(fd, "\"\n\n", 3);
}
