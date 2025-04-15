/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:50:21 by maghumya          #+#    #+#             */
/*   Updated: 2025/04/15 21:25:07 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line/get_next_line.h"
#include "./pipex.h"

int		heredoc_handler(char *limiter);
int		**alloc_pipes(int cmd_count);

void	fork_cmd_mid(int pipefd1[2], int pipefd2[2], char *cmd, char *envp[]);
void	make_pipe_bonus(int argc, char **argv, char **envp);