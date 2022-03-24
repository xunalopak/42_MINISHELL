/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grosendo <grosendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 01:14:51 by rchampli          #+#    #+#             */
/*   Updated: 2022/03/23 14:25:55 by grosendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1 && s2 && s1[i] == s2[i] && s1[i] && s2[i] && i < n)
		i++;
	if (i <= n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}
