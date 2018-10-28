/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 10:59:31 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/28 17:04:52 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct		s_asm
{
	char			name;
	char			com;
	int				fd;
	char			*cor;
	char			*exe;
	int				size;
	char			*file_name;
	char			*cor_name;
	int				opt;
	char			**lines;
	int				l;
	char			*error;
	int				irror;
	struct s_cmd	**cmd;
	void			(*check_inst[17])(struct s_asm *, struct s_cmd *);
}					t_asm;

typedef struct		s_cmd
{
	char			*line;
	int				num_line;
	char			*label;
	int				inst;
	char			**args;
	char			type[3];
	int				nb_args;
	int				byte_start;
	int				byte_end;
	char			size[3];
}					t_cmd;

t_header			get_header(t_asm *vasm);
void				ft_error(int error, t_asm *vasm);
void                ft_free(t_asm *vasm);
void				init(t_asm *vasm, t_header *header);
void				init_cmd(t_asm *vasm, t_cmd *cmd);
void				instruction(t_asm *vasm);
void				verif_label(t_asm *vasm, t_cmd **cmd);
void				two_bytes(int offset);
void				four_bytes(int offset);
char				check_file(t_asm *vasm, char **av);
char				ft_cmp(char *s1, char *s2);
char				skip_line(char *line);
int					check_inst(t_asm *vasm, t_cmd *cmd, char **split);
int					check_label(t_asm *vasm, t_cmd *cmd, char *label);
int					ft_arglen(char *str);
int					find_oct(t_cmd *cmd);
int					get_type_param(t_asm *vasm, t_cmd *cmd);
int					is_direct_char(int inst, int param_n);
int					is_instruction(t_asm *vasm, t_cmd *cmd, char *str);
int					is_param_label(char *param);
int					label(t_asm *vasm, t_cmd **cmd, char *label);
int					print_header(t_asm *vasm, t_header header);
int					output(t_asm *vasm, t_header header);
void				check_live(t_asm *vasm, t_cmd *cmd);
void				check_ld(t_asm *vasm, t_cmd *cmd);
void				check_st(t_asm *vasm, t_cmd *cmd);
void				check_add(t_asm *vasm, t_cmd *cmd);
void				check_sub(t_asm *vasm, t_cmd *cmd);
void				check_and(t_asm *vasm, t_cmd *cmd);
void				check_or(t_asm *vasm, t_cmd *cmd);
void				check_xor(t_asm *vasm, t_cmd *cmd);
void				check_zjmp(t_asm *vasm, t_cmd *cmd);
void				check_ldi(t_asm *vasm, t_cmd *cmd);
void				check_sti(t_asm *vasm, t_cmd *cmd);
void				check_fork(t_asm *vasm, t_cmd *cmd);
void				check_lld(t_asm *vasm, t_cmd *cmd);
void				check_lldi(t_asm *vasm, t_cmd *cmd);
void				check_lfork(t_asm *vasm, t_cmd *cmd);
void				check_aff(t_asm *vasm, t_cmd *cmd);
void				check_none(t_asm *vasm, t_cmd *cmd);

int					file_cor(t_asm *s, t_header *t);
int					write_in_cor(int fd, t_asm *s, t_header *h);
int					ft_atoi_bin(char *str);
long long			ft_atoi_max(char *str);
int					is_ocp(int op);
void				write_ocp(int fd, t_asm *s, int i);
uint32_t			big_end(uint32_t val, int size);

#endif
