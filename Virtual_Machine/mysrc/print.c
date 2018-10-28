/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 14:57:48 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/27 17:09:08 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*void	print_stats(t_env *e)
{
	int i;

	i = -1;
	while (++i < env->player_amount)
		ft_print_lives(e, i);
	attron(COLOR_PAIR(14));
	printw("\n\nCycle: %-10d Cursors: %-10d Total Number of lives: %d/%-10d \
	Checks: %d/9 > Decrease cycle to die with: %d     \
	Cycles to die: %d/%d\n\n", env->tot_cycle, env->cursors, NBR_LIVE, env->lives, \
	env->check, CYCLE_DELTA, env->cycles_to_die, env->cycle);
	attroff(COLOR_PAIR(14));
	refresh();
}*/


static void init_visual(t_env *env)
{
    initscr();
	noecho();
	start_color();
	init_color(COLOR_WHITE, 220, 220, 220);
	init_pair(0, COLOR_YELLOW, COLOR_BLACK);
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(3, COLOR_CYAN, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	init_pair(5, COLOR_GREEN, COLOR_BLACK);
	init_pair(6, COLOR_YELLOW, COLOR_BLACK);
	init_pair(7, COLOR_BLACK, COLOR_BLUE);
	init_pair(8, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(9, COLOR_BLACK, COLOR_CYAN);
	init_pair(10, COLOR_BLACK, COLOR_RED);
	init_pair(11, COLOR_BLACK, COLOR_GREEN);
	init_pair(12, COLOR_WHITE, COLOR_BLACK);
	init_pair(13, COLOR_BLACK, COLOR_GREEN);
	init_pair(14, COLOR_GREEN, COLOR_BLACK);
	curs_set(FALSE);
    return;
}

void	print_arena(t_env *env)
{
    init_visual(env);
    int i;

	i = 0;
	erase();
	while (i < MEM_SIZE)
	{
		attron(COLOR_PAIR(env->a[i].occupied));
		printw("%02x", 0xFF & env->a[i].hex);
		attroff(COLOR_PAIR(env->a[i].occupied));
		printw(" ");
		if ((i + 1) % (128 / 2) == 0)
			printw("\n");
		i++;
	}
	refresh();
}
