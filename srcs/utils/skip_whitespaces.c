/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_whitespaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grosendo <grosendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 11:41:44 by grosendo          #+#    #+#             */
/*   Updated: 2022/02/06 11:41:50 by grosendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_whitespaces(char **str)
{
	char	*s;

	if (str == NULL)
		return ;
	s = (*str);
	if (s == NULL)
		return ;
	while (ft_iswhitespace(*s))
		s++;
	*str = s;
}
