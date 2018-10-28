/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 18:12:24 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/28 17:19:05 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	init_arena(t_env *env)
{
    int i;

    i = 0;
    while (i < MEM_SIZE)
    {
        env->a[i].hex = 0;
        env->a[i].occupied = 13;
        i++;
    }
}

void	    init_env(t_env *env, char **av)
{
    env->exe = *av;
    env->cycle = 0;
    env->lives = 0;
    env->visual = 0;
    env->dump = -1;
    env->winner = 0;
    env->check = 0;
    env->tot_cycle = 0;
    env->cycle_to_die = CYCLE_TO_DIE;
    init_arena(env);
    set_op_tab(env);
}

void	    init_player(t_env *env, t_player *player, t_header *header, void *data)
{
    if (ft_strlen(header->prog_name) > NAME_LENGTH || ft_strlen(header->comment) > COMMENT_LENGTH)
        ft_error(0, env);
    player->name = ft_strdup(header->prog_name);
    player->comment = ft_strdup(header->comment);
    player->size = rev_int(header->prog_size);
    if (env->n > 0 && !find_player(env->player, env->n))
        player->nbr = env->n;
    else
        player->nbr = 0;
}

void        init_proc(t_player *player, t_proc *proc)
{
    proc->player = player;
    proc->carry = 0;
    proc->cycle = 0;
    proc->running = 0;
    proc->life = 0;
}
