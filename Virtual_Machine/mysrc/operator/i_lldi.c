/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_lldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 16:19:15 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/26 13:24:47 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int		value_lldi(t_env *env, int r)
{
    unsigned int	value;

    value = (ZMASK(env->a[MODA(r)].hex) << 24) |
        (ZMASK(env->a[MODA((r + 1))].hex) << 16) |
        (ZMASK(env->a[MODA((r + 2))].hex) << 8) |
        ZMASK(env->a[MODA((r + 3))].hex);
    return ((int)value);
}

void	i_lldi(t_proc *processus, t_env *env)
{
    int						*tab;
    int						p1;
    int						value;
    int						pc;

    env->op = 14;
    pc = set_pc(processus->pc + 1);
    if ((tab = byte_analysis(&env->a[pc].hex)))
    {
        pc = set_pc(pc + 1);
        p1 = get_value(env, processus, pc, tab[0]);
        pc = set_pc(pc + move_pc(tab[0], 10));
        p1 += get_value(env, processus, pc, tab[1]);
        value = (int)env->a[processus->pc + p1].hex;
        pc = set_pc(pc + move_pc(tab[1], 10));
        if (!(is_reg_valid(p1 = (char)env->a[MODA(pc)].hex)))
            return (return_error(processus, tab));
        processus->reg[p1 - 1] = value;
        carry(processus, p1);
        processus->pc = set_pc(pc + 1);
        free(tab);
    }
    else
        processus->pc = set_pc(processus->pc + 1);
}
