/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert_alphabet.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 23:39:15 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/26 09:34:58 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ret_dif_ascii(char *str, char *str2)
{
	int i;

	i = 0;
	while (str[i] && str2[i])
	{
		if (str[i] != str2[i])
			return (str[i] - str2[i]);
		i++;
	}
	if (!str[i])
		return (-1);
	else
		return (1);
}

static void	init(t_list **lst, t_list **past, t_list **cur, t_list *new)
{
	*past = NULL;
	*cur = *lst;
	if (*lst == NULL)
		*lst = new;
}

void		ft_lstinsert_alphabet(t_list **lst, t_list *new)
{
	t_list *past;
	t_list *cur;

	if (lst == NULL || new == NULL)
		return ;
	init(lst, &past, &cur, new);
	while (cur)
	{
		if (ret_dif_ascii(((char*)cur->content),
					((char*)new->content)) > 0)
		{
			new->next = cur;
			if (past)
				past->next = new;
			else
				*lst = new;
			return ;
		}
		past = cur;
		cur = cur->next;
	}
	if (past)
		past->next = new;
}
