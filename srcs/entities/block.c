/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grosendo <grosendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 19:07:30 by grosendo          #+#    #+#             */
/*   Updated: 2022/03/23 21:21:10 by grosendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_block	init_block(void)
{
	t_block	block;

	block.pid = -1;
	block.before = NULL;
	block.next = NULL;
	block.first_token = NULL;
	return (block);
}

t_block	*malloc_block(void)
{
	t_block	*block;

	block = malloc(sizeof(*block));
	if (!block)
		return (NULL);
	(*block) = init_block();
	return (block);
}

int	get_index_block(t_block *block)
{
	int	i;

	i = 0;
	while (block->before)
	{
		block = block->before;
		i++;
	}
	return (i);
}

void	free_block(t_block *block)
{
	t_token	*to_free;

	if (!block)
		return ;
	while (block->first_token)
	{
		to_free = block->first_token;
		(*block).first_token = block->first_token->next;
		free_token(to_free);
	}
	free(block);
}
