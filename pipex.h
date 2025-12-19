/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarayapa <sarayapa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 09:02:09 by sarayapa          #+#    #+#             */
/*   Updated: 2025/12/19 10:57:59 by sarayapa         ###   ########.fr       */
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
}	t_pipex;

void	*ft_calloc(size_t n, size_t size);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
char	*get_cmd_for_envpath(char *cmd, t_pipex *px);
void	ft_free_tab(char **tab);

#endif