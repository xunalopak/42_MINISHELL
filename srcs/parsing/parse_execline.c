/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_execline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grosendo <grosendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:41:51 by grosendo          #+#    #+#             */
/*   Updated: 2022/03/23 21:08:54 by grosendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_execline	*parse_execline(char *str, t_shell *shell)
{
	t_execline	*execl;

	skip_whitespaces(&str);
	if (*str == '|')
		return (NULL);
	execl = malloc_execl();
	if (!execl)
		return (NULL);
	while (*str)
	{
		if (*str == '|')
			str++;
		if (!parse_block(execl, &str, shell))
		{
			free_execl(execl);
			return (NULL);
		}
		skip_whitespaces(&str);
	}
	return (execl);
}

void	debug_parsing(t_execline *execl)
{
	t_block	*block;
	t_token	*token;

	if (!execl)
	{
		printf("Minishell : parse error\n");
		return ;
	}
	block = execl->first_block;
	while (block)
	{
		token = block->first_token;
		while (token)
		{
			printf("\ntype=%d\n", token->type);
			printf("%s\n", token->str);
			token = token->next;
		}
		block = block->next;
		if (block)
			printf("\n|\n");
	}
}
