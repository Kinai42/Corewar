/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 09:59:47 by dbauduin          #+#    #+#             */
/*   Updated: 2018/09/30 13:16:55 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char		get_file(t_asm *vasm)
{
	int			fd;
	char		*line;

	if ((fd = open(vasm->file_name, O_RDONLY)) == -1)
		ft_error(1, vasm);
	vasm->lines = (char **)ft_parrnew();
    vasm->l = 0;
	while ((line = ft_gnl(fd)))
    {
        vasm->l = ft_parrlen((void**)vasm->lines);
		ft_parrpush((void***)&(vasm->lines), line);
    }
    if (vasm->l == 0)
        ft_error(51, vasm);
	close(fd);
	return (1);
}

char			check_file(t_asm *vasm, char **av)
{
	int			len;
	int			i;
	char		*tmp;

	i = 0;
	tmp = NULL;
	vasm->file_name = NULL;
	vasm->cor = NULL;
	vasm->opt = 0;
	while (av[++i])
	{
		if (*av[i] == '-' && av[i][1] == 'a' && !av[i][2])
			vasm->opt = 1;
		else if ((len = ft_strlen(av[i])) > 2 && av[i][len - 1] == 's'
				&& av[i][len - 2] == '.')
			vasm->file_name = av[i];
	}
	if (!vasm->file_name)
		ft_error(0, vasm);
	tmp = ft_strndup(vasm->file_name, ft_strlen(vasm->file_name) - 1);
	vasm->cor = ft_strjoin(tmp, "cor");
	free(tmp);
	get_file(vasm);
	return (0);
}

int				file_cor(t_asm *s, t_header *h)
{
	if ((s->fd = open(s->cor, O_WRONLY | O_CREAT, 0777)) == -1)
		ft_error(50, s);
	write_in_cor(s->fd, s, h);
	return (1);
}
