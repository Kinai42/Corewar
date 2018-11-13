/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 17:03:23 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/20 17:46:21 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

int    swap(t_player *a, t_player *b)
{
    t_player    swap;

    swap = *a;
    *a = *b;
    *b = swap;
    return (-1);
}

void    sort_player(t_player **player)
{
    int a;

    a = -1;
    while(player[(++a) + 1])
    {
        if (player[a]->nbr > player[a + 1]->nbr)
            a = swap(player[a], player[a + 1]);
    }
}
