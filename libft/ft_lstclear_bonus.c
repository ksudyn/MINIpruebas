/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:11:11 by ksudyn            #+#    #+#             */
/*   Updated: 2024/10/11 15:26:34 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_node **lst, void (*del)(void*))
{
	if (*lst == NULL)
		return ;
	del((*lst)->content);
	ft_lstclear(&((*lst)->next), del);
	free (*lst);
	*lst = NULL;
	*lst = NULL;
}
