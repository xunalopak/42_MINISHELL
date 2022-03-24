/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grosendo <grosendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:44:48 by grosendo          #+#    #+#             */
/*   Updated: 2022/03/23 21:19:10 by grosendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_shell(t_shell *shell)
{
	int		i;
	char	**env;

	i = 0;
	env = shell->envp;
	while (env && env[i])
	{
		free(env[i]);
		i++;
	}
	if (env)
		free(env);
}
