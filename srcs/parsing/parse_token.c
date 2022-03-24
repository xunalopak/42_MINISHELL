/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grosendo <grosendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 21:04:56 by grosendo          #+#    #+#             */
/*   Updated: 2022/03/23 21:08:22 by grosendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_token_str(t_token *token, char **str)
{
	int	quote;
	int	i;

	quote = 0;
	i = 0;
	while ((quote != 0 || !is_end_of_token(**str)) && **str)
	{
		if (**str == '"' && quote == 0)
			quote = 1;
		else if (**str == '\'' && quote == 0)
			quote = 2;
		else if (**str == '"' && quote == 1)
			quote = 0;
		else if (**str == '\'' && quote == 2)
			quote = 0;
		else
		{
			(*token).str[i] = **str;
			i++;
		}
		(*str)++;
	}
	(*token).str[i] = 0;
}

void	type_token(t_token *token, char **str)
{
	(*token).type = STR;
	if (**str == '>')
	{
		(*token).type = FILE_OUT;
		(*str)++;
		if (**str == '>')
		{
			(*token).type = FILE_OUT_CONCAT;
			(*str)++;
		}
	}
	else if (**str == '<')
	{
		(*token).type = FILE_IN;
		(*str)++;
		if (**str == '<')
		{
			(*token).type = HEREDOC_IN;
			(*str)++;
		}
	}
}

void	add_last_token(t_block *block, t_token *token)
{
	t_token	*last_token;

	if (!((*block).first_token))
	{
		(*block).first_token = token;
		return ;
	}
	last_token = (*block).first_token;
	while (last_token->next)
		last_token = last_token->next;
	(*last_token).next = token;
	(*token).before = last_token;
}

int	parse_token(t_block *block, char **str, t_shell *shell)
{
	t_token	*token;

	token = malloc_token();
	if (!token)
		return (0);
	skip_whitespaces(str);
	type_token(token, str);
	skip_whitespaces(str);
	if (create_token_str(token, str))
		fill_token_str(token, str);
	else
	{
		free_token(token);
		return (0);
	}
	if (!fill_herdoc(token, shell))
	{
		free_token(token);
		return (0);
	}
	add_last_token(block, token);
	skip_whitespaces(str);
	return (1);
}
