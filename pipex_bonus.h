/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 18:58:18 by laoubaid          #+#    #+#             */
/*   Updated: 2024/01/17 16:16:01 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 6
# endif

char	*ft_strjoin(char *s1, char *s2);
void	ft_bzero(void *p, int n);
int		ft_strlen(const char *str);
int		check(char *p);
int		cal_len(char *p);
char	*get_save(char *str, char *save);
char	*get_lin(char *str);
char	*get_next_line(int fd);
int		get_next(int fd, char **str, char **line);

int		ft_strncmp(const char *s1, const char *s2, int n);
char	*ft_strjoinpro(char *s1, char *s2);
char	**ft_free(char **ptr);
char	**ft_split(char const *s, char c);
int		path(char ***p, char *ev);
int		ft_access(char *cmd);
char	**ft_split_path(char const *s, char c);
char	**ft_free_path(char **ptr);
char	*ft_strdup(const char *str);
int		getpath(char **ev);
int		ft_pipex(int files[2], int ncmd, char ***cmd, char **ev);
int		ftclose(int **fd, int n);
int		**fdpipe(int n);
int		handle_cmd(int *fdin, int *fdout, char **cmd, char **ev);
void	fd_free(int **fd, int ncmd, int trash);
int		ft_free_cmd(char ***cmd);

#endif
