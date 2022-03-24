/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_block.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grosendo <grosendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 09:58:51 by grosendo          #+#    #+#             */
/*   Updated: 2022/03/24 01:40:06 by grosendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**extract_argv(t_block *block)
{
	int		i;
	char	**argv;

	i = 0;
	if (!get_token_at_index(block->first_token, STR, i))
		return (NULL);
	while (get_token_at_index(block->first_token, STR, i))
		i++;
	argv = malloc(sizeof(*argv) * (i + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (get_token_at_index(block->first_token, STR, i))
	{
		argv[i] = get_token_at_index(block->first_token, STR, i)->str;
		argv[i + 1] = NULL;
		i++;
	}
	return (argv);
}

void	execve_link(char *prgm, char **argv, char **envp)
{
	int		i;
	char	**paths;
	char	*srcprgm;

	execve(prgm, argv, envp);
	paths = ft_split(get_env("PATH", envp), ":");
	i = 0;
	while (paths && paths[i])
	{
		srcprgm = ft_strjoin(paths[i], "/");
		if (!srcprgm)
			break ;
		srcprgm = ft_strjoin(srcprgm, prgm);
		if (!srcprgm)
			break ;
		execve(srcprgm, argv, envp);
		i++;
	}
}

void	execute_prgm(t_block *block, t_shell *minishell)
{
	char	*prgm;
	char	**argv;

	prgm = get_token_at_index(block->first_token, STR, 0)->str;
	argv = extract_argv(block);
	if (is_a_builtin(prgm))
		exit(launch_builtin(prgm, argv, &(minishell->envp)));
	execve_link(prgm, argv, minishell->envp);
	ft_printerror("Minishell: ");
	ft_printerror(prgm);
	ft_printerror(" command not found\n");
	exit(127);
}

void	execute_block(t_block *block, t_shell *minishell)
{
	execute_prgm(block, minishell);
}
