/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_aff.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 16:23:18 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/26 17:13:40 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"


void	i_aff(t_proc *processus, t_env *env)
{
    char    aff;
    int     pc;
	int		value;
    int     p1;

    env->op = 16;
	pc = set_pc(processus->pc + 1);
	if (ZMASK(env->a[MODA(pc)].hex) == 64 &&
        (is_reg_valid(p1 = (char)env->a[MODA(pc + 1)].hex)))
	{
        pc = set_pc(pc + 1);
        value = processus->reg[p1 - 1];
        aff = value % 256;
		ft_print(1, "player %s display: %c\n", processus->player->name, aff);
		processus->pc = set_pc(pc + 1);
	}
	else
		processus->pc = set_pc(processus->pc + 1);
}
