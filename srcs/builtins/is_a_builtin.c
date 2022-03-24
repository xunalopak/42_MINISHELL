/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_a_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grosendo <grosendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 22:29:00 by rchampli          #+#    #+#             */
/*   Updated: 2022/03/24 00:00:52 by grosendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_a_builtin(char *arg)
{
	if (ft_strequ(arg, "cd"))
		return (1);
	else if (ft_strequ(arg, "export"))
		return (1);
	else if (ft_strequ(arg, "pwd"))
		return (1);
	else if (ft_strequ(arg, "unset"))
		return (1);
	else if (ft_strequ(arg, "env"))
		return (1);
	else if (ft_strequ(arg, "echo"))
		return (1);
	else if (ft_strequ(arg, "exit"))
		return (1);
	return (0);
}

int	launch_builtin(char *prgm, char **av, char ***envp)
{
	int	i;

	i = 0;
	if (ft_strequ(prgm, "cd"))
		i = cd(av, *envp);
	else if (ft_strequ(prgm, "export"))
		i = ft_export(av, envp);
	else if (ft_strequ(prgm, "pwd"))
		i = pwd();
	else if (ft_strequ(prgm, "unset"))
		i = unset(av, envp);
	else if (ft_strequ(prgm, "env"))
		i = print_env(*envp);
	else if (ft_strequ(prgm, "echo"))
		i = echo(av, *envp);
	else if (ft_strequ(prgm, "exit"))
		i = mini_exit(av);
	return (i);
}
