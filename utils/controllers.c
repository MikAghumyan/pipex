/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controllers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:51:43 by maghumya          #+#    #+#             */
/*   Updated: 2025/04/12 20:49:45 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exec_command(int fd_in, int fd_out, char *cmd, char **envp)
{
	t_cmd	cmd_;

	if (dup2(fd_in, 0) == -1)
		perror("Can't read");
	if (dup2(fd_out, 1) == -1)
		perror("Can't write %d");
	cmd_.args = ft_split(cmd, ' ');
	if (!cmd_.args)
		return ;
	cmd_.cmd = command_handler(cmd_.args[0], envp);
	if (!cmd_.cmd)
	{
		free(cmd_.args);
		return ;
	}
	if (execve(cmd_.cmd, cmd_.args, envp) == -1)
		perror("Execve failed");
	free(cmd_.args);
	free(cmd_.cmd);
	close(fd_in);
	close(fd_out);
	return ;
}
