/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_and.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 16:15:46 by dbauduin          #+#    #+#             */
/*   Updated: 2018/11/13 01:23:06 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/* ************************************************************************** */
/* Instructions: Apply an & (bit-to-bit AND) over the first two arguments     */
/* and store the result in a registry, which is the third argument.           */
/* Opcode 0x06. Modifies the carry.                                           */
/* ************************************************************************** */

void	i_and(t_proc *processus, t_env *env)
{
    t_var   v;
    int		*tab;
    int		pc;

    env->op = 6;
    pc = set_pc(processus->pc + 1);
    if ((tab = byte_analysis(&env->a[pc].hex)))
    {
        pc = set_pc(pc + 1);
        v.p1 = get_value(env, processus, pc, tab[0]);
        pc = set_pc(pc + move_pc(tab[0], env->op));
        v.p2 = get_value(env, processus, pc, tab[1]);
        pc = set_pc(pc + move_pc(tab[1], env->op));
        if (!(is_reg_valid(v.p3 = (char)env->a[MODA(pc)].hex)))
            return (return_error(processus, tab));
        processus->reg[(int)v.p3 - 1] = v.p1 & v.p2;
        carry(processus, v.p1 & v.p2);
        if (env->verbose >> 2 & 1)
            ft_print(1, "P    %d | and %d %d r%d\n", processus->nbr, v.p1, v.p2, v.p3);
        processus->pc = set_pc(pc + 1);
        free(tab);
    }
    else
        processus->pc = set_pc(processus->pc + 1);
}


