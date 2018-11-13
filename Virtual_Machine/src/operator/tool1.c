/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 16:25:57 by dbauduin          #+#    #+#             */
/*   Updated: 2018/11/13 02:12:34 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		get_dir(t_env *env, int pc, int bytes)
{
    if (bytes == 2)
        return ((short)(MASK(env->a[MODA(pc)].hex) << 8) |
                MASK(env->a[MODA(pc + 1)].hex));
    else
        return ((MASK(env->a[MODA(pc)].hex) << 24) |
                (MASK(env->a[MODA(pc + 1)].hex) << 16) |
                (MASK(env->a[MODA(pc + 2)].hex) << 8) |
                MASK(env->a[MODA(pc + 3)].hex));
}

int		get_ind(t_env *env, int pc)
{
    unsigned short	ret;

    ret = ((MASK(env->a[MODA(pc)].hex) << 8) |
            MASK(env->a[MODA(pc + 1)].hex));
    return ((short)ret);
}

int		set_value(t_env *env, int pc, int op)
{
    int				value;

    if (op == 9 || op == 10 || op == 11 || op == 12 ||
            op == 14 || op == 15)
        value = get_dir(env, pc, 2);
    else
        value = get_dir(env, pc, 4);
    return (value);
}

int		get_value(t_env *env, t_proc *proc, int pc, int opc)
{
    int		value;
    int     r;

    value = 0;
    if (opc == DIR_CODE)
        value = set_value(env, pc, env->op);
    else if (opc == IND_CODE)
        value = get_ind(env, pc);
    else if (opc == REG_CODE && is_reg_valid(r = get_reg(env, pc)))
        value = proc->reg[r];
    return (value);
}
