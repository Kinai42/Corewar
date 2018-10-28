/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_xor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 16:16:44 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/26 13:25:13 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Instructions: Acts like and with an exclusive OR. As you will have guessed,
** its opcode in octal is 10.
*/

void	i_xor(t_proc *processus, t_env *env)
{
    int		p1;
    int		p2;
    int		*tab;
    char	index;
    int		pc;

    env->op = 8;
    pc = set_pc(processus->pc + 1);
    if ((tab = byte_analysis(&env->a[pc].hex)))
    {
        pc = set_pc(pc + 1);
        p1 = get_value(env, processus, pc, tab[0]);
        pc = set_pc(pc + move_pc(tab[0], 6));
        p2 = get_value(env, processus, pc, tab[1]);
        pc = set_pc(pc + move_pc(tab[1], 6));
        if (!(is_reg_valid(index = (char)env->a[MODA(pc)].hex)))
			return (return_error(processus, tab));
        processus->reg[(int)index - 1] = p1 ^ p2;
        carry(processus, p1 ^ p2);
        processus->pc = set_pc(pc + 1);
        free(tab);
    }
    else
        processus->pc = set_pc(processus->pc + 1);
}
