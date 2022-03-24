/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grosendo <grosendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 22:44:12 by grosendo          #+#    #+#             */
/*   Updated: 2022/03/23 21:06:50 by grosendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quotes(char *str)
{
	int		i;
	int		quote;

	if (!str)
		return (0);
	i = 0;
	quote = 0;
	while (str[i])
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
	return (quote == 0);
}

int	vnl(char *str)
{
	int	i;
	int	is_digit_var;

	is_digit_var = 0;
	i = 0;
	while (str[i])
	{
		if (i == 0)
		{
			if (ft_isdigit(str[i]))
				is_digit_var = 1;
			else if (str[i] == '?')
				return (1);
			else if (!ft_isalphanumus(str[i]))
				return (0);
		}
		else if (!ft_isalphanumus(str[i])
			|| (is_digit_var && !ft_isdigit(str[i])))
			break ;
		i++;
	}
	return (i);
}

char	*genv_or_estatus(char *varname, t_shell *shell)
{
	if (varname[0] == '?')
		return (shell->exittxt);
	return (get_env(varname, shell->envp));
}

int	replace_var_env(char **str, int var_index, t_shell *shell)
{
	char	*r[2];
	char	*varname;
	int		i;

	if (vnl(&((*str)[var_index])) == 0)
		return (0);
	varname = malloc(sizeof(*varname) * (vnl(&((*str)[var_index])) + 1));
	if (!varname)
		return (0);
	i = -1;
	while ((++i) < vnl(&((*str)[var_index])))
		varname[i] = (*str)[var_index + i];
	varname[i] = 0;
	(*str)[var_index - 1] = 0;
	r[0] = ft_strjoin(*str, genv_or_estatus(varname, shell));
	free(varname);
	if (!r[0])
		return (0);
	r[1] = ft_strjoin(r[0], &((*str)[var_index + vnl(&((*str)[var_index]))]));
	free(r[0]);
	if (!r[1])
		return (0);
	free(*str);
	*str = r[1];
	return (1);
}

char	*translate_env(char *str, t_shell *minishell)
{
	int		i;
	int		quote;

	i = 0;
	quote = 0;
	str = ft_strjoin(str, "");
	while (str && str[i])
	{
		if (str[i] == '"' && quote == 0)
			quote = 1;
		else if (str[i] == '\'' && quote == 0)
			quote = 2;
		else if (str[i] == '"' && quote == 1)
			quote = 0;
		else if (str[i] == '\'' && quote == 2)
			quote = 0;
		else if (str[i] == '$'
			&& quote != 2 && replace_var_env(&str, i + 1, minishell))
			i = -1;
		i++;
	}
	return (str);
}
