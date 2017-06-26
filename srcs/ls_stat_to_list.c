/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_stat_to_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 08:02:53 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/26 09:35:41 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static size_t	find_last_slash(t_elem *elem)
{
	int i;

	i = ft_strlen(elem->path);
	while (i)
	{
		if (elem->path[i] == '/' && elem->path[i - 1] != '\\')
			return (i + 1);
		i--;
	}
	return (i);
}

t_list			*ls_stat_to_list(t_env *e, struct stat buff, char *path)
{
	t_elem			elem;
	struct passwd	*passwd;
	struct group	*group;
	t_list			*ret;

	(void)e;
	passwd = NULL;
	group = NULL;
	ft_bzero(&elem, sizeof(t_elem));
	ft_memset(&elem.mode, '-', sizeof(char) * 10);
	elem.path = path;
	ls_type_and_file_right(&elem, buff.st_mode, &buff);
	elem.ind_curf = find_last_slash(&elem);
	elem.size = buff.st_size;
	elem.atime = buff.st_atime;
	elem.nlink = buff.st_nlink;
	elem.blocks = buff.st_blocks;
	passwd = getpwuid(buff.st_uid);
	group = getgrgid(buff.st_gid);
	if (passwd)
		elem.p_name = ft_strdup(passwd->pw_name);
	if (group)
		elem.g_name = ft_strdup(group->gr_name);
	ret = ft_lstnew(&elem, sizeof(t_elem));
	return (ret);
}
