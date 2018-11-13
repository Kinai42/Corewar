/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 12:17:53 by dbauduin          #+#    #+#             */
/*   Updated: 2018/11/13 02:10:12 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void set_number(t_player **player)
{
    int i;
    int n;

    i = -1;
    while (player[++i] && !(n = 0))
        while (++n && player[i]->nbr == 0)
            if (!find_player(player, n))
                player[i]->nbr = n;
}

void			setup(t_env *env, int ac, char **av)
{
    int i;

    init_env(env, av);
    parse_argv(env, ac, av);
    if (!ft_parrlen((void**)env->player))
        ft_error(0, env);
    set_number(env->player);
    sort_player(env->player);
    set_proc(env);
    i = -1;
    ft_print(1, "Introducing contestants...\n");
    while (++i < env->nb_player)
        ft_print(1, "* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",\
                env->player[i]->nbr, env->player[i]->size, 
                env->player[i]->name, env->player[i]->comment);
}
