/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   front_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grosendo <grosendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:56:40 by grosendo          #+#    #+#             */
/*   Updated: 2022/03/24 00:29:48 by grosendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	copy_fd(int	*fd)
{
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	if (fd[0] < 0 || fd[1] < 0)
	{
		ft_printerror("Minishell: dup error.");
		return (0);
	}
	return (1);
}

int	restablish_fd(int	*fd)
{
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	return (1);
}

int	has_to_front_exec(t_execline *execl)
{
	char	*prgm;
	t_block	*block;

	if (!(execl->first_block))
		return (0);
	block = execl->first_block;
	if (block->next)
		return (0);
	prgm = NULL;
	if (get_token_at_index(block->first_token, STR, 0))
		prgm = get_token_at_index(block->first_token, STR, 0)->str;
	if (prgm && is_a_builtin(prgm))
		return (1);
	return (0);
}

int	manage_exit(t_execline *execl)
{
	if (execl->first_block
		&& get_token_at_index(execl->first_block->first_token, STR, 0))
		if (ft_strdiff(get_token_at_index(execl->first_block->first_token,
					STR, 0)->str, "exit") == 0)
			execl->shell->exit = 1;
	return (1);
}

int	execute_front(t_execline *execl)
{
	char	*prgm;
	char	**argv;
	int		cp_fd[2];

	(*(execl->shell)).exit_status = 0;
	if (!copy_fd(cp_fd))
		return (1);
	redirect_in_out(execl, execl->first_block);
	redirect_to_files(execl->first_block, &((*execl).shell->exit_status));
	if ((*(execl->shell)).exit_status)
		return ((*(execl->shell)).exit_status);
	prgm = get_token_at_index(execl->first_block->first_token, STR, 0)->str;
	argv = extract_argv(execl->first_block);
	if (!argv)
		return (0);
	(*(execl->shell)).exit_status
		= launch_builtin(prgm, argv, &(execl->shell->envp));
	manage_exit(execl);
	free(argv);
	close_pipes(execl);
	close_herdocs_files_fds(execl);
	restablish_fd(cp_fd);
	return ((*(execl->shell)).exit_status);
}
