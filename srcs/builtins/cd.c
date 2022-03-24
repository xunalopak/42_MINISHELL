/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grosendo <grosendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 15:10:06 by rchampli          #+#    #+#             */
/*   Updated: 2022/03/24 00:27:41 by grosendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*add_home_path(char *path, char **envp)
{
	char	*tmp;
	char	*tmpp;

	if (!ft_strncmp(path, "~/", 2))
	{
		tmp = get_env("HOME", envp);
		if (tmp)
		{
			tmpp = ft_substr(path, 1, ft_strlen(path));
			free(path);
			path = ft_strjoin(tmp, tmpp);
			free(tmpp);
			free(tmp);
			return (path);
		}
	}
	return (path);
}

static int	change(char *path, char **envp)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!chdir(path))
	{
		if (pwd)
		{
			set_env("OLDPWD", pwd, envp);
			free(pwd);
		}
		pwd = getcwd(NULL, 0);
		if (pwd)
		{
			set_env("PWD", pwd, envp);
			free(pwd);
		}
		return (1);
	}
	free(pwd);
	return (0);
}

int	set_directory(char *path, int home, char **envp)
{
	struct stat	st;

	if (change(path, envp))
		return (1);
	ft_printerror("minishell: cd: ");
	ft_printerror(path);
	if (stat(path, &st) == -1)
	{
		ft_printerror(": No such file or directory");
	}
	else if (!(st.st_mode & S_IXUSR))
		ft_printerror(": Permission denied");
	else
		ft_printerror(": Not a directory");
	ft_printerror("\n");
	if (home)
		free(path);
	return (1);
}

int	s_path(char **args, char **envp)
{
	char	*tmp;

	if (ft_strequ(args[1], "-"))
	{
		tmp = get_env("OLDPWD", envp);
		if (tmp)
		{
			set_directory(tmp, 0, envp);
			free(tmp);
		}
		tmp = get_env("PWD", envp);
		if (tmp)
		{
			printf("%s", tmp);
			free(tmp);
			printf("\n");
		}
		return (1);
	}
	return (set_directory(args[1], 0, envp));
}

int	cd(char **args, char **envp)
{
	char	*home;

	home = NULL;
	if (args && args[1] && args[2])
	{
		ft_printerror("minishell: cd: too many arguments\n");
		return (0);
	}
	if (!args[1] || ft_strequ(args[1], "~") || ft_strequ(args[1], "--"))
	{
		home = get_env("HOME", envp);
		if (!(home))
		{
			ft_printerror("minishell: cd: HOME not set\n");
			return (0);
		}
		return (set_directory(home, 1, envp));
	}
	args[1] = add_home_path(args[1], envp);
	return (s_path(args, envp));
}
