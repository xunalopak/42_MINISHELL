/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grosendo <grosendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 01:21:05 by rchampli          #+#    #+#             */
/*   Updated: 2022/03/23 16:27:32 by grosendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_export_name(char *av)
{
	size_t	i;
	char	alpha;

	i = 0;
	alpha = 0;
	if (!av || !av[0] || av[0] == '=')
		return (0);
	while (av[i] && av[i] != '=')
	{
		if (ft_isalpha(av[i]))
			alpha = 1;
		else
		{
			if (ft_isdigit(av[i]) && !alpha)
				return (0);
			else if (!ft_isdigit(av[i]) && av[i] != '_')
				return (0);
		}
		i++;
	}
	return (1);
}

char	**dup_env(char **envp)
{
	char	**dup;
	size_t	count;

	count = get_env_count(envp);
	dup = (char **)malloc(sizeof(char *) * (count + 1));
	if (!dup)
		return (NULL);
	dup[count] = 0;
	count--;
	while (count != (unsigned long)-1)
	{
		dup[count] = ft_strdup(envp[count]);
		count--;
	}
	return (dup);
}

static void	print_export(char **export)
{
	size_t	i;
	size_t	j;
	char	equ;

	i = 0;
	while (export[i])
	{
		equ = 1;
		j = 0;
		printf("declare -x ");
		while (export[i][j])
		{
			printf("%c", export[i][j]);
			if (export[i][j] == '=' && equ)
			{
				printf("%c", 34);
				equ--;
			}
			j++;
		}
		if (!equ)
			printf("%c", 34);
		printf("\n");
		i++;
	}
}

void	sort_env(char **envp)
{
	char	**dup;
	char	*tmp;
	size_t	i;
	size_t	j;

	dup = dup_env(envp);
	i = 0;
	while (dup[i])
	{
		j = i + 1;
		while (dup[j])
		{
			if (ft_strcmp(dup[i], dup[j]) > 0)
			{
				tmp = dup[i];
				dup[i] = dup[j];
				dup[j] = tmp;
			}
			j++;
		}
		i++;
	}
	print_export(dup);
	ft_free_array(dup);
}
