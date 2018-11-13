/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_aff.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 16:23:18 by dbauduin          #+#    #+#             */
/*   Updated: 2018/11/13 01:22:41 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/* ************************************************************************** */
/* The opcode is 16. There is a parameter encoding byte, which is a register, */
/* whose contents are interpreted as the ASCII value of a character to be     */
/* displayed on the standard output. This code is modulo 256.                 */
/* ************************************************************************** */

void	i_aff(t_proc *processus, t_env *env)
{
    t_var   v;
    char    aff;
    int     pc;

    env->op = 16;
    pc = set_pc(processus->pc + 1);
    if (MASK(env->a[MODA(pc)].hex) == 64 &&
            (is_reg_valid(v.p1 = (char)env->a[MODA(pc + 1)].hex)))
    {
        pc = set_pc(pc + 1);
        v.p2 = processus->reg[v.p1 - 1];
        aff = v.p2 % 256;
        if (env->aff == 1)
            ft_print(1, "Player %d aff: %c\n", processus->player->nbr, aff);
        processus->pc = set_pc(pc + 1);
    }
    else
        processus->pc = set_pc(processus->pc + 3);
}
