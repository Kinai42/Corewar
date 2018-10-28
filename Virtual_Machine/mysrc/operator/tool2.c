/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 16:30:54 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/25 15:22:14 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_player		*get_player(t_env *env, int id)
{
    int i;

    i = -1;
    while (++i < env->nb_player)
        if (env->player[i]->nbr == id)
            return (env->player[i]);
    return (0);
}

int	set_pc(int tmp)
{
    if (tmp > MEM_SIZE - 1)
        tmp = tmp % MEM_SIZE;
    if (tmp < 0)
        tmp = MEM_SIZE + tmp % -MEM_SIZE;
    return (tmp);
}

int		*byte_analysis(char *opc)
{
    int				*nbr;
    unsigned char   byte;

    byte = *(unsigned char*)opc;
    nbr = (int*)malloc(sizeof(int) * 3);
    nbr[0] = (byte >> 6) & (REG_CODE | DIR_CODE | IND_CODE);
    nbr[1] = (byte >> 4) & (REG_CODE | DIR_CODE | IND_CODE);
    nbr[2] = (byte >> 2) & (REG_CODE | DIR_CODE | IND_CODE);
    if ((1 <= nbr[0] && nbr[0] <= 3) && (1 <= nbr[1] && nbr[1] <= 3))
        return (nbr);
    free(nbr);
    return (NULL);
}

int	carry(t_proc *processus, int p)
{
    if (p == 0)
        processus->carry = 1;
    else
        processus->carry = 0;
    return (1);
}

int		move_pc(int tab, int op)
{
    if (tab == 1)
        return (1);
    else if (tab == 2 && !(op == 9 || op == 10 || op == 11 || op == 12 ||
                op == 14 || op == 15))
        return (4);
    else
        return (2);
}
