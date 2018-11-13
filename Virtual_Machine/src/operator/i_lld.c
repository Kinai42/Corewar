/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_lld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 16:18:26 by dbauduin          #+#    #+#             */
/*   Updated: 2018/11/13 02:04:19 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/* ************************************************************************** */
/* Means long-load, so its opcode is 13. It's the same as ld, but without%    */
/* IDX_MOD. Modify the carry.                                                 */
/* ************************************************************************** */

void	i_lld(t_proc *processus, t_env *env)
{
    t_var   v;
    int		*tab;
    int		pc;

    env->op = 13;
    pc = set_pc(processus->pc + 1);
    if ((tab = byte_analysis(&env->a[pc].hex)))
    {
        pc = set_pc(pc + 1);
        v.p1 = get_value(env, processus, pc, tab[0]);
        pc = set_pc(pc + move_pc(tab[0], 2));
        if (!(is_reg_valid(v.p2 = (char)env->a[MODA(pc)].hex)))
            return (return_error(processus, tab));
        processus->reg[v.p2 - 1] = v.p1;
        carry(processus, v.p1);
        if (env->verbose >> 2 & 1)
            ft_print(1, "P    %d | lld %d r%d\n", processus->nbr, v.p1, v.p2);
        processus->pc = set_pc(pc + 1);
        free(tab);
    }
    else
        processus->pc = set_pc(processus->pc + 1);
}
