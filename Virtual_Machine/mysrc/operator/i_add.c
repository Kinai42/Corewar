/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_add.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 16:20:14 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/26 13:23:00 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/* ************************************************************************** */
/* Instructions: Opcode 4. Take three registries, add the first two, and      */
/* place the result in the third, right before modifying the carry.           */
/* ************************************************************************** */

void	i_add(t_proc *processus, t_env *env)
{
	int		index;
	int		p1;
	int		p2;
	int		*tab;
	int		pc;

	pc = set_pc(processus->pc + 1);
    env->op = 4;
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
		processus->reg[index - 1] = p1 + p2;
		carry(processus, p1 + p2);
		processus->pc = set_pc(pc + 1);
		free(tab);
	}
	else
		processus->pc = set_pc(processus->pc + 1);
}
