/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 10:28:46 by dbauduin          #+#    #+#             */
/*   Updated: 2018/09/09 10:36:21 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		is_register(t_asm *vasm, char *arg)
{
	if (*arg == 'r')
	{
		if (arg[1] && (((ft_isdigit(arg[1]) && !arg[2])) ||
					(ft_isdigit(arg[1]) && ft_isdigit(arg[2]) && !arg[3])))
			return (1);
		vasm->error = arg;
		ft_error(21, vasm);
	}
	return (0);
}

static int		is_indirect(t_asm *vasm, char *arg)
{
	int i;

	if (*arg != DIRECT_CHAR && *arg != 'r')
	{
		i = *arg == '-' ? 0 : -1;
		while (ft_isdigit(arg[++i]))
			;
		if (!arg[i] || *arg == LABEL_CHAR)
			return (1);
		vasm->error = arg;
		ft_error(21, vasm);
	}
	return (0);
}

static int		is_direct(t_asm *vasm, char *arg)
{
	if (*arg == DIRECT_CHAR)
	{
		if (ft_isnumber(&arg[1]) || arg[1] == ':')
			return (1);
		vasm->error = arg;
		ft_error(21, vasm);
	}
	return (0);
}

int				is_param_label(char *param)
{
	if (!param)
		return (0);
	if (ft_strlen(param) > 1 && *param == LABEL_CHAR)
		return (1);
	if (ft_strlen(param) > 2 && *param == DIRECT_CHAR && param[1] == LABEL_CHAR)
		return (1);
	return (0);
}

int				get_type_param(t_asm *vasm, t_cmd *cmd)
{
	int i;

	i = -1;
	while (cmd->args[++i])
	{
		if (is_register(vasm, cmd->args[i]))
			cmd->type[i] = T_REG;
		else if (is_direct(vasm, cmd->args[i]))
			cmd->type[i] = T_DIR;
		else if (is_indirect(vasm, cmd->args[i]))
			cmd->type[i] = T_IND;
		if (i >= g_tab[cmd->inst].nbr_args)
		{
			vasm->irror = cmd->inst;
			ft_error(22, vasm);
		}
	}
	cmd->nb_args = i;
	vasm->check_inst[cmd->inst](vasm, cmd);
	return (0);
}
