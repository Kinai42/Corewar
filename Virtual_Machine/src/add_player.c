/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 12:17:44 by dbauduin          #+#    #+#             */
/*   Updated: 2018/11/13 02:09:01 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			*parse_player(int fd, t_env *env, t_player *player)
{
    t_header	*header;
    void		*buffer;
    void		*data;
    int         rd;

    buffer = ft_memalloc(sizeof(t_header));
    if (read(fd, buffer, sizeof(t_header)) == -1)
        ft_error(9, env);
    header = (t_header*)buffer;
    if ((rev_int(header->magic) != COREWAR_EXEC_MAGIC))
        ft_error(8, env);
    if (rev_int(header->prog_size) > CHAMP_MAX_SIZE)
        ft_error(7, env);
    data = ft_memalloc(sizeof(t_header));
    ft_memcpy(data, buffer, sizeof(t_header));
    if ((rd = read(fd, player->content, rev_int(header->prog_size))) == -1)
        ft_error(6, env);
    free(buffer);
    player->content[rd] = '\0';
    return (data);
}

int			find_player(t_player **players, int n)
{
    int i;

    i = -1;
    while (players[++i])
        if (players[i]->nbr == n)
            return (1);
    return (0);
}

void            add_player_n(t_env *env, char **av, int ac, int *i)
{
    if (*i + 3 > ac)
        ft_error(5, env);
    if (ft_intlen(ft_atoi(av[(*i + 1)])) != (int)ft_strlen(av[(*i + 1)]) ||
            ft_atoi(av[(*i + 1)]) <= 0)
        ft_error(4, env);
    env->n = (unsigned int)ft_atoi(av[(*i + 1)]);
    *i += 2;
    add_player(env, av[*i]);
}

void			add_player(t_env *env, char *path)
{
    t_player	*player;
    t_header	*header;
    void		*data;
    int			fd;

    env->path = path;
    if (ft_parrlen((void**)env->player) == MAX_PLAYERS)
        ft_error(1, env); /*too many champions*/
    if (!check_cor(path))
        ft_error(2, env); /*file fail*/
    if ((fd = open(path, O_RDONLY)) == -1)
        ft_error(3, env); /*open fail*/
    player = (t_player*)ft_memalloc(sizeof(t_player));
    data = parse_player(fd, env, player);
    header = (t_header*)data;
    close(fd);
    init_player(env, player, header);
    ft_parrpush((void***)&env->player, player);
    env->n = 0;
}
