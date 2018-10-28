/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 17:31:44 by dbauduin          #+#    #+#             */
/*   Updated: 2018/10/27 17:31:46 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int					ft_atoi_bin(char *str)
{
	int				i;
	int				result;

	i = 0;
	result = 0;
	while (str[i] && (str[i] == '0' || str[i] == '1'))
	{
		result = result * 2 + (str[i] - 48);
		i++;
	}
	return (result);
}

static long long	ft_atoi_long(char *str)
{
	int				i;
	long long		num;
	int				sign;

	i = 0;
	sign = 1;
	num = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while ((str[i] >= '0') && (str[i] <= '9'))
		num = (num * 10) + (str[i++] - '0');
	return (num * sign);
}

static long long	check(int i, char *str, char *compare, int neg)
{
	int				j;

	j = 0;
	while (j < 19)
	{
		if (str[i + neg + j] > compare[j])
			return (neg == 1 ? 0 : 0xffffffff);
		else if (str[i + neg + j] < compare[j])
			return (ft_atoi_long(str));
		else if (str[i + neg + j] == compare[j])
			j++;
	}
	return (ft_atoi_long(str));
}

long long			ft_atoi_max(char *str)
{
	int				i;
	int				neg;

	i = 0;
	neg = 0;
	if (str[i] == '-')
		neg = 1;
	if (ft_strlen(str) - i - neg > 19)
		return (neg == 1 ? 0 : 0xffffffff);
	else if (ft_strlen(str) - i - neg < 19)
		return (ft_atoi_long(str));
	else if (ft_strlen(str) - i - neg == 19)
		return (check(i, str, "9223372036854775807", neg));
	return (-1);
}

uint32_t			big_end(uint32_t val, int size)
{
	uint32_t		nv;

	nv = 0;
	if (size == 1)
		nv = val;
	else if (size == 2)
	{
		val = (uint16_t)val;
		nv |= (uint32_t)((uint16_t)val << 8);
		nv |= (val >> 8);
	}
	else if (size == 4)
	{
		nv |= val >> 24;
		nv |= ((val >> 16) << 24) >> 16;
		nv |= ((val >> 8) << 24) >> 8;
		nv |= (val << 24);
	}
	return (nv);
}
