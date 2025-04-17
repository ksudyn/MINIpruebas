/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:31:45 by ksudyn            #+#    #+#             */
/*   Updated: 2025/03/12 15:31:47 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
# include "../../libft/libft.h"

//UTILS PARA ESTAS FUNCIONES

t_list	*env_new(char *env_var)
{
	t_list	*new_node;
	int		equal_pos;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	equal_pos = 0;
	while (env_var[equal_pos] && env_var[equal_pos] != '=')
		equal_pos++;

	new_node->variable = ft_strndup(env_var, equal_pos);
	if (env_var[equal_pos] == '=')
		new_node->content = ft_strdup(&env_var[equal_pos + 1]);
	else
		new_node->content = NULL;

	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}


//INICIO DE FUNCIONES DE ENV.C

int ft_env(char **args, t_mini *mini)
{
    t_list *temp;

    // Verifica que no se pasen argumentos a env
    if (args[1])
    {
        printf("minishell: env: Args not allowed\n");
        return (1);
    }

    temp = mini->first_node;
    while (temp)
    {
        if (temp->variable && temp->content)
        {
            printf("%s=%s\n", temp->variable, temp->content);
        }
        else
        {
            printf("Error: Invalid environment variable or content in node\n");
        }
        temp = temp->next;
    }
	printf("se ha usado mi env\n");
    return (0);
}


void	free_env(t_mini *mini)
{
	t_list	*temp;
	t_list	*next_node;

	temp = mini->first_node;
	while (temp)
	{
		next_node = temp->next;
		free(temp->variable);
		free(temp->content);
		free(temp);
		temp = next_node;
	}
	mini->first_node = NULL;
}

/*
int main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	(void)argc;
	(void)argv;
	init_env(envp, &mini);
	ft_built_env(NULL, &mini);
    printf("Llega hasta el fuincla del printf, el fallo esta fuera de estas funciones\n");
	free_env(&mini);
	return (0);
}*/
