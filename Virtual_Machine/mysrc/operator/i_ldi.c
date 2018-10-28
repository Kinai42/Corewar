/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_ldi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 16:18:54 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/26 13:24:16 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/* ************************************************************************** */
/* ** ldi, its code is 0x0a. Instead, it will use 2 indexes and 1 registry,   */
/* ** adding the first two, treating that like an address, reading a value of */
/* ** a registry’s size and putting it on the third.                          */
/* ************************************************************************** */

void	i_ldi(t_proc *processus, t_env *env)
{
    int						*tab;
    int						p1;
    int						value;
    int						pc;

    env->op = 10;
    pc = set_pc(processus->pc + 1);
    if ((tab = byte_analysis(&env->a[pc].hex)))
    {
        pc = set_pc(pc + 1);
        p1 = get_value(env, processus, pc, tab[0]);
        pc = set_pc(pc + move_pc(tab[0], 10));
        p1 += get_value(env, processus, pc, tab[1]);
        value = (int)env->a[processus->pc + (p1 % IDX_MOD)].hex;
        pc = set_pc(pc + move_pc(tab[1], 10));
        if (!(is_reg_valid(p1 = (char)env->a[MODA(pc)].hex)))
            return (return_error(processus, tab));
        processus->reg[p1 - 1] = value;
        processus->pc = set_pc(pc + 1);
        free(tab);
    }
    else
        processus->pc = set_pc(processus->pc + 1);
}

