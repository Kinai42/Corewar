/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 10:21:05 by dbauduin          #+#    #+#             */
/*   Updated: 2018/09/30 10:52:31 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		is_separator(t_asm *vasm, char *str)
{
	int i;
	int k;

	if (!(i = 0) && (str[i] == DIRECT_CHAR || str[i] == LABEL_CHAR))
		i = str[i] == DIRECT_CHAR && str[i + 1] == LABEL_CHAR ? 2 : 1;
	i += str[i] == '-' ? 0 : -1;
	while (str[++i] && ft_strchr(LABEL_CHARS, str[i]))
		;
	i == 0 ? ft_error(40, vasm) : 0;
	if (str[i] == LABEL_CHAR)
	{
		while (str[++i] == ' ' || str[i] == '\t' || str[i] == LABEL_CHAR)
			;
		return (i);
	}
	while ((str[i] == ' ' || str[i] == '\t') && (i++))
		;
	k = str[i] == SEPARATOR_CHAR ? i + 1 : i;
	if (str[i] == SEPARATOR_CHAR)
	{
		while (str[++i] == ' ' || str[i] == '\t')
			;
		str[i] == COMMENT_CHAR || !str[i] ? ft_error(41, vasm) : 0;
	}
	return (k);
}

static int		get_cmd(t_asm *vasm, t_cmd *cmd, char **split, int size)
{
	int c;

	init_cmd(vasm, cmd);
	c = 0;
	cmd->byte_start = size;
	if (c == 0 && ft_strchr(split[c], LABEL_CHAR))
		c += check_label(vasm, cmd, split[c]);
	if (split[c] && is_instruction(vasm, cmd, split[c]) >= 0)
		size += check_inst(vasm, cmd, &split[c]);
	cmd->byte_end = size;
	ft_parrfree((void**)split);
	return (size);
}

static char		**get_split(t_asm *vasm, char *line)
{
	int		begin;
	char	**split;
	int		c;

	c = 0;
	split = (char**)ft_parrnew();
	while (line[c] && line[c] != COMMENT_CHAR)
	{
		while (line[c] && (line[c] == ' ' || line[c] == '\t'))
			c++;
		begin = c;
		if (line[c] && line[c] != COMMENT_CHAR)
			c += is_separator(vasm, &line[c]);
		ft_parrpush((void***)&split, ft_strndup(&line[begin], c - begin));
	}
	return (split);
}

void			instruction(t_asm *vasm)
{
	t_cmd	*cmd;
	char	**split;

	vasm->l -= 1;
	vasm->cmd = (t_cmd**)ft_parrnew();
	while (vasm->lines[++vasm->l])
	{
		if (skip_line(vasm->lines[vasm->l]))
			continue ;
		split = get_split(vasm, vasm->lines[vasm->l]);
		cmd = (t_cmd*)(ft_memalloc(sizeof(t_cmd)));
		ft_parrpush((void***)&vasm->cmd, cmd);
		vasm->size = get_cmd(vasm, cmd, split, vasm->size);
	}
}
