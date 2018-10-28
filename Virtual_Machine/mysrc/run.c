/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 11:05:10 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/27 17:21:07 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void (*g_func_inst[17])(t_proc *proc, t_env *env) =
{
    0, i_live, i_ld, i_st, i_add, i_sub, i_and, i_or, i_xor, i_zjmp, i_ldi,
    i_sti, i_fork, i_lld, i_lldi, i_lfork, i_aff
};

static void		execute(t_env *env, t_proc *proc)
{
    char		op;

    op = env->a[proc->pc].hex & 0xFF;
    //printf("Player : %d -> EXECUTE OP[%d]\n", proc->player->nbr, op);
    if (!(op > 0 && op < 17) && (proc->pc += 1) == MEM_SIZE)
        proc->pc = 0;
    else if (op > 0 && op < 17)
        (*g_func_inst[(int)op])(proc, env);
}

void			cycles(t_env *env, t_proc *proc)
{
    char		op;

    op = env->a[proc->pc].hex & 0xFF;
    proc->cycle = 1 + 9 * (op == 1 || op == 4 || op == 5 || op == 13) + 4 *
        (op == 2 || op == 3) + 5 * (op == 6 || op == 7 || op == 8) + 19 *
        (op == 9) + 24 * (op == 10 || op == 11) + 799 * (op == 12) + 49 *
        (op == 14) + 999 * (op == 15) + (op == 16);
}

void			process(t_env *env)
{
    int	i;

    i = ft_parrlen((void**)env->proc);
    while (i--)
    {
        if (!(--(env->proc[i]->cycle)))
        {
            //printf("---PROCESS n:%d---\n", i);
            execute(env, env->proc[i]);
            cycles(env, env->proc[i]);
        }
    }
}

void					run(t_env *env)
{
    unsigned int	cycle;

    cycle = 0;
    if (env->visual)
       print_arena(env);
    while (ft_parrlen((void**)env->proc))
    {
        usleep(100);
        process(env);
        if (++env->cycle == env->dump)
            printf("DUMP %d\n", env->cycle);
        if (++cycle >= env->cycle_to_die && (check_live(env) >= NBR_LIVE || env->check < 1))
        {
            env->cycle_to_die -= CYCLE_DELTA > env->cycle_to_die ?
            env->cycle_to_die : CYCLE_DELTA;
            env->check = MAX_CHECKS;
        if (env->visual)
            print_arena(env);
        }
        else
            --env->check;
        cycle = cycle >= env->cycle_to_die ? 0 : cycle;
    }
    /*WINNER*/
    if (!(env->visual))
    {
        int hex = 0;
        int i = 0;
        while (i < MEM_SIZE)
        {
            if ((i) % (64) == 0)
                printf("0x%04x : ", hex);
            if (env->a[i].occupied == 1)
                printf("\033[31m");
            if (env->a[i].occupied == 2)
                printf("\033[32m");
            printf("%02x ", 0xFF & env->a[i].hex);
            if ((i + 1) % (64) == 0)
            {
                printf("\n");
                hex += 64;
            }
            printf("\033[0m");
            i++;
        }
        printf("WIN %s\n", env->player[env->last_alive - 1]->name);
    }
}
