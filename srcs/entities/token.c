/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grosendo <grosendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 19:22:24 by grosendo          #+#    #+#             */
/*   Updated: 2022/03/23 21:19:02 by grosendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	init_token(void)
{
	t_token	token;

	token.before = NULL;
	token.next = NULL;
	token.str = NULL;
	token.type = UNDEFINED;
	token.fd[0] = -1;
	token.fd[1] = -1;
	return (token);
}

t_token	*malloc_token(void)
{
	t_token	*token;

	token = malloc(sizeof(*token));
	if (!token)
		return (NULL);
	(*token) = init_token();
	return (token);
}

t_token	*get_token_at_index(t_token *token, int type, int index)
{
	int		i;

	i = 0;
	while (token)
	{
		if (type == token->type || type == -1)
		{
			if (i == index)
				return (token);
			i++;
		}
		token = token->next;
	}
	return (NULL);
}

void	free_token(t_token *token)
{
	if (!token)
		return ;
	if ((*token).str)
		free((*token).str);
	free(token);
}
