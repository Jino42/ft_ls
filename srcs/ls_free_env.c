/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 23:31:32 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/24 20:10:50 by ntoniolo         ###   ########.fr       */
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

static void	free_elem(t_elem **elem)
{
	if (elem)
	{
		ft_strdel(&(*elem)->path);
		ft_strdel(&(*elem)->g_name);
		ft_strdel(&(*elem)->p_name);
	}
}

void		ls_free_elem(t_list **lst)
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
		{
			free_elem((t_elem**)&cur->content);
			ft_memdel(&cur->content);
		}
		free(cur);
		cur = save;
	}
	*lst = NULL;
}
