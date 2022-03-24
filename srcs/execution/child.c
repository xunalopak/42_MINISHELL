/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grosendo <grosendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 18:47:52 by grosendo          #+#    #+#             */
/*   Updated: 2022/03/24 01:21:34 by grosendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirect_in_out(t_execline *execl, t_block *block)
{
	int		*fd;

	fd = &(execl->pipes[get_index_block(block) * 2]);
	if (block->before)
		dup2(fd[0 - 2], STDIN_FILENO);
	if (block->next)
		dup2(fd[1], STDOUT_FILENO);
	return (1);
}

int	open_error(t_token *token, int way, int *status)
{
	int	fd;

	if (token->type != FILE_IN && token->fd[0] > 2)
		close(token->fd[0]);
	else if (token->fd[1] > 2)
		close(token->fd[1]);
	fd = open(token->str, way, 0644);
	if (token->type != FILE_IN)
		token->fd[0] = fd;
	else
		token->fd[1] = fd;
	if (fd < 0)
	{
		ft_printerror("Minishell: ");
		ft_printerror(token->str);
		ft_printerror(" No such file or directory\n");
		*status = 1;
	}
	return (fd);
}

int	redirect_to_files(t_block *block, int *status)
{
	t_token	*token;

	token = block->first_token;
	while (token)
	{
		if (token->type == FILE_IN)
			dup2(open_error(token, O_RDONLY, status), STDIN_FILENO);
		else if (token->type == HEREDOC_IN)
			dup2(token->fd[0], STDIN_FILENO);
		else if (token->type == FILE_OUT)
			dup2(open_error(token, O_WRONLY | O_TRUNC | O_CREAT,
					status), STDOUT_FILENO);
		else if (token->type == FILE_OUT_CONCAT)
			dup2(open_error(token, O_WRONLY | O_APPEND | O_CREAT,
					status), STDOUT_FILENO);
		token = token->next;
	}
	return (1);
}

int	child_exec(t_execline *execl, t_block *block)
{
	char	*prgm;

	(*(execl->shell)).exit_status = 0;
	prgm = NULL;
	if (get_token_at_index(block->first_token, STR, 0))
		prgm = get_token_at_index(block->first_token, STR, 0)->str;
	redirect_in_out(execl, block);
	close_pipes(execl);
	redirect_to_files(block, &(execl->shell->exit_status));
	close_herdocs_files_fds(execl);
	if ((*execl).shell->exit_status)
		exit ((*execl).shell->exit_status);
	if (prgm)
		execute_block(block, execl->shell);
	exit (0);
}
