/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 14:57:48 by dbauduin          #+#    #+#             */
/*   Updated: 2018/11/13 01:16:45 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void init_print(t_env *env)
{
    initscr();
    if (LINES < 70 || COLS < 198)
    {
        printw("Terminal is too small !\n");
        printw("Press any key to exit\n");
        getch();
        endwin();
        ft_error(0, env);
    }
    env->arene = subwin(stdscr, 66, 196 , 0, 0);
    env->stats = subwin(stdscr, 69, 64, 0, 197);
    env->cmd = subwin(stdscr, 3, 196, 66, 0);
    box(env->arene, ACS_VLINE, ACS_HLINE);
    box(env->stats, ACS_VLINE, ACS_HLINE);
    box(env->cmd, ACS_VLINE, ACS_HLINE);
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_YELLOW);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_BLACK, COLOR_BLUE);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);
    init_pair(8, COLOR_BLACK, COLOR_CYAN);
    init_pair(5, COLOR_RED, COLOR_BLACK);
    init_pair(10, COLOR_BLACK, COLOR_RED);
    init_pair(6, COLOR_GREEN, COLOR_BLACK);
    init_pair(12, COLOR_BLACK, COLOR_GREEN);
    init_pair(13, COLOR_WHITE, COLOR_BLACK);
    curs_set(FALSE);
    noecho();
    wrefresh(env->cmd);
    print_arena(env);
    print_stats(env, 0);
}

void	print_arena(t_env *env)
{
    int i;
    int c;
    int l;
    int color;

    i = 0;
    c = 2;
    l = 1;
    while (i < MEM_SIZE)
    {
        wattron(env->arene, COLOR_PAIR(env->a[i].new_color));
        mvwprintw(env->arene, l, c, "%02x", 0xFF & env->a[i].hex);
        wattroff(env->arene, COLOR_PAIR(color = env->a[i].new_color));
        c += 2;
        mvwprintw(env->arene, l, c += 1, " ");
        if ((i + 1) % (128 / 2) == 0 && (c = 2))
            l++;
        env->a[i].before_color = env->a[i].new_color;
        i++;
    }
    wrefresh(env->arene);
}

void        print_stats(t_env *env, int cycle)
{
    int i;

    werase(env->stats);
    box(env->stats, ACS_VLINE, ACS_HLINE);
    mvwprintw(env->stats, 1, 3, "** %s **", "RUNNING");
    mvwprintw(env->stats, 3, 3, "Cycles/second limit : %d/second", env->speed);

    mvwprintw(env->stats, 5, 3, "Cycle: %-10d", env->cycle);
    mvwprintw(env->stats, 7, 3, "Process: %d", ft_parrlen((void**)env->proc));

    i = -1;
    while (env->player[++i])
    {
        mvwprintw(env->stats, 9 + i * 4, 3, "Player -%d :", env->player[0]->nbr);
        wattron(env->stats, COLOR_PAIR(i + 1));
        mvwprintw(env->stats, 9 + i * 4, 16, " %s", env->player[i]->name);
        wattroff(env->stats, COLOR_PAIR(i + 1));
        mvwprintw(env->stats, 10 + i * 4, 3, "Last Live : %-10d", env->last_alive);
        mvwprintw(env->stats, 11 + i * 4, 3, "Lives in current period : %-10d", env->lives);
    }
    i = i * 3;
    mvwprintw(env->stats, 13 + i, 3, "CYCLE TO DIE : %d (%d)", env->cycle_to_die, cycle);
    mvwprintw(env->stats, 15 + i, 3, "CYCLE DELTA: %d", CYCLE_DELTA);
    mvwprintw(env->stats, 17 + i, 3, "NBR LIVE: %d", NBR_LIVE);
    mvwprintw(env->stats, 19 + i, 3, "MAX CHECKS: %d", MAX_CHECKS);
    wrefresh(env->stats);
}
