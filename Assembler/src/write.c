/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 17:31:48 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/27 17:31:54 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static	void	write_label(int fd, t_asm *s, t_cmd *cmd, int j)
{
	int			distance;

	distance = label(s, s->cmd, cmd->args[j]) - cmd->byte_start;
	if ((cmd->args[j][1] == LABEL_CHAR) && (cmd->size[j] == 4))
	{
		distance = big_end(distance, 4);
		write(fd, &distance, 4);
	}
	else
	{
		distance = big_end(distance, 2);
		write(fd, &distance, 2);
	}
}

static	int		write_direct(int fd, t_cmd *cmd, int j, int long val)
{
	if (cmd->size[j] == 2)
	{
		val = big_end(val, 2);
		write(fd, &val, 2);
	}
	else if (cmd->size[j] == 4)
	{
		val = big_end(val, 4);
		write(fd, &val, 4);
	}
	return (0);
}

static	int		write_params(int fd, t_asm *s, int i)
{
	int			j;
	int	long	val;

	j = -1;
	val = 0;
	while (++j < s->cmd[i]->nb_args)
	{
		val = ft_atoi_max(&(s->cmd[i]->args[j][1]));
		if ((s->cmd[i]->args[j][0] == ':') || (s->cmd[i]->args[j][1] == ':'))
			write_label(fd, s, s->cmd[i], j);
		else if (s->cmd[i]->args[j][0] == 'r')
			write(fd, &val, 1);
		else if (s->cmd[i]->args[j][0] == '%' && (s->cmd[i]->args[j][1] != ':'))
			write_direct(fd, s->cmd[i], j, val);
		else if (ft_isdigit(s->cmd[i]->args[j][0]))
		{
			val = ft_atoi_max(&(s->cmd[i]->args[j][0]));
			val = big_end(val, 2);
			write(fd, &val, 2);
		}
	}
	return (0);
}

static	void	write_instruction(int fd, t_asm *s, int i)
{
	int			op;

	op = s->cmd[i]->inst;
	write(fd, &op, 1);
	if (is_ocp(op))
		write_ocp(fd, s, i);
	write_params(fd, s, i);
}

int				write_in_cor(int fd, t_asm *s, t_header *h)
{
	int			inst;

	inst = 0;
	h->prog_size = s->size;
	h->magic = big_end(0xea83f3, 4);
	h->prog_size = big_end(s->size, 4);
	write(fd, h, sizeof(t_header));
	while (s->cmd[inst])
	{
		write_instruction(fd, s, inst);
		inst++;
	}
	return (0);
}
