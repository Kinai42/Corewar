/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_live.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 11:44:53 by dbauduin          #+#    #+#             */
/*   Updated: 2018/11/13 01:14:16 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

unsigned int			check_live(t_env *env)
{
    unsigned int	total;
    unsigned int	i;
    t_proc			*proc;

    total = 0;
    i = 0;
    while (i < ft_parrlen((void**)env->proc))
    {
        proc = env->proc[i];
        if (!proc->dead && !proc->live && !proc->safe)
        {
            proc->dead = 1;
            if (env->verbose >> 8 & 1)
                printf("Process %d hasn't lived for %d cycles (CTD %D)\n", 
                        proc->nbr, proc->live, env->cycle_to_die);
        }
        else
        {
            total += proc->live;
            proc->live = 0;
            proc->safe = 0;
        }
        i++;
    }
    return (total);
}
