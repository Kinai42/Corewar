/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_9_12.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 10:19:37 by dbauduin          #+#    #+#             */
/*   Updated: 2018/09/09 10:20:24 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		check_zjmp(t_asm *vasm, t_cmd *cmd)
{
	if (cmd->type[0] == T_DIR)
		return ;
	vasm->irror = cmd->inst;
	ft_error(21, vasm);
}

void		check_ldi(t_asm *vasm, t_cmd *cmd)
{
	if ((cmd->type[0] == T_REG || cmd->type[0] == T_DIR ||
			cmd->type[0] == T_IND) && (cmd->type[1] == T_REG ||
			cmd->type[1] == T_DIR) && (cmd->type[2] == T_REG))
		return ;
	vasm->irror = cmd->inst;
	ft_error(21, vasm);
}

void		check_sti(t_asm *vasm, t_cmd *cmd)
{
	if ((cmd->type[0] == T_REG) &&
			(cmd->type[1] == T_REG || cmd->type[1] == T_DIR ||
			cmd->type[1] == T_IND) && (cmd->type[2] == T_REG ||
			cmd->type[2] == T_DIR))
		return ;
	vasm->irror = cmd->inst;
	ft_error(21, vasm);
}

void		check_fork(t_asm *vasm, t_cmd *cmd)
{
	if (cmd->type[0] == T_DIR)
		return ;
	vasm->irror = cmd->inst;
	ft_error(21, vasm);
}
