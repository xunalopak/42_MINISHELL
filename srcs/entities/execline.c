/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grosendo <grosendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:44:49 by grosendo          #+#    #+#             */
/*   Updated: 2022/03/23 21:20:12 by grosendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_execline	init_execl(void)
{
	t_execline	execl;

	execl.first_block = NULL;
	execl.pipes = NULL;
	return (execl);
}

t_execline	*malloc_execl(void)
{
	t_execline	*execl;

	execl = malloc(sizeof(*execl));
	if (!execl)
		return (NULL);
	(*execl) = init_execl();
	return (execl);
}

void	free_execl(t_execline *execl)
{
	t_block	*to_free;

	if (!execl)
		return ;
	while (execl->first_block)
	{
		to_free = execl->first_block;
		(*execl).first_block = execl->first_block->next;
		free_block(to_free);
	}
	if (execl->pipes)
		free(execl->pipes);
	free(execl);
}
