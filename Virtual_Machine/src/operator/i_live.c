/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_live.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 16:11:25 by dbauduin          #+#    #+#             */
/*   Updated: 2018/11/13 01:29:25 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/* ************************************************************************** */
/* The instruction that allows a process to stay alive. Also has the effect   */
/* of reporting that the player whose number is in parameter is alive.        */
/* No byte encoding parameters, opcode 0x01. Oh, and its only parameter       */
/* is 4 bytes.                                                                */
/* ************************************************************************** */

void	i_live(t_proc *processus, t_env *env)
{
    int         id;
    t_player    *player;

    env->op = 1;
    id = get_value(env, processus, processus->pc + 1, DIR_CODE);
    if ((env->verbose) >> 2 & 1)
        ft_print(1, "P    %d | live %d\n", processus->nbr, id);
    if ((player = get_player(env, id)))
    {
        processus->live += 1;
        env->last_alive = player->nbr;
        if (env->verbose >> 0 & 1)
            ft_print(1, "Player %d (%s) is said to be alive\n", player->nbr, player->name);
    }
    processus->pc = set_pc(processus->pc + 5);
}
