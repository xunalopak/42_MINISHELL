/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grosendo <grosendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 23:49:08 by grosendo          #+#    #+#             */
/*   Updated: 2022/03/24 00:29:21 by grosendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_atoi(char *str)
{
	int	res;
	int	negative;

	negative = 1;
	res = 0;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t'
			|| *str == '\v' || *str == '\f' || *str == '\r'))
		++str;
	if (*str == '-')
		negative = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		++str;
	}
	return (res * negative);
}

int	ft_strisnum(char *str)
{
	if (!str || !*str)
		return (0);
	str--;
	while (++str && *str)
		if (!ft_isdigit(*str))
			return (0);
	return (1);
}

int	mini_exit(char **arg)
{
	if (arg[1] && ft_strisnum(arg[1]) == 0)
	{
		ft_printerror("Minishell: exit: ");
		ft_printerror(arg[1]);
		ft_printerror(": numeric argument required\n");
		return (255);
	}
	else if (arg[1] && arg[2])
		ft_printerror("Minishell: exit: too many arguments\n");
	else if (arg[1])
		return (ft_atoi(arg[1]));
	else
		return (0);
	return (0);
}
