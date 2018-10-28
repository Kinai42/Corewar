/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_sti.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 16:19:53 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/26 15:44:16 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	ft_sti(t_env *env, t_proc *proc, int p1, int p2)
{
    int		pc;
    int		i;

    i = 4;
    while (--i >= 0)
    {
        pc = set_pc(p2 + i);
        env->a[MODA((pc))].hex = p1 >> (8 * (i)) & 0xff;
    }
}

void	i_sti(t_proc *processus, t_env *env)
{
	int				*tab;
	unsigned int	p1;
	int				p2;
	int				pc;

    env->op = 11;
	pc = set_pc(processus->pc + 1);
    if ((tab = byte_analysis(&env->a[pc].hex)))
	{
	    pc = set_pc(pc + 1);
        p1 = get_value(env, processus, pc, tab[0]);
		pc = set_pc(pc + 1);
        p2 = get_value(env, processus, pc, tab[1]);
		pc = set_pc(pc + move_pc(tab[1], 11));
        p2 += get_value(env, processus, pc, tab[2]);
		p2 = set_pc(processus->pc + p2);
        ft_sti(env, processus, p1, p2);
		processus->pc = set_pc(pc + move_pc(tab[2], 11));
		free(tab);
	}
	else
		processus->pc = set_pc(processus->pc + 1);
}
