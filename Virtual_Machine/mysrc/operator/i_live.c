/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_live.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 16:11:25 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/26 13:24:36 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	i_live(t_proc *processus, t_env *env)
{
    int         id;
    t_player    *player;

    env->op = 1;
    id = get_dir(env, processus->pc + 1, 4);
	if ((player = get_player(env, id)))
	{
		player->live++;
        processus->life = 1;
		env->last_alive = player->nbr;
	}
	processus->pc = set_pc(processus->pc + 5);
}
