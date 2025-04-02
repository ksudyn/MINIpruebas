/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:47:54 by ksudyn            #+#    #+#             */
/*   Updated: 2025/03/31 17:47:58 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history
#include <readline/readline.h>
#include <readline/history.h>
// signal, sigaction
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_shell
{
    int last_exit_status;
} t_shell;
// last_exit_status: guarda el código de salida del último comando ejecutado.
// Se usa en las funciones de manejo de señales para recordar el estado de salida

void ctrl_minishell(int signal, t_shell *shell)
{
    if (signal == SIGINT)
    {
        rl_replace_line("", 0);
        write(1, "\n", 1);
        rl_on_new_line();
        rl_redisplay();
        shell->last_exit_status = 1;
    }
    else if (signal == SIGQUIT)
    {
        rl_on_new_line();
        rl_redisplay();
    }
}
//Maneja Ctrl-C y Ctrl-\ cuando se está en Minishell (interactivo).
//Ctrl-C limpia la línea actual y muestra un nuevo prompt, sin salir del shell.
//Ctrl-\``** simplemente **redibuja el prompt` sin hacer nada más.

void ctrl_child(int signal, t_shell *shell)
{
    if (signal == SIGINT)
        shell->last_exit_status = 130;
    else if (signal == SIGQUIT)
    {
        write(1, "Quit: 3\n", 8);
        shell->last_exit_status = 131;
    }
}
//Ctrl-C (SIGINT) en un hijo:
// No imprime nada.
// Guarda 130 como código de salida (indica que el proceso fue interrumpido).
// Ctrl-\ (SIGQUIT) en un hijo:
// Muestra "Quit: 3" en pantalla.
// Guarda 131 como código de salida.

void	ctrls(int is_child)
{
	struct sigaction	sa;

	if (is_child)
		sa.sa_handler = (void (*)(int))ctrl_child;
	else
		sa.sa_handler = (void (*)(int))ctrl_minishell;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
}
//que este en rojo es normal, funciona bien, es por las señales
//es por que se usa tan poco que el sistema lo detecta como fallo

//MAIN GENERADO POR CHRGPT PARA COMPROBAR

int main(void)
{  // Inicializa la estructura con el estado de salida a 0

    // Configura los manejadores de señales para el proceso principal
    ctrls(0);

    // Bucle principal del minishell
    while (1)
    {
        char *input = readline("minishell> ");
        if (!input)
        {
            printf("exit\n");
            break;  // Sale del shell si el usuario presiona Ctrl-D
        }

        // Si la entrada no está vacía, añade al historial
        if (*input)
            add_history(input);

        free(input);  // Libera la memoria asignada por readline
    }

    return 0;
}