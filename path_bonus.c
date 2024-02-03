/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:45:58 by laoubaid          #+#    #+#             */
/*   Updated: 2024/01/06 12:42:06 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	getpath(char **ev)
{
	int	i;

	i = 0;
	while (ev[i])
	{
		if (!(ft_strncmp(ev[i], "PATH=", 5)))
			return (i);
		i++;
	}
	write(2, "PATH enviremment not exist!\n", 28);
	exit (1);
}

int	path(char ***p, char *ev)
{
	char	**paths;
	char	*cmd;
	int		i;

	i = 0;
	paths = ft_split_path(&ev[5], ':');
	while (paths[i])
	{
		cmd = ft_strjoinpro(paths[i], (*p)[0]);
		if (!(ft_access(cmd)))
		{
			free((*p)[0]);
			(*p)[0] = cmd;
			ft_free(paths);
			return (0);
		}
		free(cmd);
		i++;
	}
	ft_free(paths);
	return (1);
}
