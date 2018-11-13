/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 13:01:49 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/15 13:50:59 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int check_cor(char *path)
{
    int len;

    if ((len = ft_strlen(path)) < 5 || ft_strcmp(&path[len - 4], ".cor"))
        return (0);
    return (1);
}
