/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 10:10:05 by dbauduin          #+#    #+#             */
/*   Updated: 2018/09/09 11:35:47 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		init_check_inst(t_asm *vasm)
{
	vasm->check_inst[0] = 0;
	vasm->check_inst[1] = &check_live;
	vasm->check_inst[2] = &check_ld;
	vasm->check_inst[3] = &check_st;
	vasm->check_inst[4] = &check_add;
	vasm->check_inst[5] = &check_sub;
	vasm->check_inst[6] = &check_and;
	vasm->check_inst[7] = &check_or;
	vasm->check_inst[8] = &check_xor;
	vasm->check_inst[9] = &check_zjmp;
	vasm->check_inst[10] = &check_ldi;
	vasm->check_inst[11] = &check_sti;
	vasm->check_inst[12] = &check_fork;
	vasm->check_inst[13] = &check_lld;
	vasm->check_inst[14] = &check_lldi;
	vasm->check_inst[15] = &check_lfork;
	vasm->check_inst[16] = &check_aff;
}

void			init(t_asm *vasm, t_header *header)
{
	vasm->name = 0;
	vasm->com = 0;
	vasm->l = -1;
	vasm->size = 0;
	ft_bzero(header, sizeof(t_header));
	ft_bzero((void*)(header->prog_name), NAME_LENGTH + 1);
	ft_bzero((void*)(header->comment), COMMENT_LENGTH + 1);
	init_check_inst(vasm);
}

void			init_cmd(t_asm *vasm, t_cmd *cmd)
{
	cmd->line = vasm->lines[vasm->l];
	cmd->num_line = vasm->l;
	cmd->label = NULL;
	cmd->inst = 0;
	cmd->args = (char**)ft_parrnew();
	cmd->type[0] = 0;
	cmd->type[1] = 0;
	cmd->type[2] = 0;
	cmd->nb_args = 0;
	cmd->size[0] = 0;
	cmd->size[1] = 0;
	cmd->size[2] = 0;
	cmd->byte_start = 0;
	cmd->byte_end = 0;
}
