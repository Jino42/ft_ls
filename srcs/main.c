/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 11:53:16 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/27 09:46:38 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		print_not_here(t_env *e)
{
	t_list *lst;

	lst = e->not_here;
	while (lst)
	{
		ft_dprintf(2, "ls: %s: No such file or directory\n", (char*)lst->content);
		lst = lst->next;
	}
	ls_free_temp(&e->not_here);
}

int			main(int argc, char **argv)
{
	t_env	e;
	int		i;
//	t_list	*ret;

	ft_bzero(&e, sizeof(t_env));
	pars_arg(&e, argc, argv, &i);
	ls_recup_file(&e, 1);
	ls_print(&e, e.file, 1);
//	if (e.dir)
//		ret = ft_lst_remove_index(&e.dir, 0);
//	if (ret)
//		ls_free_elem(&ret);

	if (!(ls_loop(&e)))
	{
		ft_putstr_fd("Error ?\n", 2);
		return (0);
	}
	///////tmp
	if (e.not_here)
		print_not_here(&e);
	ls_free_temp(&e.temp);
	ls_free_temp(&e.not_here);
	ls_free_elem(&e.file);
	ls_free_elem(&e.dir);
	//	ft_bzero(&e, sizeof(t_env));
	//	while (1);
	return (1);
}
