/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_recup_file_from_arg.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 23:47:55 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/30 11:20:10 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ls_recup_current_dir(t_env *e)
{
	struct stat	buff;
	t_list		*ret;

	ret = NULL;
	if (!e->file && !e->dir && !e->temp)
	{
		stat(("."), &buff);
		ret = ls_stat_to_list(e, buff, ft_strdup("."));
		ft_lstinsert(&e->dir, ret);
	}
}

static void		ls_put_in_list(t_env *e, struct stat buff, t_list *save)
{
	t_list	*ret;

	ret = NULL;
	ret = ls_stat_to_list(e, buff, ft_strdup((char*)save->content));
	if (buff.st_mode & S_IFDIR)
	{
		if (e->flag & FLAG_R || e->cur_dir)
		{
			ft_lstadd(&e->temp_dir, ret);
			ret = ls_stat_to_list(e, buff, ft_strdup((char*)save->content));
		}
		if (e->flag & FLAG_T)
			ft_lstinsert_time(&e->file, ret, e->flag & FLAG_RV);
		else
			ft_lstinsert(&e->file, ret);
	}
	else
	{
		if (e->flag & FLAG_T)
			ft_lstinsert_time(&e->file, ret, e->flag & FLAG_RV);
		else
			ft_lstinsert(&e->file, ret);
	}
	save = ft_lst_remove(&e->temp, save);
	ft_memdel((void**)&save);
}

static void		ls_initialisation_list(t_env *e, struct stat buff, t_list *save)
{
	t_list	*ret;

	ret = NULL;
	ret = ls_stat_to_list(e, buff, ft_strdup((char*)save->content));
//	save = ft_lst_remove(&e->temp, save);
//	ft_memdel((void**)&save);
	if (buff.st_mode & S_IFDIR)
	{
		if (e->flag & FLAG_T)
			ft_lstinsert_time(&e->dir, ret, e->flag & FLAG_RV);
		else
			ft_lstinsert(&e->dir, ret);
	}
	else
	{
		if (e->flag & FLAG_T)
			ft_lstinsert_time(&e->file, ret, e->flag & FLAG_RV);
		else
			ft_lstinsert(&e->file, ret);
	}
}

int				ls_recup_file(t_env *e, int init)
{
	t_list		*lst;
	t_list		*save;
	struct stat	buff;

	lst = e->temp;
	if (init)
		ls_recup_current_dir(e);
	while (lst)
	{
		ft_bzero(&buff, sizeof(struct stat));
		save = lst;
		lst = lst->next;
		if (stat(((char*)save->content), &buff) == -1 &&
									lstat(((char*)save->content), &buff) == -1)
			ft_lstinsert_alphabet(&e->not_here, ft_lst_remove(&e->temp, save), 0);
		else
		{
			if (init)
				ls_initialisation_list(e, buff, save);
			else
				ls_put_in_list(e, buff, save);
		}
	}
	ls_free_temp(&e->temp);
	return (1);
}
