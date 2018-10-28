/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_13_16.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 10:16:50 by dbauduin          #+#    #+#             */
/*   Updated: 2018/09/09 10:17:12 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		check_lld(t_asm *vasm, t_cmd *cmd)
{
	if ((cmd->type[0] == T_DIR || cmd->type[0] == T_IND) &&
			(cmd->type[1] == T_REG))
		return ;
	vasm->irror = cmd->inst;
	ft_error(21, vasm);
}

void		check_lldi(t_asm *vasm, t_cmd *cmd)
{
	if ((cmd->type[0] == T_REG || cmd->type[0] == T_DIR ||
				cmd->type[0] == T_IND) &&
			(cmd->type[1] == T_REG || cmd->type[1] == T_DIR) &&
			(cmd->type[2] == T_REG))
		return ;
	vasm->irror = cmd->inst;
	ft_error(21, vasm);
}

void		check_lfork(t_asm *vasm, t_cmd *cmd)
{
	if (cmd->type[0] == T_DIR)
		return ;
	vasm->irror = cmd->inst;
	ft_error(21, vasm);
}

void		check_aff(t_asm *vasm, t_cmd *cmd)
{
	if (cmd->type[0] == T_REG)
		return ;
	vasm->irror = cmd->inst;
	ft_error(21, vasm);
}
