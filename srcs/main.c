/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 11:53:16 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/26 07:43:41 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			main(int argc, char **argv)
{
	t_env	e;
	int		i;

	ft_bzero(&e, sizeof(t_env));
	pars_arg(&e, argc, argv, &i);
	ls_recup_file_from_arg(&e);
	if (!(ls_loop(&e)))
	{
		ft_putstr_fd("Error ?\n", 2);
		return (0);
	}
	ls_free_temp(&e.temp);
	ls_free_temp(&e.not_here);
	ls_free_elem(&e.file);
	ls_free_elem(&e.dir);
//	ft_bzero(&e, sizeof(t_env));
//	while (1);
	return (1);
}
