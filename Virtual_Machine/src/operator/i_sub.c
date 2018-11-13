/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_sub.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 16:20:47 by dbauduin          #+#    #+#             */
/*   Updated: 2018/11/13 02:04:04 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/* ************************************************************************** */
/* ** Instructions: Same as add, but with the opcode est 0b101 (5 in decimal) */
/* ** and uses a substraction                                                 */
/* ************************************************************************** */

void	i_sub(t_proc *processus, t_env *env)
{
    t_var   v;
    int		*tab;
    int		pc;

    env->op = 5;
    pc = set_pc(processus->pc + 1);
    if ((tab = byte_analysis(&env->a[pc].hex)))
    {
        pc = set_pc(pc + 1);
        if (!(is_reg_valid(v.p1 = (char)env->a[MODA(pc)].hex)))
            return (return_error(processus, tab));
        v.p4 = processus->reg[v.p1 - 1];
        pc = set_pc(pc + 1);
        if (!(is_reg_valid(v.p2 = (char)env->a[MODA(pc)].hex)))
            return (return_error(processus, tab));
        v.p5 = processus->reg[v.p2 - 1];
        pc = set_pc(pc + 1);
        if (!(is_reg_valid(v.p3 = (char)env->a[MODA(pc)].hex)))
            return (return_error(processus, tab));
        processus->reg[v.p3 - 1] = v.p4 - v.p5;
        carry(processus, v.p4 - v.p5);
        if (env->verbose >> 2 & 1)
            ft_print(1, "P    %d | sub r%d r%d r%d\n", processus->nbr, v.p1, v.p2, v.p3);
        processus->pc = set_pc(pc + 1);
        free(tab);
    }
    else
        processus->pc = set_pc(processus->pc + 5);
}
