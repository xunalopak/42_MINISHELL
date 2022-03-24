/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grosendo <grosendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 09:01:28 by grosendo          #+#    #+#             */
/*   Updated: 2022/03/23 23:45:03 by grosendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	save_pids(t_block *block, pid_t pid)
{
	(*block).pid = pid;
	return (1);
}

int	launch_execution(t_execline *execl)
{
	t_block	*block;
	pid_t	pid;

	block = execl->first_block;
	while (block)
	{
		pid = fork();
		if (pid < 0)
			ft_printerror("Minishell : fork error.\n");
		else if (pid == 0)
			child_exec(execl, block);
		else if (pid > 1)
			save_pids(block, pid);
		block = block->next;
	}
	return (0);
}

int	wait_pids(t_block *f_block, t_shell *shell)
{
	int	status;

	status = 0;
	if (!f_block)
		return (0);
	while (f_block && waitpid(f_block->pid, &status, WUNTRACED) > 0)
	{
		f_block = f_block->next;
		if (!f_block)
			(*shell).exit_status = WEXITSTATUS(status);
	}
	return (status);
}

int	close_pipes(t_execline *execl)
{
	int	i;

	if (!execl->pipes)
		return (0);
	i = 0;
	while (execl->pipes[i] > 2)
	{
		close(execl->pipes[i]);
		i++;
	}
	return (1);
}

int	execute(t_execline *execl)
{
	if (has_to_front_exec(execl))
		return (execute_front(execl));
	launch_execution(execl);
	close_pipes(execl);
	close_herdocs_files_fds(execl);
	wait_pids(execl->first_block, execl->shell);
	return (1);
}
