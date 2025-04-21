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

////...........////BUILTINS
//cd.c
int cd_argument(char *path);
void ft_cd(char **args);
//cpy_envp.c
t_list	*create_env_node(char *var, char *value);
void	add_env_var(t_mini *mini, char *var, char *value);
void	init_env_list(t_mini *mini, char **envp);
void	free_env_list(t_mini *mini);
//echo.c
void	ft_echo(char **args);
//env.c
int ft_env(char **args, t_mini *mini);
//execute_command.c
void	execute_command(t_mini *mini, char **args);
char	*ft_get_path_command(char **command, t_mini *mini);
char	*ft_check_command(char **path_list, char *command);
char **env_list_to_array(t_mini *mini);
char *build_env_string(t_list *node);
void	free_path_list(char **path_list);
//exit.c
int check_long_number(char *str);
int transform_number(char *str, long long *result);
int final_numbers(char *str, long long *result);
int multiple_args(char **exit_args, int argc);
int ft_exit(char **exit_args);
//export.c
int is_valid_variable(char *var);
void add_or_update_variable(t_mini *mini, char *var, char *value);
void nodes_order(t_mini *mini);
void print_export_list(t_mini *mini);
int export_args(char **args, t_mini *mini);
int ft_export(char **args, t_mini *mini);
//pwd.c
void previous_pwd(void);
void new_pwd(char *new_path);
void ft_pwd(void);
//unset.c
int ft_unset_env(t_mini *mini, char *variable);
int process_unset_argument(t_mini *mini, char *arg);
int ft_unset(t_mini *mini, char **args);
//utils.c
int	ft_lstsize_mini(t_list *lst);
t_list	*new_node_export(char *var, char *value);
int	node_to_end(t_list **list, t_list *insert);
void execute_builtins(t_mini *mini, char **args);
int	is_builtin(char *cmd);

////...........////CTRLS
//ctrls.c
void ctrls(int is_child);
void ctrl_minishell(int signal, t_shell *shell);
void ctrl_child(int signal, t_shell *shell);

#endif
