/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarayapa <sarayapa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:34:59 by sarayapa          #+#    #+#             */
/*   Updated: 2025/12/26 10:07:17 by sarayapa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	error_exit(char *exit_name, int errno, int code)
{

	if(errno == PATH)
		ft_putstr_fd("pipex : No such file or directory: ", 2);
	else if(errno == PERMISSION)
		ft_putstr_fd("pipex : Permission denied :", 2);
	else if(errno == COMMAND)
		ft_putstr_fd("pipex : Command not found: ", 2);
	if(exit_name)
		ft_putstr_fd(exit_name, 2);
	ft_putstr_fd("\n", 2);
	exit(code);
}
