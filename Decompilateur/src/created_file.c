/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   created_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 14:48:06 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/02 14:48:08 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deasm.h"

void		created_file(char *argv, char **cor)
{
	char *tmp;

	tmp = ft_strndup(argv, ft_strlen(argv) - 4);
	*cor = ft_strjoin(tmp, "_deasm.s");
	free(tmp);
}
