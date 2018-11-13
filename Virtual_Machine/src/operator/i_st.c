/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_st.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 16:21:21 by dbauduin          #+#    #+#             */
/*   Updated: 2018/11/13 01:34:07 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/* ************************************************************************** */
/* Take a registry and a registry or an indirect and store the value of the   */
/* registry toward a second argument. Its opcode is 0x03. For example, st r1, */
/* 42 store the value of r1 at the address (PC + (42 % IDX_MOD))              */
/* ************************************************************************** */

static void	ft_ri(t_env *env, t_proc *proc, int p1, int p2)
{
    int		pc;
    int		i;

    i = -1;
    while (++i < 4)
    {
        pc = proc->pc + p2 + i;
        env->a[MODA(pc)].hex = (p1 >> (8 * (3 - i))) & 0xff;
    }
}

void	i_st(t_proc *processus, t_env *env)
{
    t_var           v;
    int				*tab;
    int             pc;

    env->op = 3;
    pc = set_pc(processus->pc + 1);
    if ((tab = byte_analysis(&env->a[pc].hex)))
    {
        pc = set_pc(pc + 1);
        v.p1 = get_value(env, processus, pc, tab[0]);
        v.p3 = env->a[pc].hex;
        pc = set_pc(pc + move_pc(tab[0], env->op));
        if (tab[1] == 1 && carry(processus, v.p1))
        {
            v.p2 = env->a[MODA(pc)].hex - 1;
            processus->reg[v.p2] = v.p1;
        }
        else if (tab[1] == 3)
        {
            v.p2 = get_value(env, processus, pc, tab[1]);
            ft_ri(env, processus, v.p1, MODX(v.p2));
        }
        if (env->verbose >> 2 & 1)
            ft_print(1, "P    %d | st r%d %d\n", processus->nbr, v.p3, v.p2);
        processus->pc = set_pc(pc + (tab[1] == 3 ? 2 : 1));
        free(tab);
    }
    else
        processus->pc = set_pc(pc + 1);
}
