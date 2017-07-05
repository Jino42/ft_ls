/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 11:53:16 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/07/05 22:30:26 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ls_free_env(t_env *e)
{
	ls_free_temp(&e->temp);
	ls_free_temp(&e->not_here);
	ls_free_elem(&e->file);
	ls_free_elem(&e->temp_dir);
	ls_free_elem(&e->dir);
}

int			main(int argc, char **argv)
{
	t_env	e;
	int		i;

	ft_bzero(&e, sizeof(t_env));
	if (!(pars_arg(&e, argc, argv, &i)))
		return (0);
	ls_recup_file(&e, 1, e.temp);
	ls_print(&e, e.file, 1);
	if (!(ls_loop(&e)))
	{
		ft_putstr_fd("Error ?\n", 2);
		return (0);
	}
	if (e.not_here)
		print_not_here(&e);
	ls_free_env(&e);
	return (1);
}
