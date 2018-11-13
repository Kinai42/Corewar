/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_sti.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 16:19:53 by dbauduin          #+#    #+#             */
/*   Updated: 2018/11/13 01:35:47 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/* ************************************************************************** */
/* Opcode 11. Takes a register, and two indexes (potentially registers).      */
/* Add the last two, use this sum as an address where the value of the        */
/* first parameter will be copied.                                            */
/* ************************************************************************** */

static void	ft_sti(t_env *env, t_proc *proc, int p1, int p2)
{
    int		pc;
    int		i;

    i = -1;
    while (++i < 4)
    {
        pc = set_pc(p2 + i);
        env->a[MODA(pc)].hex = p1 >> (8 * (3 - i));
        env->a[MODA(pc)].new_color = proc->player->nbr % 6;
    }
}

void	i_sti(t_proc *processus, t_env *env)
{
    int				*tab;
    t_var           v;
    int				pc;

    env->op = 11;
    pc = set_pc(processus->pc + 1);
    if ((tab = byte_analysis(&env->a[pc].hex)))
    {
        pc = set_pc(pc + 1);
        v.p5 = env->a[pc].hex;
        v.p1 = get_value(env, processus, pc, tab[0]);
        pc = set_pc(pc + 1);
        v.p2 = get_value(env, processus, pc, tab[1]);
        pc = set_pc(pc + move_pc(tab[1], 11));
        v.p3 = get_value(env, processus, pc, tab[2]);
        v.p4 = set_pc(processus->pc + v.p2 + v.p3);
        ft_sti(env, processus, v.p1, v.p4);
        processus->pc = set_pc(pc + move_pc(tab[2], 11));
        if (env->verbose >> 2 & 1)
        {
            ft_print(1, "P    %d | sti r%d %d %d\n", processus->nbr, v.p5, 
                    v.p2, v.p3);
            ft_print(1, "       | -> store to %d + %d = %d (with pc and mod %d)\n", 
                    v.p2, v.p3, v.p2 + v.p3, v.p4);
        }
        free(tab);
    }
    else
        processus->pc = set_pc(processus->pc + 1);
}
