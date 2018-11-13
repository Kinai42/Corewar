/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 14:14:19 by dbauduin          #+#    #+#             */
/*   Updated: 2018/11/13 02:16:52 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "libft.h"
# include "op.h"
# include <ncurses.h>
# include <curses.h>
# include <stdio.h>
# include <limits.h>
#include <fcntl.h>

# define MODS(x)	(x % 32768 < 0 ? x % 32768 + 32768 : x % 32768)
# define MODA(x)	(x % MEM_SIZE < 0 ? x % MEM_SIZE + MEM_SIZE : x % MEM_SIZE)
# define MODAI(x)	(x % MEM_SIZE)
# define MODX(x)	(x % IDX_MOD)
# define MM(x)		(x & 0xFF)
# define MASK(x)	(x & 0xFF)

typedef struct		s_arena
{
    char	hex;
    int		new_color;
    int     before_color;
}					t_arena;

typedef struct		s_player
{
    int		        nbr;

    char	        *name;
    char	        *comment;
    int		        size;
    char	        content[CHAMP_MAX_SIZE + 1];

    int             total;
    int             period;


}					t_player;

typedef struct      s_var
{
    int p1;
    int p2;
    int p3;
    int p4;
    int p5;
}                   t_var;




typedef struct      s_proc
{
    t_player	    *player;
    int             nbr;

    int		        start;

    unsigned int	reg[REG_NUMBER];
    int				pc;
    char			carry;

    int		        live;
    int             safe;
    int             cycle;
    char            dead;
}                   t_proc;





typedef struct		s_env
{
    char        *exe;
    char        *path;

    int			nb_player;

    t_player	**player;
    t_arena		a[MEM_SIZE];
    t_proc      **proc;

    int			visual;
    int			dump;
    char        verbose;
    char        aff;
    int         sleep;        

    int         cycle;

    int			cycle_to_die;
    int			lives;
    int         check;

    int			last_alive;
    int			winner;


    char		arena[MEM_SIZE];
    int         n;
    int         op;
    t_op		op_tab[17];

    WINDOW      *arene;
    WINDOW      *stats;
    WINDOW      *cmd;
    unsigned int speed;

}					t_env;

void			setup(t_env *env, int ac, char **av);
void        	init_env(t_env *env, char **av);
void            init_proc(t_player *player, t_proc *proc);
void        	init_player(t_env *env, t_player *player, t_header *header);
void        	parse_argv(t_env *env, int ac, char **av);
unsigned int	rev_int(unsigned int nb);
int             check_cor(char *path);
//void          set_number(env, env->player);
void            ft_error(int error, t_env *env);
void			add_player(t_env *env, char *path);
void            add_player_n(t_env *env, char **av, int ac, int *i);
void        	build_arena(t_env *env);
void        	set_op_tab(t_env *env);
t_player        *get_champ(t_env *env, int number);
int	    		find_player(t_player **players, int n);
void            run(t_env *env);
unsigned int    check_live(t_env *env);
void            get_cycle(t_env *env, t_proc *proc);
void           	execute_cycle(t_env *env, t_player *player);


int	        	is_reg_valid(int i);
int	        	get_reg(t_env *env, int pc);
void        	return_error(t_proc *processus, int *tab);
int	        	get_dir(t_env *env, int pc, int bytes);
int	        	set_value(t_env *env, int pc, int op);
int	        	get_value(t_env *env, t_proc *proc, int pc, int opc);
t_player		*get_player(t_env *env, int id);
int         	set_pc(int tmp);
int	           	*byte_analysis(char *opc);
int         	carry(t_proc *processus, int p);
int	           	move_pc(int tab, int op);
void            init_print(t_env *env);
void            print_arena(t_env *env);
void            print_stats(t_env *env, int cycle);


void				i_live(t_proc *processus, t_env *env);
void	            i_ld(t_proc *processus, t_env *env);
void				i_ldi(t_proc *processus, t_env *env);
void				i_st(t_proc *processus, t_env *env);
void				i_add(t_proc *processus, t_env *env);
void				i_sub(t_proc *processus, t_env *env);
void				i_and(t_proc *processus, t_env *env);
void				i_or(t_proc *processus, t_env *env);
void				i_xor(t_proc *processus, t_env *env);
void				i_zjmp(t_proc *processus, t_env *env);
void				i_ldi(t_proc *processus, t_env *env);
void				i_sti(t_proc *processus, t_env *env);
void				i_fork(t_proc *processus, t_env *env);
void				i_lld(t_proc *processus, t_env *env);
void				i_lldi(t_proc *processus, t_env *env);
void				i_lfork(t_proc *processus, t_env *env);
void				i_aff(t_proc *processus, t_env *env);

void                sort_player(t_player **player);
void                set_proc(t_env *env);
void                cycles(t_env *env, t_proc *proc);





#endif
