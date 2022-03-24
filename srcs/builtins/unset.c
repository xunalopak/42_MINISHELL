/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grosendo <grosendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:41:24 by rchampli          #+#    #+#             */
/*   Updated: 2022/03/23 21:21:14 by grosendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**remove_env(ssize_t i2, char **envp)
{
	char	*tmp;
	size_t	i;
	size_t	size;

	i = i2;
	size = get_env_count(envp);
	while (envp[i + 1])
	{
		tmp = ft_strdup(envp[i + 1]);
		free(envp[i]);
		envp[i] = tmp;
		i++;
	}
	return (realloc_env((size - 1), envp, 1));
}

int	unset(char **arg, char ***envp)
{
	size_t	i;
	ssize_t	i2;

	if (!arg[1])
		return (1);
	i = 0;
	while (arg[++i])
	{
		i2 = find_env(arg[i], *envp);
		if (i2 != -1)
		{
			if (*envp[i2])
				*envp = remove_env(i2, *envp);
		}
		if (!check_export_name(arg[i]))
		{
			ft_printerror("minishell: unset `");
			ft_printerror(arg[i]);
			ft_printerror("': not a valid identifier\n");
			return (1);
		}
	}
	return (0);
}
