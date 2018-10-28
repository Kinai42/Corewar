/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 10:30:16 by dbauduin          #+#    #+#             */
/*   Updated: 2018/09/25 15:25:20 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_free(t_asm *vasm)
{
    int	i;
    int	l;

    i = -1;
    free(vasm->cor);
    while (vasm->lines && vasm->lines[++i])
        free(vasm->lines[i]);
    free(vasm->lines);
    i = -1;
    while (vasm->cmd && vasm->cmd[++i])
    {
        l = -1;
        while (vasm->cmd[i]->args && vasm->cmd[i]->args[++l])
            free(vasm->cmd[i]->args[l]);
        free(vasm->cmd[i]->args);
        free(vasm->cmd[i]->label);
        free(vasm->cmd[i]);
    }
    free(vasm->cmd);
}

int				main(int ac, char **av)
{
    t_asm		*vasm;
    t_header	header;

    if (!(vasm = (t_asm *)malloc(sizeof(t_asm))))
        return (-1);
    vasm->exe = *av;
    if (ac >= 2)
    {
        check_file(vasm, av);
        header = get_header(vasm);
        instruction(vasm);
        verif_label(vasm, vasm->cmd);
        if (vasm->opt && output(vasm, header))
        {
            ft_free(vasm);
            return (0);
        }
        file_cor(vasm, &header);
        ft_print(1, "Writing output program to %s\n", vasm->cor);
        ft_free(vasm);
    }
    else
        ft_error(0, vasm);
    free(vasm);
    return (0);
}
