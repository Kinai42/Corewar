/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_or.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 16:16:18 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/26 13:24:51 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Instructions: Apply an | (bit-to-bit or) over the first two arguments
** or store the result in a registry, which is the third argument.
** Opcode 0x06. Modifies the carry.
** T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG
*/

void	i_or(t_proc *processus, t_env *env)
{
    int		p1;
    int		p2;
    int		*tab;
    char	index;
    int		pc;

    env->op = 7;
    pc = set_pc(processus->pc + 1);
    if ((tab = byte_analysis(&env->a[pc].hex)))
    {
        pc = set_pc(pc + 1);
        p1 = get_value(env, processus, pc, tab[0]);
        pc = set_pc(pc + move_pc(tab[0], 6));
        p2 = get_value(env, processus, pc, tab[1]);
        pc = set_pc(pc + move_pc(tab[1], 6));
        if (!(is_reg_valid(index = (char)env->a[MODA(pc)].hex)))
			return (return_error(processus, tab));
        processus->reg[(int)index - 1] = p1 | p2;
        carry(processus, p1 | p2);
        processus->pc = set_pc(pc + 1);
        free(tab);
    }
    else
        processus->pc = set_pc(processus->pc + 1);
}
