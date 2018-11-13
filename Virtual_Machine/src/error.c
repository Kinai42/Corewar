/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 11:12:51 by dbauduin          #+#    #+#             */
/*   Updated: 2018/11/13 01:14:41 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

# define US1 "Usage:"
# define USEXE env->exe
# define US2 "[-d N -s N -v N | -n] [-a] <champion1.cor> <...>\n"
# define US3 "-a\t: Prints output from \"aff\" (Default is to hide it)\n"
# define US4 "TEXT OUTPUT MODE"
# define US5 "-d N\t: Dumps memory after N cycles then exits\n"
# define US6 "-s N\t: Runs N cycles, dumps memory, pauses, then repeats\n"
# define US7 "-v N\t: Verbosity levels, can be added together to enable several\n"
# define US8 "\t\t- 0 : Show only essentials\n"
# define US9 "\t\t- 1 : Show lives\n"
# define US10 "\t\t- 2 : Show cycles\n"
# define US11 "\t\t- 4 : Show operations (Params are NOT litteral ...)\n"
# define US12 "\t\t- 8 : Show deaths\n"
# define US13 "NCURSES OUTPUT MODE"
# define US14 "-visual\t: Ncurses output mode\n"
# define US20 "-n N\t: Specifies the player's number\n"
# define US15 "---- "
# define US16 " ----------------------------------------------------------\n"
# define US17 " -------------------------------------------------------\n"
# define US18 "----------------------------------------"
# define US19 "----------------------------------------\n"
# define USAGE  US2 US20 US3 US15 US4 US16 US5 US6 US7 US8 US9 US10 US11 US12 US15 
# define USAGE2 US13 US17 US14 US18 US19

void			ft_error(int error, t_env *env)
{
    if (error == 0)
        ft_print(2, "%s %s %s%s", US1, env->exe, USAGE, USAGE2);
    if (error == 1)
        ft_print(2, "Too many champions\n");
    if (error == 2)
        ft_print(2, "Error: File %s is too small to be a champion\n", env->path);
    exit(1);
}
