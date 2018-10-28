/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 09:52:17 by dbauduin          #+#    #+#             */
/*   Updated: 2018/09/09 09:54:23 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		label(t_asm *vasm, t_cmd **cmd, char *label)
{
	int i;
	int c;

	i = -1;
	c = *label == LABEL_CHAR ? 1 : 2;
	while (cmd[++i])
	{
		if (cmd[i]->label && !ft_strcmp(cmd[i]->label, &label[c]))
			return (cmd[i]->byte_start);
	}
	(vasm->error) = label;
	c == 2 ? ft_error(11, vasm) : ft_error(12, vasm);
	return (-1);
}

void	verif_label(t_asm *vasm, t_cmd **cmd)
{
	int i;
	int j;

	i = -1;
	while (cmd[++i])
	{
		j = -1;
		while (cmd[i]->args[++j])
			if (is_param_label(cmd[i]->args[j]) && (vasm->l = cmd[i]->num_line))
				label(vasm, cmd, cmd[i]->args[j]);
	}
}

int		check_label(t_asm *vasm, t_cmd *cmd, char *label)
{
	int i;
	int s;

	i = -1;
	s = ft_strlen(label);
	while (label[++i] != LABEL_CHAR && ft_strchr(LABEL_CHARS, label[i]))
		;
	while (label[--s] == ' ' || label[s] == '\t')
		;
	if (i != s && (vasm->error = label))
		ft_error(10, vasm);
	label[i] = 0;
	cmd->label = ft_strdup(label);
	return (1);
}

int		check_inst(t_asm *vasm, t_cmd *cmd, char **split)
{
	int size;
	int n;
	int i;

	i = 0;
	size = 0;
	while (split[++i] && (++(cmd->nb_args)))
	{
		n = ft_arglen(split[i]);
		ft_parrpush((void ***)&cmd->args, ft_strndup(split[i], n));
		if (*split[i] == 'r')
			cmd->size[i - 1] = 1;
		else if (*split[i] != DIRECT_CHAR)
			cmd->size[i - 1] = 2;
		else if (*split[i] == DIRECT_CHAR)
			cmd->size[i - 1] = is_direct_char(cmd->inst, cmd->nb_args);
		size += (int)cmd->size[i - 1];
	}
	get_type_param(vasm, cmd);
	if (cmd->inst == 1)
		return (size + 1);
	if (cmd->inst == 9 || cmd->inst == 12 || cmd->inst == 15)
		return (size + 1);
	return (size + 2);
}
