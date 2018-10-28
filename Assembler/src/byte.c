/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byte.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 09:51:40 by dbauduin          #+#    #+#             */
/*   Updated: 2018/09/20 09:28:36 by imhaimou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		find_oct(t_cmd *cmd)
{
	int	i;
	int	oct;

	i = -1;
	oct = 0;
	while (cmd->args[++i] && (oct *= 4) > -1)
	{
		if (cmd->type[i] == 1)
			oct += 1;
		else if (cmd->type[i] == 2)
			oct += 2;
		else if (cmd->type[i] == 4)
			oct += 3;
	}
	while (i++ < 4)
		oct *= 4;
	return (oct);
}

void	four_bytes(int offset)
{
	int	ret;
	int	len;

	len = 3;
	ret = (offset >> 24) & 0x000000ff;
	ft_print(1, "\t%d ", ret);
	len += ft_intlen(ret);
	ret = (offset >> 16) & 0x000000ff;
	ft_print(1, "%d ", ret);
	len += ft_intlen(ret);
	ret = (offset >> 8) & 0x000000ff;
	ft_print(1, "%d ", ret);
	len += ft_intlen(ret);
	ret = offset & 0x000000ff;
	ft_print(1, "%d\t", ret);
	len += ft_intlen(ret);
	if (len < 8)
		ft_print(1, "\t");
}

void	two_bytes(int offset)
{
	int	ret;

	ret = (offset >> 8) & 0x000000ff;
	ft_print(1, "\t%d", ret);
	ret = offset & 0x000000ff;
	ft_print(1, " %d\t\t", ret);
}

int		print_header(t_asm *vasm, t_header header)
{
	ft_print(1, "Dumping annotated program on standard output\n");
	ft_print(1, "Program size : %d bytes\n", vasm->size);
	ft_print(1, "Name : \"%s\"\n", header.prog_name);
	ft_print(1, "Comment : \"%s\"\n", header.comment);
	return (-1);
}
