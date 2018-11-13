/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_ldi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 16:18:54 by dbauduin          #+#    #+#             */
/*   Updated: 2018/11/13 01:26:22 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/* ************************************************************************** */
/* ldi, its code is 10. Instead, it will use 2 indexes and 1 registry,        */
/* adding the first two, treating that like an address, reading a value of    */
/* a registry’s size and putting it on the third.                             */
/* ************************************************************************** */

void	i_ldi(t_proc *processus, t_env *env)
{
    t_var                   v;
    int						*tab;
    int						pc;

    env->op = 10;
    pc = set_pc(processus->pc + 1);
    if ((tab = byte_analysis(&env->a[pc].hex)))
    {
        pc = set_pc(pc + 1);
        v.p1 = get_value(env, processus, pc, tab[0]);
        pc = set_pc(pc + move_pc(tab[0], 10));
        v.p2 = get_value(env, processus, pc, tab[1]);
        pc = set_pc(pc + move_pc(tab[1], 10));
        if (!(is_reg_valid(v.p3 = (char)env->a[MODA(pc)].hex)))
            return (return_error(processus, tab));
        v.p4 = processus->pc + ((v.p1 + v.p2) % IDX_MOD);
        v.p5 = MASK(env->a[MODA(v.p4)].hex) << 24 | MASK(env->a[MODA((v.p4 + 1))].hex) << 16 |
            MASK(env->a[MODA((v.p4 + 2))].hex) << 8 | MASK(env->a[MODA((v.p4 + 3))].hex);
        processus->reg[v.p3 - 1] = v.p5;
        if (env->verbose >> 2 & 1)
        {
            ft_print(1, "P   %d | ldi %d %d r%d\n", processus->nbr, v.p1, v.p2, v.p3);
            ft_print(1, "       | -> load from %d + %d = %d (with pc and mod %d)\n", v.p1, v.p2, v.p1 + v.p2, v.p4);
        }
        processus->pc = set_pc(pc + 1);
        free(tab);
    }
    else
        processus->pc = set_pc(processus->pc + 1);
}
