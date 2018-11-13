/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 13:52:27 by dbauduin          #+#    #+#             */
/*   Updated: 2018/11/13 02:09:29 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	put_arena(t_env *env, int i, int k)
{
    int	count;

    count = -1;
    while (++count < env->player[i]->size)
    {
        env->a[k].hex = env->player[i]->content[count] & 0xFF;
        env->a[k].before_color = i + 1;
        env->a[k].new_color = i + 1;
        k++;
    }
}

void	build_arena(t_env *env)
{
    int			i;

    i = -1;
    while (++i < env->nb_player)
    {
        put_arena(env, i, (MEM_SIZE / env->nb_player) * i);
        cycles(env, env->proc[i]);
    }
}
