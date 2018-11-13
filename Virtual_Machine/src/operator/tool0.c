/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 18:40:12 by dbauduin          #+#    #+#             */
/*   Updated: 2018/11/13 02:11:12 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		is_reg_valid(int i)
{
	return (i >= 0 && i <= REG_NUMBER);
}

int		get_reg(t_env *env, int pc)
{
	return ((char)env->a[MODA(pc)].hex - 1);
}

void	return_error(t_proc *processus, int *tab)
{
	processus->pc = set_pc(processus->pc + 1);
	free(tab);
}
