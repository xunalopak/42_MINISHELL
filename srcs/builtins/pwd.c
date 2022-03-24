/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grosendo <grosendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 14:06:52 by rchampli          #+#    #+#             */
/*   Updated: 2022/03/23 16:27:41 by grosendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(void)
{
	char	*dir;

	dir = getcwd((char *) NULL, 1);
	printf("%s\n", dir);
	free(dir);
	if (dir == NULL)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}
