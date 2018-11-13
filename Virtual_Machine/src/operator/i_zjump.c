/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_zjump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 16:21:50 by dbauduin          #+#    #+#             */
/*   Updated: 2018/11/13 01:37:34 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/* ************************************************************************** */
/* The opcode is 9. It will take an index, and jump to that address if        */
/* the carry is 1.                                                            */
/* ************************************************************************** */

void	i_zjmp(t_proc *processus, t_env *env)
{
    int index;
    int pc;

    env->op = 9;
    pc = set_pc(processus->pc + 1);
    index = get_value(env, processus, pc, 2);
    if (processus->carry)
        processus->pc = set_pc(processus->pc + index);
    else
        processus->pc = set_pc(processus->pc + 3);
    if (env->verbose >> 2 & 1)
        ft_print(1, "P    %d | zjmp %d %s\n", processus->nbr, index, processus->carry ? "OK" : "FAILED");
}
