/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 16:43:44 by dbauduin          #+#    #+#             */
/*   Updated: 2018/11/06 11:17:29 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void    set_proc(t_env *env)
{
    t_proc *proc;
    int     i;

    i = -1;
    env->proc = (t_proc**)ft_parrnew();
    while(++i < env->nb_player)
    {
        proc = (t_proc*)ft_memalloc(sizeof(t_proc));
        init_proc(env->player[i], proc);
        proc->start = i * (MEM_SIZE / env->nb_player);
        proc->pc = proc->start;
        proc->nbr = i + 1;
        ft_parrpush((void***)&env->proc, proc);
    }
}
