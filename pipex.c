/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarayapa <sarayapa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:51:59 by sarayapa          #+#    #+#             */
/*   Updated: 2025/12/04 21:23:34 by sarayapa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"
#include <stdio.h>

char **format_argv(char *av, char **envp)
{
	char **av_formated;
	char *temp;

	while (envp[i])
	{
		/* code */
	}

	temp = ft_strjoin("/usr/bin/", av);
	av_formated = ft_split(temp, ' ');
	free(temp);

	return(av_formated);
}
char()
int main(int ac, char **av)
{
	int pipefd[2];
	int infile;
	int outfile;
	int pid_1;
	int pid_2;
	char **args1;
	char **args2;

	if(ac != 5)
		return(0);
	infile = open(av[1], O_RDONLY);
	outfile = open(av[4], O_WRONLY | O_CREAT, 0644 | O_TRUNC);

	if(pipe(pipefd) == -1)
		return (1);

	pid_1 = fork();
	if(pid_1 == 0)//child
	{
		dup2(infile , 0);
		dup2(pipefd[1] , 1); //pipe[1] <- input

		printf("Child : \n");
		args1 = format_argv(av[2]);
		execve(args1[0], args1, NULL);
	}
	pid_2 = fork();
	if(pid_2 == 0)//child
	{
		dup2(pipefd[0] , STDIN_FILENO); //pipe[0] -> output
		dup2(outfile , STDOUT_FILENO);

		printf("Child : \n");
		args2 = format_argv(av[3]);//
		printf("%s\n", args2[0]);
		printf("%s\n", args2[1]);
		execve(args2[0], args2, NULL);
		//execve("/usr/bin/cat", "/usr/bin/cat", environ);
	}
	dup2(infile , STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	(void)infile;
	(void)outfile;
}


/*
./pipex {file1} {cmd1} {cmd2} {file2}

< pipex.c ls | wc -w > txt
☺  make debug && ./pipex input "echo hello" cat output                                                                                                                                                                                                       main ✗

*/