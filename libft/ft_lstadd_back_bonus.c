/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:00:45 by ksudyn            #+#    #+#             */
/*   Updated: 2024/10/10 19:19:23 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_node **lst, t_node *new)
{
	t_node	*last;

	if (new == NULL)
		return ;
	if (*lst)
	{
		last = *lst;
		while (last -> next != NULL)
			last = last -> next;
		last -> next = new;
	}
	else
	{
		*lst = new;
	}
}
