/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_ld.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 16:18:00 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/26 16:17:28 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
 ** Instructions:
 ** Take a random argument and a registry. Load the value of the first argument
 ** in the registry. Its opcode is 10 in binary and it will change the carry.
 */

void	i_ld(t_proc *processus, t_env *env)
{
    int		p1;
    int		index;
    int		*tab;
    int		pc;

    env->op = 2;
    pc = set_pc(processus->pc + 1);
    if ((tab = byte_analysis(&env->a[pc].hex)))
    {
        pc = set_pc(pc + 1);
        p1 = get_value(env, processus, pc, tab[0]);
        pc = set_pc(pc + move_pc(tab[0], 2));
        p1 = MODX(p1);
        if (!(is_reg_valid(index = (char)env->a[MODA(pc)].hex)))
            return (return_error(processus, tab));
        processus->reg[index - 1] = p1;
        carry(processus, p1);
        processus->pc = set_pc(pc + 1);
        free(tab);
    }
    else
        processus->pc = set_pc(processus->pc + 1);
}
