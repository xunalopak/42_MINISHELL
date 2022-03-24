/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grosendo <grosendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 13:45:29 by rchampli          #+#    #+#             */
/*   Updated: 2022/03/23 16:27:25 by grosendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**realloc_env(size_t size, char **envp, int to_free)
{
	char	**new;
	size_t	i;

	new = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (envp[i] && i < size)
	{
		new[i] = ft_strdup(envp[i]);
		i++;
	}
	new[size] = 0;
	if (to_free == 1)
		ft_free_array(envp);
	return (new);
}

char	*get_env(char *name, char **env)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		tmp = ft_strjoin(name, "=");
		if (ft_strstartwith(env[i], tmp))
		{
			free(tmp);
			return (ft_strchr(env[i], '=') + 1);
		}
		free(tmp);
		i++;
	}
	return ("");
}

ssize_t	find_env(char *env, char **envp)
{
	char	*sub;
	ssize_t	i;
	ssize_t	i2;

	if (!env)
		return (0);
	i = -1;
	sub = 0;
	while (envp[++i])
	{
		i2 = ft_istrchr(envp[i], '=');
		if (i2 == -1)
			i2 = ft_strlen(envp[i]);
		sub = ft_substr(envp[i], 0, i2);
		if (sub)
		{
			if (ft_strequ(sub, env))
			{
				free(sub);
				return (i);
			}
			free(sub);
		}
	}
	return (-1);
}

static int	modify_env(char *new_env, size_t len, ssize_t i, char **envp)
{
	char	*tmp;
	char	*new;

	tmp = ft_substr(envp[i], 0, (len + 1));
	if (!tmp)
		return (0);
	new = ft_strjoin(tmp, new_env);
	if (!new)
		return (0);
	free(envp[i]);
	free(tmp);
	envp[i] = new;
	return (1);
}

int	set_env(char *env, char *new_env, char **envp)
{
	char	*tmp;
	ssize_t	i;
	size_t	len;

	if (!env || !new_env)
		return (0);
	len = ft_strlen(env);
	i = find_env(env, envp);
	if (i != -1)
		return (modify_env(new_env, len, i, envp));
	else
	{
		len = get_env_count(envp) + 1;
		envp = realloc_env(len, envp, 1);
		tmp = ft_strjoin(env, "=");
		envp[len - 1] = ft_strjoin(tmp, new_env);
		free(tmp);
		return (1);
	}
	return (0);
}
