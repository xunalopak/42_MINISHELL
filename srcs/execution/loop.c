/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grosendo <grosendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 17:00:34 by grosendo          #+#    #+#             */
/*   Updated: 2022/03/24 00:07:15 by grosendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	loop(t_shell *minishell)
{
	char		*buffer;
	t_execline	*execl;

	while (1)
	{
		ft_itoa_spe(minishell->exit_status, minishell->exittxt);
		buffer = readline(MINISHELL);
		if (!buffer)
			break ;
		if (buffer && ft_strlen(buffer) > 0)
			add_history(buffer);
		execl = parse(buffer, minishell);
		if (execl)
			execute(execl);
		else
			printf("Minishell : parse error.\n");
		free_execl(execl);
		free(buffer);
		if (minishell->exit)
			break ;
	}
}
