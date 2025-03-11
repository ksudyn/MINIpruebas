/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:32:24 by ksudyn            #+#    #+#             */
/*   Updated: 2024/10/10 17:35:35 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_node	*ft_lstnew(void *content)
{
	t_node	*list;

	list = (t_node *) malloc(sizeof(t_node));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}
