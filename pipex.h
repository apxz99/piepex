/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarayapa <sarayapa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 09:02:09 by sarayapa          #+#    #+#             */
/*   Updated: 2025/12/26 09:58:38 by sarayapa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>

typedef enum e_pipex_errno
{
	PATH,
	PERMISSION,
	COMMAND
}	t_pipex_errno;

typedef struct s_pipex
{
	char	**av;
	int		pid[2];
	int		pipefd[2];
	int		infile;
	int		outfile;
	int		status;
	char	**envp;
	char	**cmd1;
	char	**cmd2;
	char	*tmp;
	int		i;
	char	**path;
	char	*full_path;
	int		error_status;
	int		pid_check;
	int		exit_status;
}	t_pipex;

void	*ft_calloc(size_t n, size_t size);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
char	*find_envpath_for_cmd(char *cmd, t_pipex *px);
void	ft_free_tab(char **tab);
void	ft_putstr_fd(char *str, int fd);
char	**format_argv(char *av, t_pipex *px);
char	*find_envpath_for_cmd(char *cmd, t_pipex *px);
void	error_exit(char *exit_name, int errno, int code);
char	*ft_strrchr(const char *s, int c);

#endif