/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:12:07 by maghumya          #+#    #+#             */
/*   Updated: 2025/04/15 20:23:51 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
}			t_cmd;

# define EXIT_CMD_NOT_FOUND 127

void		handle_error(char *message);
int			input_handler(char **argv);
int			output_handler(char **argv, int argc);
char		*command_handler(char *cmd, char **envp);

char		**parse_path(char **envp);
void		free_split(char **split);

void		exec_command(int fd_in, int fd_out, char *cmd, char **envp);
void		make_pipe(int argc, char **argv, char **envp);
void		fork_cmd1(int pipefd[2], char **argv, char **envp);
pid_t		fork_cmd2(int pipefd[2], int argc, char **argv, char **envp);

#endif