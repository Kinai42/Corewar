/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 13:52:27 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/26 18:36:33 by dbauduin         ###   ########.fr       */
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
        env->a[k].occupied = env->player[i]->nbr % 6;
        k++;
    }
}

void	build_arena(t_env *env)
{
    int			i;
    int         player;

    i = -1;

    while (++i < env->nb_player)
    {
        put_arena(env, i, (MEM_SIZE / env->nb_player) * i);
        cycles(env, env->proc[i]);
    }

    /*PRINT ARENA SHELL DUMP
      int hex = 0;
      i = 0;
      while (i < MEM_SIZE)
      {
      if (env->a[i].occupied == 1)
      printf("\033[31m");
      if (env->a[i].occupied == 2)
      printf("\033[32m");
      if ((i) % (32) == 0)
      printf("0x%04x : ", hex);
      printf("%02x ", 0xFF & env->a[i].hex);
      if ((i + 1) % (32) == 0)
      {
      printf("\n");
      hex += 32;
      }
      printf("\033[0m");

      i++;
      }*/
}
