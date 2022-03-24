/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grosendo <grosendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 01:52:22 by rchampli          #+#    #+#             */
/*   Updated: 2022/03/23 21:05:44 by grosendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_array(char **array)
{
	size_t	i;

	i = -1;
	if (!array)
		return ;
	while (array[++i] != NULL)
	{
		if (array[i])
			free(array[i]);
	}
	free(array);
}
