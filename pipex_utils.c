/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:59:56 by laoubaid          #+#    #+#             */
/*   Updated: 2024/01/17 16:00:00 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	if (!s1)
		return (-1);
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strdup(const char *str)
{
	int		len;
	int		i;
	char	*ptr;

	i = 0;
	len = ft_strlen(str);
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (i < len)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[len] = '\0';
	return (ptr);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_access(char *cmd)
{
	if (!(access(cmd, F_OK)))
	{
		if (!(access(cmd, X_OK)))
			return (0);
	}
	return (1);
}

void	fd_free(int **fd, int ncmd, int trash)
{
	int	i;

	trash = 0;
	i = 0;
	while (i < ncmd)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}
