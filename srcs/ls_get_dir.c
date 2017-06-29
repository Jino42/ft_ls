/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 07:28:53 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/29 11:23:17 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		ls_add_to_list(t_env *e, t_elem *elem, struct dirent *dir)
{
	char			*temp;

	if (!(e->flag & FLAG_A) && dir->d_name[0] == '.')
		return (0);
	temp = ft_sprintf("%s/%s", elem->path, dir->d_name);
	ft_lstinsert_alphabet(&e->temp, ft_lstnew(temp, ft_strlen(temp) + 1),
					e->flag & FLAG_RV);
	ft_strdel(&temp);
	return (1);
}

int				ls_get_dir(t_env *e, t_elem *elem)
{
	void			*ptr;
	struct dirent	*dir;

	(void)e;
	ptr = opendir(elem->path);
	if (!ptr)
		return (0);
	while ((dir = readdir(ptr)))
		ls_add_to_list(e, elem, dir);
	closedir(ptr);
	return (1);
}
