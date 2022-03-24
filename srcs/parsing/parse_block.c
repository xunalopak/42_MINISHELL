/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_block.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grosendo <grosendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 19:06:14 by grosendo          #+#    #+#             */
/*   Updated: 2022/03/23 21:09:16 by grosendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_token(char **str)
{
	if (**str == '|' || **str == 0)
		return (0);
	return (1);
}

void	add_last_block(t_execline *execl, t_block *block)
{
	t_block	*last_block;

	if (!((*execl).first_block))
	{
		(*execl).first_block = block;
		return ;
	}
	last_block = (*execl).first_block;
	while (last_block->next)
		last_block = last_block->next;
	(*last_block).next = block;
	(*block).before = last_block;
}

int	parse_block(t_execline *execl, char **str, t_shell *shell)
{
	t_block	*block;

	skip_whitespaces(str);
	if (!has_token(str))
		return (0);
	block = malloc_block();
	if (!block)
		return (0);
	while (has_token(str))
	{
		if (!parse_token(block, str, shell))
		{
			free_block(block);
			return (0);
		}
		skip_whitespaces(str);
	}
	add_last_block(execl, block);
	return (1);
}
