/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarayapa <sarayapa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 09:00:14 by sarayapa          #+#    #+#             */
/*   Updated: 2025/12/26 10:15:07 by sarayapa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*find_envpath_for_cmd(char *cmd, t_pipex *px)
{
	if (!cmd)
		return (NULL);
	px->i = 0;
	while (px->envp[px->i] && ft_strncmp(px->envp[px->i], "PATH=", 5) != 0)
		px->i++;
	if (!px->envp[px->i])
		return (NULL);
	px->path = ft_split(px->envp[px->i] + 5, ':');
	if (!px->path)
		return (NULL);
	px->i = -1;
	while (px->path[++px->i])
	{
		px->tmp = ft_strjoin(px->path[px->i], "/");
		px->full_path = ft_strjoin(px->tmp, cmd);
		free(px->tmp);
		if (access(px->full_path, F_OK) == 0 || access(px->full_path, X_OK) == 0)
			return (ft_free_tab(px->path), px->full_path);
		free(px->full_path);
	}
	ft_free_tab(px->path);
	return (NULL);
}

char	**format_argv(char *av, t_pipex *px)
{
	char	**av_formated;
	char	*temp;

	if (!av || av[0] == '\0')
		return (NULL);
	av_formated = ft_split(av, ' ');
	if (!av_formated || !av_formated[0])
	{
		error_exit(NULL, COMMAND, 127);
		return (ft_free_tab(av_formated), NULL);
	}
	if(ft_strrchr(av, '/'))
	{
		if (access(av_formated[0], F_OK) == 0 && access(av_formated[0], X_OK) == 0)
			return (av_formated);
		else if (access(av_formated[0], F_OK) == 0 && access(av_formated[0], X_OK) != 0)
			error_exit(av_formated[0], PERMISSION, 126);
		error_exit(av_formated[0], PATH, 127);
	}
	temp = find_envpath_for_cmd(av_formated[0], px);
	if (!temp)
	{
		error_exit(av_formated[0], COMMAND, 127);
		return (ft_free_tab(av_formated), NULL);
	}
	free(av_formated[0]);
	av_formated[0] = temp;
	return (av_formated);
}

void	do_command_1(t_pipex *px)
{
	px->infile = open(px->av[1], O_RDONLY);
	if (px->infile == -1)
	{
		if (access(px->av[1], F_OK) == 0)
			error_exit(px->av[1], PERMISSION, 126);
		error_exit(px->av[1], PATH, 126);
	}
	px->cmd1 = format_argv(px->av[2], px);
	dup2(px->infile, STDIN_FILENO);
	dup2(px->pipefd[1], STDOUT_FILENO);
	close(px->pipefd[0]);
	close(px->pipefd[1]);
	close(px->infile);
	execve(px->cmd1[0], px->cmd1, px->envp);
	perror(px->cmd1[0]);
	ft_free_tab(px->cmd1);
	exit(127);
}

void	do_command_2(t_pipex *px)
{
	px->outfile = open(px->av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (px->outfile == -1)
	{
		if (access(px->av[4], W_OK) != 0)
			error_exit(px->av[4], PERMISSION, 1);
		error_exit(px->av[4], PATH, 1);
	}
	px->cmd2 = format_argv(px->av[3], px);
	dup2(px->pipefd[0], STDIN_FILENO);
	dup2(px->outfile, STDOUT_FILENO);
	close(px->pipefd[0]);
	close(px->pipefd[1]);
	close(px->outfile);
	execve(px->cmd2[0], px->cmd2, px->envp);
	perror(px->cmd2[0]);
	ft_free_tab(px->cmd2);
	exit(127);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	px;

	px.av = av;
	px.envp = envp;

	if (ac != 5)
		return (ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2), 0);
	if (pipe(px.pipefd) == -1)
		return (0);
	px.pid[0] = fork();
	if (px.pid[0] == 0)
		do_command_1(&px);
	px.pid[1] = fork();
	if (px.pid[1] == 0)
		do_command_2(&px);
	close(px.pipefd[0]);
	close(px.pipefd[1]);
	px.pid_check = wait(&px.status);
	while (px.pid_check > 0)
	{
		px.pid_check = wait(&px.status);
		if (px.pid_check == px.pid[1])
			px.exit_status = WEXITSTATUS(px.status);
	}
	return(px.exit_status);
}
