/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 12:29:29 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/27 16:59:19 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void init_dump(t_env *env, char *av, int *i, int ac)
{
    int tmp;

    if ((*i + 3) > ac)
        ft_error(11, env);
    *i += 1;
    tmp = ft_atoi(av);
    if (ft_strlen(av) != ft_intlen(tmp))
        ft_error(12, env);
    env->dump = tmp;
    *i += 1;
    return;
}

static void init_visual(t_env *env, int *i, int ac)
{
    *i +=1;
    if (*i >= ac)
        ft_error(11, env);
    env->visual = 1;
    return;
}
void	parse_argv(t_env *env, int ac, char **av)
{
    int	i;

    i = 1;
    if (!ft_strcmp(av[i], "-dump"))
        init_dump(env, av[i + 1], &i, ac);
    else if (!ft_strcmp(av[i], "-visual"))
        init_visual(env, &i, ac);
    env->player = (t_player**)ft_memalloc(sizeof(t_player*));
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
