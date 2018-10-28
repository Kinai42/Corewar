/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 14:47:51 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/02 14:47:56 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deasm.h"

int		check_instruction(uint8_t buffer[BUFF_SIZE], int tab_fd[3],
														char *argv, char *cor)
{
	if (!w_instructions(buffer, tab_fd[1], tab_fd[2] & FLAG_I, argv))
	{
		remove(cor);
		free(cor);
		return (0);
	}
	return (1);
}
