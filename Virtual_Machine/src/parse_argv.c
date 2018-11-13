/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 12:29:29 by dbauduin          #+#    #+#             */
/*   Updated: 2018/11/13 02:15:35 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void init_option(t_env *env, char **av, int *i, int ac)
{
    int     tmp;
    char    a;

    a = av[*i][1];
    if ((a != 'a' && (*i + 3) > ac) || (a == 'a' && (*i + 2) > ac))
        ft_error(0, env);
    tmp = ft_atoi(av[*i + 1]);
    if (a != 'a')
    {
        if ((int)ft_strlen(av[*i + 1]) != ft_intlen(tmp))
            ft_error(0, env);
        if (a == 'd' && (*i += 2))
            env->dump = tmp;
        else if (a == 'v' && (*i += 2))
            env->verbose = tmp;
        else if (a == 's' && (*i += 2))
            env->sleep = tmp;
    }
    if (a == 'a' && (*i +=1))
        env->aff = 1;
    if (!ft_strcmp(av[*i], "-d") || !ft_strcmp(av[*i], "-v") ||
            !ft_strcmp(av[*i], "-s") || !ft_strcmp(av[*i], "-a"))
        init_option(env, av, i, ac);
    return;
}

static void init_visual(t_env *env, int *i, int ac)
{
    *i +=1;
    if (*i >= ac)
        ft_error(11, env);
    env->visual = 1;
    env->dump = 0;
    env->verbose = 0;
    return;
}

void	parse_argv(t_env *env, int ac, char **av)
{
    int	i;

    i = 1;
    if (!ft_strcmp(av[i], "-d") || !ft_strcmp(av[i], "-v") ||
            !ft_strcmp(av[i], "-s") || !ft_strcmp(av[i], "-a"))
        init_option(env, av, &i, ac);
    if (!ft_strcmp(av[i], "-visual"))
        init_visual(env, &i, ac);
    env->player = (t_player**)ft_memalloc(sizeof(t_player*));
    if (i >= ac)
        ft_error(0, env);
    while (i < ac)
    {
        if (!ft_strcmp(av[i], "-n"))
            add_player_n(env, av, ac, &i);
        else
            add_player(env, av[i]);
        env->nb_player++;
        i++;
    }
}
