/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_1-4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 10:14:02 by dbauduin          #+#    #+#             */
/*   Updated: 2018/09/20 09:50:32 by imhaimou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		check_live(t_asm *vasm, t_cmd *cmd)
{
	if (cmd->type[0] == T_DIR)
		return ;
	vasm->irror = cmd->inst;
	ft_error(21, vasm);
}

void		check_ld(t_asm *vasm, t_cmd *cmd)
{
	if ((cmd->type[0] == T_DIR || cmd->type[0] == T_IND) &&
			(cmd->type[1] == T_REG))
		return ;
	vasm->irror = cmd->inst;
	ft_error(21, vasm);
}

void		check_st(t_asm *vasm, t_cmd *cmd)
{
	if (cmd->type[0] == T_REG && (cmd->type[1] == T_IND \
			|| cmd->type[1] == T_REG))
		return ;
	vasm->irror = cmd->inst;
	ft_error(21, vasm);
}

void		check_add(t_asm *vasm, t_cmd *cmd)
{
	if (cmd->type[0] == T_REG && cmd->type[1] == T_REG && cmd->type[2] == T_REG)
		return ;
	vasm->irror = cmd->inst;
	ft_error(21, vasm);
}
