/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grosendo <grosendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:33:50 by grosendo          #+#    #+#             */
/*   Updated: 2022/03/23 21:09:23 by grosendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_execline	*parse(char *str, t_shell *minishell)
{
	t_execline	*execl;

	if (!check_quotes(str))
		return (NULL);
	str = translate_env(str, minishell);
	if (!str)
		return (NULL);
	execl = parse_execline(str, minishell);
	free(str);
	if (!execl)
		return (NULL);
	(*execl).shell = minishell;
	if (make_pipes(execl))
		return (execl);
	return (NULL);
}
