/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_lldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 16:19:15 by dbauduin          #+#    #+#             */
/*   Updated: 2018/11/13 02:04:38 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"


/* ************************************************************************** */
/* Opcode 0x0e. Same as ldi, but does not apply any modulo to the addresses.  */
/* Change, however, the carry.                                                */
/* ************************************************************************** */

void	i_lldi(t_proc *processus, t_env *env)
{
    int						*tab;
    t_var                   v;
    int						pc;

    env->op = 14;
    pc = set_pc(processus->pc + 1);
    if ((tab = byte_analysis(&env->a[pc].hex)))
    {
        pc = set_pc(pc + 1);
        v.p1 = get_value(env, processus, pc, tab[0]);
        pc = set_pc(pc + move_pc(tab[0], 10));
        v.p2 = get_value(env, processus, pc, tab[1]);
        v.p4 = processus->pc + v.p1 + v.p2;
        v.p4 = (int)env->a[v.p4].hex;
        pc = set_pc(pc + move_pc(tab[1], 10));
        if (!(is_reg_valid(v.p3 = (char)env->a[MODA(pc)].hex)))
            return (return_error(processus, tab));
        processus->reg[v.p3 - 1] = v.p4;
        carry(processus, processus->reg[v.p3 - 1]);
        if (env->verbose >> 2 & 1)
        {
            ft_print(1, "P    %d | lldi %d %d r%d\n", processus->nbr, v.p1, v.p2, v.p3);
            ft_print(1, "        | -> load from %d + %d = %d (with pc %d)\n", v.p1, v.p2, v.p4, processus->pc);
        }
        processus->pc = set_pc(pc + 1);
        free(tab);
    }
    else
        processus->pc = set_pc(processus->pc + 1);
}
