/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_zjump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 16:21:50 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/26 17:30:33 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	i_zjmp(t_proc *processus, t_env *env)
{
    int index;
    int pc;

    env->op = 9;
    if (processus->carry)
    {
        pc = set_pc(processus->pc + 2);
        index = MODX(env->a[pc].hex);
        processus->pc = set_pc(processus->pc + index);
    }
    else
        processus->pc = set_pc(processus->pc + 3);
}
