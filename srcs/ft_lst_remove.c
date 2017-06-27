/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_remove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 23:46:09 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/27 07:41:32 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list		*ft_lst_remove(t_list **lst, t_list *remove)
{
	t_list *past;

	past = NULL;
	if (lst == NULL || remove == NULL)
		return (NULL);
	while (*lst)
	{
		if (*lst == remove)
		{
			if (past)
				past->next = remove->next;
			else
				*lst = remove->next;
			remove->next = NULL;
			return (remove);
		}
		past = (*lst);
		lst = &(*lst)->next;
	}
	return (NULL);
}
