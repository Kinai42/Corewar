/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_5_8.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 10:17:27 by dbauduin          #+#    #+#             */
/*   Updated: 2018/09/09 10:19:04 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		check_sub(t_asm *vasm, t_cmd *cmd)
{
	if (cmd->type[0] == T_REG && cmd->type[1] == T_REG && cmd->type[2] == T_REG)
		return ;
	vasm->irror = cmd->inst;
	ft_error(21, vasm);
}

void		check_and(t_asm *vasm, t_cmd *cmd)
{
	if ((cmd->type[0] == T_REG || cmd->type[0] == T_DIR ||
				cmd->type[0] == T_IND) &&
			(cmd->type[1] == T_REG || cmd->type[1] == T_DIR ||
			cmd->type[1] == T_IND) && (cmd->type[2] == T_REG))
		return ;
	vasm->irror = cmd->inst;
	ft_error(21, vasm);
}

void		check_or(t_asm *vasm, t_cmd *cmd)
{
	if ((cmd->type[0] == T_REG || cmd->type[0] == T_DIR ||
				cmd->type[0] == T_IND) &&
			(cmd->type[1] == T_REG || cmd->type[1] == T_DIR ||
			cmd->type[1] == T_IND) && (cmd->type[2] == T_REG))
		return ;
	vasm->irror = cmd->inst;
	ft_error(21, vasm);
}

void		check_xor(t_asm *vasm, t_cmd *cmd)
{
	if ((cmd->type[0] == T_REG || cmd->type[0] == T_DIR ||
				cmd->type[0] == T_IND) &&
			(cmd->type[1] == T_REG || cmd->type[1] == T_DIR ||
			cmd->type[1] == T_IND) && (cmd->type[2] == T_REG))
		return ;
	vasm->irror = cmd->inst;
	ft_error(21, vasm);
}
