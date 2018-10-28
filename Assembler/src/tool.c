/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 10:55:30 by dbauduin          #+#    #+#             */
/*   Updated: 2018/09/09 10:57:51 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	skip_line(char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (!line[i] || line[i] == COMMENT_CHAR)
		return (1);
	return (0);
}

char	ft_cmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2 && s1++ && s2++)
		;
	return (*s1);
}

int		is_direct_char(int inst, int param_n)
{
	if ((inst == 10 && (param_n == 1 || param_n == 2))
			|| (inst == 11 && (param_n == 2 || param_n == 3))
			|| (inst == 14 && (param_n == 1 || param_n == 2))
			|| (inst == 9 || inst == 12 || inst == 15))
		return (2);
	return (4);
}

int		is_instruction(t_asm *vasm, t_cmd *cmd, char *str)
{
	int		i;
	char	tmp[6];

	i = -1;
	if (!str)
		return (0);
	while (++i < 6 && ft_strchr(LABEL_CHARS, str[i]))
		tmp[i] = str[i];
	vasm->error = str;
	tmp[i] = 0;
	i--;
	while (str[++i])
		if (str[i] != ' ' && str[i] != '\t')
			ft_error(20, vasm);
	i = 0;
	while (++i < 17 && ft_strcmp(g_tab[i].mnemonique, tmp))
		;
	cmd->inst = i;
	if (i != 17 && (vasm->irror = i))
		return (i);
	vasm->error = tmp;
	ft_error(20, vasm);
	return (0);
}

int		ft_arglen(char *str)
{
	int l;

	l = -1;
	while (str[++l] && str[l] != ' ' && str[l] != '\t' &&
			str[l] != SEPARATOR_CHAR)
		;
	return (l);
}
