/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:12:07 by maghumya          #+#    #+#             */
/*   Updated: 2025/04/21 16:36:19 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
}			t_cmd;

typedef struct s_params
{
	int		argc;
	char	**argv;
	char	**envp;
	int		cmd_count;
	int		**pipefds;
	int		pipe_count;
}			t_params;

# define EXIT_CMD_NOT_FOUND 127

void		handle_error(char *message);
int			input_handler(char **argv);
int			output_handler(char **argv, int argc);
char		*command_handler(char *cmd, char **envp);
int			heredoc_handler(char *limiter);

char		**parse_path(char **envp);
void		free_split(char **split);

int			exec_command(int fd_in, int fd_out, char *cmd, char **envp);
// void		make_pipe(int argc, char **argv, char **envp);
void		fork_cmd1(int pipefd[2], t_params *params);
pid_t		fork_cmd2(int pipefd[2], t_params *params);
void		fork_cmd_mid(int pipefd1[2], int pipefd2[2], char *cmd,
				t_params *params);
void		fork_heredoc(int pipefd[2], int heredoc_fd, t_params *params);

void		make_pipe_bonus(t_params *params);
void		make_pipe_mid(int **pipefds, t_params *params);
int			**alloc_pipes(int cmd_count);
void		free_pipes(int **arr);

void		puterr(char *filename, int _errornum);
int			get_cmd_count(int argc, char **argv);

#endif