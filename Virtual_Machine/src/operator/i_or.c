/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_or.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 16:16:18 by dbauduin          #+#    #+#             */
/*   Updated: 2018/11/13 01:33:08 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"


/* ************************************************************************** */
/* This operation is a bit-to-bit OR, following the same principle as and,    */
/* its opcode is 7.                                                           */
/* ************************************************************************** */

void	i_or(t_proc *processus, t_env *env)
{
    t_var   v;
    int		*tab;
    int		pc;

    env->op = 7;
    pc = set_pc(processus->pc + 1);
    if ((tab = byte_analysis(&env->a[pc].hex)))
    {
        pc = set_pc(pc + 1);
        v.p1 = get_value(env, processus, pc, tab[0]);
        pc = set_pc(pc + move_pc(tab[0], env->op));
        v.p2 = get_value(env, processus, pc, tab[1]);
        pc = set_pc(pc + move_pc(tab[1], env->op));
        if (!(is_reg_valid(v.p3 = env->a[MODA(pc)].hex)))
			return (return_error(processus, tab));
        processus->reg[v.p3 - 1] = v.p1 | v.p2;
        if (env->verbose >> 2 & 1)
            ft_print(1, "P    %d | or %d %d r%d\n", processus->nbr, v.p1, v.p2, v.p3);
        carry(processus, v.p1 | v.p2);
        processus->pc = set_pc(pc + 1);
        free(tab);
    }
    else
        processus->pc = set_pc(processus->pc + 1);
}
