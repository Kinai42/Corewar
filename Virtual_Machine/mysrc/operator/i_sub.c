/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_sub.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 16:20:47 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/26 13:25:06 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/* ************************************************************************** */
/* ** Instructions: Same as add, but with the opcode est 0b101 (5 in decimal) */
/* ** and uses a substraction                                                 */
/* ************************************************************************** */

void	i_sub(t_proc *processus, t_env *env)
{
	int		index;
	int		p1;
	int		p2;
	int		*tab;
	int		pc;

    env->op = 5;
	pc = set_pc(processus->pc + 1);
    if ((tab = byte_analysis(&env->a[pc].hex)))
	{
        pc = set_pc(pc + 1);
		if (!(is_reg_valid(index = (char)env->a[MODA(pc)].hex)))
			return (return_error(processus, tab));
		p1 = processus->reg[index - 1];
		pc = set_pc(pc + 1);
		if (!(is_reg_valid(index = (char)env->a[MODA(pc)].hex)))
			return (return_error(processus, tab));
		p2 = processus->reg[index - 1];
		pc = set_pc(pc + 1);
		if (!(is_reg_valid(index = (char)env->a[MODA(pc)].hex)))
			return (return_error(processus, tab));
		processus->reg[index - 1] = p1 - p2;
		carry(processus, p1 - p2);
		processus->pc = set_pc(pc + 1);
		free(tab);
	}
	else
		processus->pc = set_pc(processus->pc + 1);
}
