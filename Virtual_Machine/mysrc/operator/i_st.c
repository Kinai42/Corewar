/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_st.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 16:21:21 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/26 16:16:49 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
 ** Instructions:
 ** Take a registry and a registry or an indirect and store the value of the
 ** registry toward a second argument. Its opcode is 0x03. For example, st r1, 42
 ** store the value of r1 at the address (PC + (42 % IDX_MOD))
 */

static void	ft_ri(t_env *env, t_proc *proc, int p1, int p2)
{
    int		pc;
    int		i;

    i = 4;
    while (--i >= 0)
    {
        pc = proc->pc + p2 + i;
        env->a[MODA((pc))].hex = (proc->reg[p1] >> (8 * (i))) & 0xff;
    }
}

void	i_st(t_proc *processus, t_env *env)
{
    int				p1;
    int             p2;
    int				*tab;
    int             pc;

    env->op = 3;
    pc = set_pc(processus->pc + 1);
    if ((tab = byte_analysis(&env->a[pc].hex)))
    {
        pc = set_pc(pc + 1);
        p1 = get_value(env, processus, pc, tab[0]);
        pc = set_pc(pc + move_pc(tab[0], 3));
        if (tab[1] == 1 && carry(processus, p1))
            processus->reg[env->a[MODA(pc)].hex - 1] = p1;
        else if (tab[1] == 3)
        {
            p2 = get_value(env, processus, pc, tab[1]);
            ft_ri(env, processus, p1 - 1, MODX(p2));
        }
        processus->pc = set_pc(pc + (tab[1] == 3 ? 2 : 1));
        free(tab);
    }
    else
        processus->pc = set_pc(pc + 1);
}
