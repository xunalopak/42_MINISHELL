/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grosendo <grosendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 09:42:27 by grosendo          #+#    #+#             */
/*   Updated: 2022/03/23 21:11:24 by grosendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_blocks(t_execline *execl)
{
	t_block	*block;
	int		i;

	i = 0;
	block = execl->first_block;
	while (block)
	{
		i++;
		block = block->next;
	}
	return (i);
}

int	make_pipes(t_execline *execl)
{
	int		i;

	(*execl).pipes = malloc(sizeof(*(*execl).pipes)
			* 2 * (count_blocks(execl) + 1));
	if (!(*execl).pipes)
		return (0);
	i = 0;
	while (i < count_blocks(execl))
	{
		(*execl).pipes[i * 2] = -1;
		if (pipe(&((*execl).pipes[i * 2])) != 0)
			return (0);
		i++;
	}
	(*execl).pipes[i * 2] = -1;
	return (1);
}
