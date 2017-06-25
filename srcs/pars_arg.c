/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 17:59:18 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/25 10:21:38 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	pars_file(t_env *e, int argc, char **argv, int *i)
{
	t_elem elem;

	ft_bzero(&elem, sizeof(t_elem));
	while (*i < argc)
	{
		ft_lstinsert_alphabet(&e->temp, ft_lstnew(argv[*i], ft_strlen(argv[*i]) + 1));
		(*i)++;
	}
}

static void	pars_flag(t_env *e, int argc, char **argv, int *i)
{
	int	i_in;

	while (*i < argc && argv[*i][0] == '-')
	{
		i_in = 1;
		while (argv[*i][i_in])
		{
			if (argv[*i][i_in] == 'l')
				e->flag |= FLAG_L;
			else if (argv[*i][i_in] == 'R')
				e->flag |= FLAG_R;
			else if (argv[*i][i_in] == 'a')
				e->flag |= FLAG_A;
			else if (argv[*i][i_in] == 't')
				e->flag |= FLAG_T;
			else if (argv[*i][i_in] == 'r')
				e->flag |= FLAG_RV;
			else
				ft_error("usage : ls [-Rlart] [file ...]\n");
			i_in++;
		}
		(*i)++;
	}
}

void		pars_arg(t_env *e, int argc, char **argv, int *i)
{
	*i = 1;
	pars_flag(e, argc, argv, i);
	pars_file(e, argc, argv, i);
}
