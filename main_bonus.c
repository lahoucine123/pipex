/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:12:41 by laoubaid          #+#    #+#             */
/*   Updated: 2024/01/18 10:12:44 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	arg_error(int opt)
{
	if (opt == 1)
	{
		write(2, "Arguments not set correctly <cmd2+>!\n", 37);
		write(2, "Usage: [in_file] [cmd1] ... [cmdn] [out_file]...\n", 50);
		exit (2);
	}
	else if (opt == 2)
	{
		write(2, "Arguments not set correctly!\n", 29);
		write(2, "Usage: here_doc [limiter] [cmd1] [cmd2] [out_file]...\n", 54);
		exit (2);
	}
}

int	ft_multi_pipe(int ac, char **av, char **ev)
{
	int		fd[2];
	int		i;
	int		ncmd;
	char	***args;

	i = 0;
	ncmd = ac - 3;
	fd[0] = open(av[1], O_RDONLY);
	fd[1] = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd[0] == -1 || fd[1] == -1)
		return (write(2, av[1], ft_strlen(av[1])), perror(" "), 1);
	args = malloc((ncmd + 1) * sizeof(char **));
	while (i < ncmd)
	{
		args[i] = ft_split(av[i + 2], ' ');
		path(args + (i++), ev[getpath(ev)]);
	}
	args[ncmd] = NULL;
	if (ft_pipex(fd, ncmd, args, ev) == 0)
		ft_free_cmd(args);
	free(args);
	return (0);
}

char	*ft_getstr(char *limiter)
{
	char	*line;
	char	*str;
	char	*tmp;

	line = NULL;
	str = NULL;
	while (ft_strncmp(line, limiter, ft_strlen(line)) != 0)
	{
		tmp = str;
		str = ft_strjoinpro(str, line);
		free(tmp);
		free(line);
		write(1, "pipe heredoc> ", 14);
		line = get_next_line(0);
	}
	free(limiter);
	free(line);
	return (str);
}

int	ft_here_doc(int ac, char **av, char ***args, char **ev)
{
	char	*str;
	int		f[2];
	int		**fd;
	int		pid;

	fd = fdpipe(2);
	f[1] = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (f[1] == -1)
		return (perror(""), 1);
	str = ft_getstr(ft_strjoinpro(av[2], "\n"));
	pipe(fd[0]);
	pipe(fd[1]);
	write(fd[0][1], str, ft_strlen(str));
	pid = fork();
	if (pid == 0)
		handle_cmd(fd[0], fd[1], args[0], ev);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0][1]);
		handle_cmd(fd[1], f, args[1], ev);
	}
	free(str);
	return (ftclose(fd, 3), fd_free(fd, ac - 4, 0), wait(NULL), wait(NULL), 0);
}

int	main(int ac, char **av, char **ev)
{
	int		i;
	char	***args;
	int		ncmd;

	ncmd = ac - 3;
	i = 0;
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		if (ac != 6)
			arg_error(2);
		args = malloc((ac - 4) * sizeof(char **));
		while (i < ac - 4)
		{
			args[i] = ft_split(av[i + 3], ' ');
			path(args + i, ev[getpath(ev)]);
			i++;
		}
		ft_here_doc(ac, av, args, ev);
		return (ft_free_cmd(args), free(args), 0);
	}
	if (ac < 5)
		arg_error(1);
	ft_multi_pipe(ac, av, ev);
	return (0);
}
