/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 14:35:14 by dbauduin          #+#    #+#             */
/*   Updated: 2018/09/20 09:47:23 by imhaimou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		ft_read_nam_com(t_asm *v, char *name, int a)
{
	char		*line;
	int			i;
	int			max;

	i = -1;
	max = a == 1 ? NAME_LENGTH : COMMENT_LENGTH;
	ft_print(1, "You didn’t specify a %s, add one :  \n", a == 1 ? "name" :
			"comment");
	line = ft_gnl(0);
	while (line && line[++i])
	{
		if (i == max)
			ft_error(8 - a, v);
		name[i] = line[i];
	}
	free(line);
	if (i <= 0)
		ft_error(2, v);
	name[i] = '\0';
}

static int		put_name(t_asm *v, char *name, int c, int a)
{
	int			k;

	k = 0;
	while (v->lines[v->l][++c] == ' ' || v->lines[v->l][c] == '\t')
		;
	c += a == 1 ? (ft_strlen(NAME_STRING)) : (ft_strlen(COMMENT_STRING));
	while (v->lines[v->l][++c] != '"')
		if (v->lines[v->l][c] != ' ' && v->lines[v->l][c] != '\t')
			ft_error(3 - a, v);
	while (v->lines[v->l] && v->lines[v->l][++c] != '"')
	{
		if ((a == 1 && k == NAME_LENGTH) || (a == 0 && k == COMMENT_LENGTH))
			ft_error(8 - a, v);
		if (!v->lines[v->l][c] && (c = -1) && ((v->l) += 1))
			name[k++] = '\n';
		else if (v->lines[v->l] && v->lines[v->l][c])
			name[k++] = v->lines[v->l][c];
		else
			ft_error((6 - a), v);
	}
	v->lines[v->l] ? 0 : ft_error(3 - a, v);
	k == 0 ? ft_read_nam_com(v, name, a) : 0;
	return (c);
}

static void		ft_prog_name(t_asm *v, char *name, int a)
{
	int			c;

	c = -1;
	if ((a == 1 && v->name == 2) || (a == 0 && v->com == 2))
		ft_error(3 - a, v);
	c = put_name(v, name, c, a);
	while (v->lines[v->l][++c] && v->lines[v->l][c] != COMMENT_CHAR)
		if (v->lines[v->l][c] != ' ' && v->lines[v->l][c] != '\t')
			ft_error(3 - a, v);
}

t_header		get_header(t_asm *v)
{
	t_header	header;
	int			c;

	init(v, &header);
	while (v->lines[++(v->l)])
	{
		c = -1;
		while (v->lines[v->l][++c] == ' ' || v->lines[v->l][c] == '\t')
			;
		if (!ft_cmp(NAME_STRING, &v->lines[v->l][c]) && (v->name += 1))
			ft_prog_name(v, (char *)(header.prog_name), 1);
		else if (!ft_cmp(COMMENT_STRING, &v->lines[v->l][c]) && (v->com += 1))
			ft_prog_name(v, (char *)(header.comment), 0);
		else if (v->lines[v->l][c] == COMMENT_CHAR || !(v->lines[v->l][c]))
			continue ;
		else
			break ;
	}
	!v->name ? ft_error(2, v) : 0;
	!v->com ? ft_error(3, v) : 0;
	!(v->lines[v->l]) ? ft_error(4, v) : 0;
	return (header);
}
