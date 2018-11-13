/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_fork.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 16:22:39 by dbauduin          #+#    #+#             */
/*   Updated: 2018/11/13 01:25:08 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/* ************************************************************************** */
/* No byte encoding parameters, takes an index, opcode is 12. Creates a new   */
/* process, which inherits the different states of his father, apart from     */
/* his PC, which is set to (PC + (1st parameter% IDX_MOD)).                   */
/* ************************************************************************** */

void	i_fork(t_proc *processus, t_env *env)
{
    t_proc			*process_fils;
    int             pc;
    int             p1;

    env->op = 12;
    process_fils = (t_proc*)malloc(sizeof(t_proc));
    ft_memcpy(process_fils, processus, sizeof(t_proc));
    pc = set_pc(processus->pc + 1);
    p1 = get_value(env, processus, pc, IND_CODE);
    process_fils->pc = set_pc(processus->pc + (p1 % IDX_MOD));
    ft_memcpy(process_fils->reg, processus->reg, 4 * REG_NUMBER); 
    cycles(env, process_fils);
    if (processus->live)
        process_fils->safe = 1;
    process_fils->live = 0;
    ft_parrpush((void***)&env->proc, process_fils);
    process_fils->nbr = ft_parrlen((void**)env->proc);
    processus->pc = set_pc(processus->pc + 3);
        if (env->verbose >> 2 & 1)
    ft_print(1, "P    %d | fork %d (%d)\n", processus->nbr, p1, process_fils->pc);
}
