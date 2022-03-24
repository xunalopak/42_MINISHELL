/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grosendo <grosendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 09:33:39 by grosendo          #+#    #+#             */
/*   Updated: 2022/03/23 21:03:09 by grosendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_words(char *str, char *charset)
{
	size_t	str_len;
	int		word_counter;
	size_t	i;

	str_len = ft_strlen(str);
	word_counter = 0;
	i = 0;
	while (i < str_len)
	{
		while (i < str_len && ft_isinset(charset, str[i]))
			i++;
		if (i < str_len)
			word_counter++;
		else
			continue ;
		while (i < str_len && !ft_isinset(charset, str[i]))
			i++;
	}
	return (word_counter);
}

void	fill_words(char *str, char *charset, char **result)
{
	size_t	str_len;
	int		word_counter;
	size_t	i;
	size_t	temp;

	str_len = ft_strlen(str);
	word_counter = 0;
	i = 0;
	while (i < str_len)
	{
		while (i < str_len && ft_isinset(charset, str[i]))
			i++;
		if (i < str_len)
		{
			temp = i;
			word_counter++;
		}
		else
			continue ;
		while (i < str_len && !ft_isinset(charset, str[i]))
			i++;
		result[word_counter - 1] = ft_strndup(&str[temp], i - temp, 0);
	}
}

char	**ft_split(char *str, char *charset)
{
	char	**result;
	int		word_counter;

	if (str == NULL || charset == NULL)
		return (NULL);
	result = NULL;
	word_counter = count_words(str, charset);
	result = malloc((word_counter + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	fill_words(str, charset, result);
	result[word_counter] = NULL;
	return (result);
}
