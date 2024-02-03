/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 19:19:01 by laoubaid          #+#    #+#             */
/*   Updated: 2024/01/04 09:52:30 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	handle_cmd(int *fdin, int *fdout, char **cmd, char **ev)
{
	int	i;

	i = 0;
	close(fdin[1]);
	close(fdout[0]);
	dup2(fdin[0], STDIN_FILENO);
	dup2(fdout[1], STDOUT_FILENO);
	close(fdin[0]);
	close(fdout[1]);
	execve(cmd[0], cmd, ev);
	if (cmd[0][0] == '/' || cmd[0][0] == '.')
		return (write(2, cmd[0], ft_strlen(cmd[0])), perror(" "), 127);
	write(2, "command not found: ", 19);
	write(2, cmd[0], sizeof(cmd[0]));
	write(2, "\n", 1);
	return (127);
}

int	**fdpipe(int n)
{
	int	i;
	int	**fd;

	i = 0;
	fd = malloc(sizeof(int *) * n);
	while (i < n)
	{
		fd[i] = malloc(2 * sizeof(int));
		i++;
	}
	return (fd);
}

int	ftclose(int **fd, int n, int op)
{
	if (op)
	{
		close(fd[n - 1][1]);
		close(fd[n][0]);
	}
	while (n - 2 >= 0)
	{
		close(fd[n - 2][0]);
		close(fd[n - 2][1]);
		n--;
	}
	return (1);
}

void	ftwait(int **fd, int ncmd)
{
	fd_free(fd, ncmd, 0);
	while (wait(NULL) != -1)
	{
	}
}

int	ft_pipex(int files[2], int ncmd, char ***cmd, char **ev)
{
	int	pid;
	int	**fd;
	int	i;

	i = 0;
	fd = fdpipe(ncmd);
	while (i <= ncmd - 1)
	{
		if (i != ncmd - 1)
			pipe(fd[i]);
		pid = fork();
		if (!pid)
		{
			if (i == 0)
				handle_cmd(files, fd[0], cmd[i], ev);
			else if (i == ncmd - 1)
				handle_cmd(fd[i - 1], files, cmd[i], ev);
			else
				handle_cmd(fd[i - 1], fd[i], cmd[i], ev);
			return (fd_free(fd, ncmd, ft_free_cmd(cmd)), 127);
		}
		close(fd[i++][1]);
	}
	return (ftclose(fd, ncmd, 0), ftwait(fd, ncmd), 0);
}
