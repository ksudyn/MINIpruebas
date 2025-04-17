/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:07:42 by ksudyn            #+#    #+#             */
/*   Updated: 2025/03/11 16:54:14 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
// rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history
#include <readline/readline.h>
#include <readline/history.h>
// signal, sigaction
#include <signal.h>


typedef struct t_list
{
    char            *variable;   // Nombre de la variable (ej. "PATH")
    char            *content;    // Valor de la variable (ej. "/usr/bin")
    char            *cmd_path;  // NULL             //  /usr/bin/cat
    char            **cmd_arg;  // NULL             // infile | < | cat | -e
    char            *cmd_name;  // NULL             // cat
    int             order;       // Posición en orden alfabético
	struct t_list	*next;
	struct t_list	*prev;
}					t_list;


typedef struct s_mini
{
    t_list   *first_node;  // Apunta al primer nodo de la lista de variables de entorno
    t_list   *node_inter;        // Iterador temporal para recorrer la lista
    int     total_nodes;    // Número total de variables en la lista
}   t_mini;

typedef struct s_shell
{
    int last_exit_status;
} t_shell;
// last_exit_status: guarda el código de salida del último comando ejecutado.
// Se usa en las funciones de manejo de señales para recordar el estado de salida

void	execute_command(t_mini *mini, char **args);
char	*ft_get_path_command(char **command, t_mini *mini);
char	*ft_check_command(char **path_list, char *command);
char **env_list_to_array(t_mini *mini);
char *build_env_string(t_list *node);
void	free_split(char **split);
void	free_path_list(char **path_list);

////...........////BUILTINS
void ft_cd(char **args);
void	init_env_list(t_mini *mini, char **envp);
void	free_env_list(t_mini *mini);
void	ft_echo(char **args);
int ft_env(char **args, t_mini *mini);
int ft_exit(char **exit_args);
int ft_export(char **args, t_mini *mini);
void ft_pwd(void);
int ft_unset(t_mini *mini, char **args);
void execute_builtins(t_mini *mini, char **args);
int	is_builtin(char *cmd);

void ft_lstadd_back(t_list **lst, t_list *new);
int	ft_lstsize_mini(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
t_list *ft_lstnew(void *content);

t_list	*new_doble_node(char *token);
int	node_to_end(t_list **list, t_list *insert);
////...........////CTRLS
void ctrls(int is_child);
void ctrl_minishell(int signal, t_shell *shell);
void ctrl_child(int signal, t_shell *shell);

#endif
