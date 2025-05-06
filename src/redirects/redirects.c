/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:09:10 by ksudyn            #+#    #+#             */
/*   Updated: 2025/04/23 16:09:14 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Cuando usas redirecciones (<, >),
// lo que estás haciendo es cambiar el flujo de entrada/salida del comando,
// y eso se aplica a cualquier comando, no solo a cat, grep o echo.

// Redirección de salida (>)
void	redir_outf(t_list *node_redir, t_execution *inf_exec, t_mini *mini)
{
	if (inf_exec->outf_pipe < 0 || inf_exec->inf_pipe < 0)
		return ;
	if (inf_exec->outf_pipe != 1)
		close(inf_exec->outf_pipe);
	inf_exec->outf_pipe = open(node_redir->content, O_RDWR | O_CREAT | O_TRUNC,
			0777);
	if (inf_exec->outf_pipe < 0)
	{
		printf("minishell: %s: Permission denied\n", node_redir->content);
		mini->last_exit_status = 1;
	}
}
// ejmplo basico
// echo hola > salida.txt
// En vez de que echo imprima en pantalla (stdout = fd 1),lo hará en el archivo salida.txt.

// Redirección de entrada (<)
void	redir_inf(t_list *node_redir, t_execution *inf_exec, t_mini *mini)
{
	if (inf_exec->inf_pipe < 0 || inf_exec->outf_pipe < 0)
		return ;
	if (inf_exec->inf_pipe != 0)
		close(inf_exec->inf_pipe);
	inf_exec->inf_pipe = open(node_redir->content, O_RDONLY);
	if (inf_exec->inf_pipe < 0)
	{
		printf("minishell: %s: No such file or directory\n",
			node_redir->content);
		mini->last_exit_status = 1;
	}
}
// ejemplo basico
// cat < archivo.txt
// esto hara un cat en terminal de archivo.txt

// Redirección de salida con append (>>)
void	redir_append(t_list *node_redir, t_execution *inf_exec, t_mini *mini)
{
	if (inf_exec->outf_pipe < 0 || inf_exec->inf_pipe < 0)
		return ;
	if (inf_exec->outf_pipe != 1)
		close(inf_exec->outf_pipe);
	inf_exec->outf_pipe = open(node_redir->content,
			O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (inf_exec->outf_pipe < 0)
	{
		printf("minishell: %s: Permission denied\n", node_redir->content);
		mini->last_exit_status = 1;
	}
}
//>> añade al final del archivo (lo conserva).>> añade al final del archivo (lo conserva).
// ejemplo basico
// echo "Primera línea" > archivo.txt
// echo "Segunda línea" >> archivo.txt
// Primera línea
// Segunda línea

// Heredoc (<<)
void	heredoc(int fd, t_execution *inf_exec, t_mini *mini)
{
	mini->n_here_docs++;
	if (inf_exec->inf_pipe < 0 || inf_exec->outf_pipe < 0)
	{
		close(fd);
		return ;
	}
	if (inf_exec->inf_pipe != 0)
		close(inf_exec->inf_pipe);
	inf_exec->inf_pipe = fd;
	if (inf_exec->inf_pipe < 0)
	{
		printf("minishell: Error opening here_doc\n");
		mini->last_exit_status = 1;
	}
}
// Te permite escribir varias líneas de texto directamente en la terminal,
// como entrada simulada desde un archivo

// ejemplo basico
// cat << FIN
// hola
// esto es una prueba
// FIN
// escribe por terminal

// ejemplo 2
// grep "prueba" << EOF
// hola
// esto es una prueba
// EOF
// al escribir EOF te escribe la palabra entre "" si la hay

// Comunicación entre procesos con |
void	ft_pipe(t_execution *inf_exec)
{
	int	pipe_fds[2];

	pipe(pipe_fds);
	if (inf_exec->outf_pipe == 1)
		inf_exec->outf_pipe = pipe_fds[1];
	else
		close(pipe_fds[1]);
	// Si este comando no tiene ya una redirección de salida,se le asigna la escritura del pipe.
	inf_exec = inf_exec->next;
	// Nos movemos al siguiente comando.
	if (inf_exec->inf_pipe == 0)
		inf_exec->inf_pipe = pipe_fds[0];
	else
		close(pipe_fds[0]);
	// Si el siguiente comando no tiene redirección de entrada,
	// se le asigna el extremo de lectura del pipe.
}
// Sí, cuando encuentras un |, esta función conecta:
//  comando_antes_del_pipe → escribe al pipe
//  comando_despues_del_pipe → lee del pipe
// Y lo hace sin ejecutar nada aún. Solo prepara los file descriptors
//(inf_pipe, outf_pipe) para que luego tú los uses con dup2() cuando hagas fork()
// y ejecutes el comando.

// cat archivo.txt | grep hola | sort | head -n 1
// Abre y muestra el contenido del archivo archivo.txt.
// Filtra solo las líneas que contienen la palabra "hola".
// Ordena alfabéticamente las líneas anteriores.
// Muestra solo la primera línea de ese resultado ordenado.
