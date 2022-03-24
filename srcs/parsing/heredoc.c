/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grosendo <grosendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:40:51 by grosendo          #+#    #+#             */
/*   Updated: 2022/03/24 00:30:13 by grosendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	here_doc(char *end_of_file, t_token *token, t_shell *shell)
{
	char	*buffer;
	int		tmp_fd;
	char	*str;

	tmp_fd = dup(STDOUT_FILENO);
	if (tmp_fd < 0 || pipe(token->fd) != 0)
		return (0);
	while (1)
	{
		buffer = readline(HEREDOC);
		if (!buffer || ft_strdiff(buffer, end_of_file) == 0)
			break ;
		str = translate_env(buffer, shell);
		dup2(token->fd[1], STDOUT_FILENO);
		printf("%s\n", str);
		dup2(tmp_fd, STDOUT_FILENO);
		free(str);
		free(buffer);
	}
	if (buffer)
		free(buffer);
	close(tmp_fd);
	return (1);
}

int	fill_herdoc(t_token *token, t_shell *shell)
{
	if (token->type != HEREDOC_IN)
		return (1);
	if (!(*token).str)
		return (0);
	here_doc((*token).str, token, shell);
	if (!(*token).str)
		return (0);
	return (1);
}

void	close_herdocs_files_fds(t_execline *execl)
{
	t_block	*block;
	t_token	*token;

	block = execl->first_block;
	while (block)
	{
		token = block->first_token;
		while (token)
		{
			if (token->type == HEREDOC_IN && token->fd[0] > 2)
			{
				close(token->fd[0]);
				close(token->fd[1]);
			}
			else if (token->type != FILE_IN && token->fd[0] > 2)
				close(token->fd[0]);
			else if (token->type != FILE_OUT && token->type != FILE_OUT_CONCAT
				&& token->fd[1] > 2)
				close(token->fd[1]);
			token = token->next;
		}
		block = block->next;
	}
}
