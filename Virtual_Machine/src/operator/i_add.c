/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_add.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 16:20:14 by dbauduin          #+#    #+#             */
/*   Updated: 2018/11/13 01:21:48 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/* ************************************************************************** */
/* Instructions: Opcode 4. Take three registries, add the first two, and      */
/* place the result in the third, right before modifying the carry.           */
/* ************************************************************************** */

void	i_add(t_proc *processus, t_env *env)
{
    t_var   v;
    int		*tab;
    int		pc;

    pc = set_pc(processus->pc + 1);
    env->op = 4;
    if ((tab = byte_analysis(&env->a[pc].hex)))
    {
        pc = set_pc(pc + 1);
        if (!(is_reg_valid(v.p1 = (char)env->a[MODA(pc)].hex)))
            return (return_error(processus, tab));
        v.p2 = processus->reg[v.p1 - 1];
        pc = set_pc(pc + 1);
        if (!(is_reg_valid(v.p3 = (char)env->a[MODA(pc)].hex)))
            return (return_error(processus, tab));
        v.p4 = processus->reg[v.p3 - 1];
        pc = set_pc(pc + 1);
        if (!(is_reg_valid(v.p5 = (char)env->a[MODA(pc)].hex)))
            return (return_error(processus, tab));
        processus->reg[v.p5 - 1] = v.p2 + v.p4;
        carry(processus, v.p2 + v.p4);
        if (env->verbose >> 2 & 1)
            ft_print(1, "P %d | add r%d r%d r%d\n", processus->nbr, 
                    v.p1, v.p3, v.p5);
        processus->pc = set_pc(pc + 1);
        free(tab);
    }
    else
        processus->pc = set_pc(processus->pc + 5);
}
