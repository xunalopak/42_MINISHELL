/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grosendo <grosendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 21:52:00 by grosendo          #+#    #+#             */
/*   Updated: 2022/03/23 21:07:08 by grosendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_end_of_token(char c)
{
	if (ft_isinset("<>|\n\t\v\r\f ", c) || c == 0)
		return (1);
	return (0);
}

int	count_token_str(char *str)
{
	int	quote;
	int	i;

	quote = 0;
	i = 0;
	while ((quote != 0 || !is_end_of_token(str[i])) && str[i])
	{
		if (str[i] == '"' && quote == 0)
			quote = 1;
		else if (str[i] == '\'' && quote == 0)
			quote = 2;
		else if (str[i] == '"' && quote == 1)
			quote = 0;
		else if (str[i] == '\'' && quote == 2)
			quote = 0;
		i++;
	}
	if (quote != 0)
		return (0);
	return (i);
}

int	create_token_str(t_token *token, char **str)
{
	if (count_token_str(*str) == 0)
		return (0);
	(*token).str = malloc(sizeof(**str) * (count_token_str(*str) + 1));
	if (!(*token).str)
		return (0);
	return (1);
}
