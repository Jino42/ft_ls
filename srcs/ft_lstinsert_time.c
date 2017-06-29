/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert_time.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 00:54:07 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/29 11:06:02 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	init(t_list **lst, t_list **past, t_list **cur, t_list *new)
{
	*past = NULL;
	*cur = *lst;
	if (*lst == NULL)
		*lst = new;
}

static void	reverse_on(t_list **lst, t_list *new, t_list *past, t_list *cur)
{
	new->next = cur;
	if (past)
		past->next = new;
	else
		*lst = new;
}

void		ft_lstinsert_time(t_list **lst, t_list *new, int reverse)
{
	t_list *past;
	t_list *cur;

	if (lst == NULL || new == NULL)
		return ;
	init(lst, &past, &cur, new);
	while (cur)
	{
		if (!reverse && ((t_elem*)cur->content)->mtime -
										((t_elem*)new->content)->mtime < 0)
			return (reverse_on(lst, new, past, cur));
		else if (reverse && ((t_elem*)cur->content)->mtime -
										((t_elem*)new->content)->mtime > 0)
			return (reverse_on(lst, new, past, cur));
		past = cur;
		cur = cur->next;
	}
	if (past)
		past->next = new;
}
