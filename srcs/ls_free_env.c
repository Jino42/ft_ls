/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 23:31:32 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/22 23:38:06 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_free_temp(t_list **lst)
{
	t_list	*save;
	t_list	*cur;

	if (!lst)
		return ;
	cur = *lst;
	while (cur)
	{
		save = cur->next;
		if (cur->content)
			free(cur->content);
		free(cur);
		cur = save;
	}
	*lst = NULL;
}
