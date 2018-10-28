/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:24:08 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/27 17:18:41 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			main(int ac, char **av)
{
	t_env   env;

	if (ac == 1)
		ft_error(0, &env);
	setup(&env, ac, av);
    build_arena(&env);
	run(&env);
    if (env.visual == 1)
    {
        refresh();
		getch();
		endwin();
    }
	return (0);
}
