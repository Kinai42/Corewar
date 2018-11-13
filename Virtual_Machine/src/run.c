/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 11:05:10 by dbauduin          #+#    #+#             */
/*   Updated: 2018/11/13 02:16:27 by dbauduin         ###   ########.fr       */
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
        if (env->proc[i]->dead == 0 && !(--(env->proc[i]->cycle)))
        {
            execute(env, env->proc[i]);
            cycles(env, env->proc[i]);
        }
    }
}

void dump(t_env *env)
{
    int i = 0;
    int hex = 0;

    while (i < MEM_SIZE)
    {
        if ((i) % (64) == 0)
            printf("0x%04x : ", hex);
        if (env->a[i].new_color == 1)
            printf("\033[31m");
        if (env->a[i].new_color == 2)
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
    if (env->dump == env->cycle)
        exit (0);
    else
        ft_gnl(0);
}

int end(t_env *env)
{
    int i;

    i = -1;
    while(env->proc[++i])
        if (env->proc[i]->dead == 0)
            return (1);
    return (0);
}

void					run(t_env *env)
{
    int	cycle;

    cycle = 0;
    if (env->visual)
        init_print(env);
    while(end(env))
    {
        if (++env->cycle == env->dump || 
                (env->sleep > 0 && env->cycle % env->sleep == 0))
            dump(env);
        env->verbose >> 1 & 1 ? ft_print(1, "It is now cycle %d\n", 
                env->cycle) : 0;
        process(env);
        if (++cycle >= env->cycle_to_die &&
                (check_live(env) >= NBR_LIVE || env->check < 1))
        {
            env->cycle_to_die -= CYCLE_DELTA > env->cycle_to_die ? 
                env->cycle_to_die : CYCLE_DELTA;
            (env->verbose) >> 1 & 1 ? ft_print(1, "Cycle to die is now %d\n", 
                    env->cycle_to_die) : 0;
            env->check = MAX_CHECKS;
        }
        else if (cycle >= env->cycle_to_die)
                env->check -= 1;
        if (env->visual)
        {
            print_arena(env);
            print_stats(env, cycle);
        }
        cycle = cycle >= env->cycle_to_die ? 0 : cycle;
    }
    if (!env->visual)
    printf("Contestant %d, \"%s\", has won !\n", 
    env->player[env->last_alive - 1]->nbr, env->player[env->last_alive - 1]->name);
}
