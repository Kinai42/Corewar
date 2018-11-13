/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_lfork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 16:22:57 by dbauduin          #+#    #+#             */
/*   Updated: 2018/11/13 01:27:56 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/* ************************************************************************** */
/* Opcode is 15. Same as a fork without modulo to the address.                */
/* ************************************************************************** */

void	i_lfork(t_proc *processus, t_env *env)
{
    t_proc			*process_fils;
    int             pc;
    int             p1;

    env->op = 15;
    process_fils = (t_proc*)malloc(sizeof(t_proc));
    ft_memcpy(process_fils, processus, sizeof(t_proc));
    pc = set_pc(processus->pc + 1);
    p1 = get_value(env, processus, pc, IND_CODE);
    process_fils->pc = set_pc(processus->pc + p1);
    ft_memcpy(process_fils->reg, processus->reg, 4 * REG_NUMBER);
    cycles(env, process_fils);
    if (processus->live)
        process_fils->safe = 1;
    ft_parrpush((void***)&env->proc, process_fils);
    processus->pc = set_pc(processus->pc + 3);
    if (env->verbose >> 2 & 1)
        ft_print(1, "P    %d | lfork %d (%d)\n", processus->nbr, p1, process_fils->pc);
}
