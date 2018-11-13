/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:24:08 by dbauduin          #+#    #+#             */
/*   Updated: 2018/11/12 18:53:11 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			main(int ac, char **av)
{
	t_env   env;

    env.exe = *av;
	if (ac == 1)
		ft_error(0, &env);
	setup(&env, ac, av);
    build_arena(&env);
	run(&env);
    if (env.visual == 1)
    {
        mvwprintw(env.stats, 50, 5, "The winner is :");
        wattron(env.stats, COLOR_PAIR(env.player[env.last_alive - 1]->nbr % 6));
        mvwprintw(env.stats, 50, 15, " %s", env.player[env.last_alive - 1]->name);
        wattroff(env.stats, COLOR_PAIR(env.player[env.last_alive - 1]->nbr % 6));
        refresh();
		getch();
		endwin();
    }
	return (0);
}
