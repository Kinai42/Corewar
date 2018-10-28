/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 10:37:54 by dbauduin          #+#    #+#             */
/*   Updated: 2018/09/25 14:57:38 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		print_dir(t_asm *vasm, t_cmd *cmd, int i)
{
	if (cmd->size[i] == 2)
	{
		if (cmd->args[i][1] == LABEL_CHAR)
			two_bytes(label(vasm, vasm->cmd, cmd->args[i]) - cmd->byte_start);
		else
			two_bytes(ft_atoi(&(cmd->args[i][1])));
	}
	else if (cmd->size[i] == 4)
	{
		if (cmd->args[i][1] == LABEL_CHAR)
			four_bytes(label(vasm, vasm->cmd, cmd->args[i]) - cmd->byte_start);
		else
			four_bytes(ft_atoi(&(cmd->args[i][1])));
	}
}

static void		print_arg_oct(t_asm *vasm, t_cmd *cmd, int i)
{
	if (cmd->type[i] == 1)
		ft_print(1, "\t%s\t\t", &(cmd->args[i][1]));
	else if (cmd->type[i] == 2)
		print_dir(vasm, cmd, i);
	else if (cmd->type[i] == 4)
	{
		if (cmd->args[i][0] == LABEL_CHAR)
			two_bytes(label(vasm, vasm->cmd, cmd->args[i]) - cmd->byte_start);
		else
			two_bytes(ft_atoi(cmd->args[i]));
	}
}

static void		print_arg(t_asm *vasm, t_cmd *cmd, int type, char *arg)
{
	if (type == 1)
		ft_print(1, "\t%s\t\t", &arg[1]);
	if (type == 2)
	{
		if (arg[1] == LABEL_CHAR)
			ft_print(1, "\t%d\t\t", (label(vasm, vasm->cmd, arg) -
						cmd->byte_start));
		else
			ft_print(1, "\t%d\t\t", ft_atoi(&arg[1]));
	}
	if (type == 4)
	{
		if (arg[0] == LABEL_CHAR)
			ft_print(1, "\t%d\t\t", (label(vasm, vasm->cmd, arg) -
						cmd->byte_start));
		else
			ft_print(1, "\t%d\t\t", ft_atoi(arg));
	}
}

static void		out_code(t_asm *vasm, t_cmd *cmd)
{
	int a;
	int inst;

	inst = cmd->inst;
	if (inst != 1 && inst != 9 && inst != 12 && inst != 15)
		ft_print(1, "\t\t\t   %d  %d", inst, find_oct(cmd));
	else
		ft_print(1, "\t\t\t   %d\t", inst);
	a = -1;
	while (cmd->args[++a])
		print_arg_oct(vasm, cmd, a);
	write(1, "\n", 1);
	if (inst != 1 && inst != 9 && inst != 12 && inst != 15)
		ft_print(1, "\t\t\t   %d  %d", inst, find_oct(cmd));
	else
		ft_print(1, "\t\t\t   %d\t", inst);
	a = -1;
	while (cmd->args[++a])
		print_arg(vasm, cmd, cmd->type[a], cmd->args[a]);
	write(1, "\n", 1);
}

int				output(t_asm *vasm, t_header header)
{
	int i;
	int a;
	int w;

	i = print_header(vasm, header);
	while (vasm->cmd[++i])
	{
		if (vasm->cmd[i]->label)
			ft_print(1, "\n%d\t\t:\t%s:", vasm->cmd[i]->byte_start,
					vasm->cmd[i]->label);
		if (vasm->cmd[i]->inst > 0 && (a = -1))
		{
			ft_print(1, "\n%d\t(%d)\t:\t   %s\t%s", vasm->cmd[i]->byte_start,
					vasm->cmd[i]->byte_end - vasm->cmd[i]->byte_start,
					g_tab[vasm->cmd[i]->inst].mnemonique,
					vasm->cmd[i]->inst == 15 ? "" : "\t");
			while (vasm->cmd[i]->args[++a] &&
					(w = ft_strlen(vasm->cmd[i]->args[a])))
				ft_print(1, "%s%s%s%s", vasm->cmd[i]->args[a], w < 23 ? "\t" :
						"", w < 17 ? "\t" : "", w < 8 ? "\t" : "");
			write(1, "\n", 1);
			out_code(vasm, vasm->cmd[i]);
		}
	}
	return (1);
}
