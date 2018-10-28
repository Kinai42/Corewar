/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_live.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 11:44:53 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/26 18:33:50 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void				remove_proc(t_env *env, t_proc *proc)
{
	ft_parrprem((void**)env->proc, proc);
	free(proc);
}

unsigned int			check_live(t_env *env)
{
	unsigned int	total;
	unsigned int	i;
	t_proc			*proc;

	total = 0;
	i = -1;
	while (++i < ft_parrlen((void**)env->proc))
	{
		proc = env->proc[i];
		if (!proc->player->live && !proc->safe)
			remove_proc(env, proc);
		else
		{
			total += proc->player->live;
			proc->player->live = 0;
			proc->safe = 0;
		}
	}
	return (total);
}
