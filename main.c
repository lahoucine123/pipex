/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 11:14:53 by laoubaid          #+#    #+#             */
/*   Updated: 2024/01/16 16:26:13 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	arg_error(void)
{
	write(2, "Arguments not set correctly!\n", 29);
	write(2, "Usage: [in_file] [cmd1] [cmd2] [out_file]...\n", 45);
	exit (2);
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
		return (write(2, av[1], ft_strlen(av[1])), perror(" "), exit(1), 1);
	args = malloc((ncmd) * sizeof(char **));
	while (i < ncmd)
	{
		args[i] = ft_split(av[i + 2], ' ');
		path(args + (i++), ev[getpath(ev)]);
	}
	if (ft_pipex(fd, ncmd, args, ev) == 0)
		ft_free_cmd(args);
	return (0);
}

char	*ft_getstr(char *limiter)
{
	char	*line;
	char	*str;

	line = NULL;
	str = NULL;
	while (ft_strncmp(line, limiter, ft_strlen(line) - 1) != 0)
	{
		str = ft_strjoinpro(str, line);
		free(line);
		line = get_next_line(0);
	}
	return (str);
}

int	main(int ac, char **av, char **ev)
{
	if (ac != 5)
		arg_error();
	ft_multi_pipe(ac, av, ev);
	return (0);
}
