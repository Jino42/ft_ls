/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 17:18:15 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/03 04:56:19 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int				ft_printf(char *str, ...)
{
	t_option	option;

	ft_bzero(&option, sizeof(t_option));
	option.len = 0;
	if (!str)
		return (0);
	if (str[0] == '%' && str[1] == '\0')
		return (0);
	option.b = 0;
	ft_bzero(option.buffer, BUFF_SIZE_P);
	option.fd = 1;
	va_start(option.ap, str);
	printf_loop(str, &option);
	va_end(option.ap);
	if (option.buffer[0] != '\0')
		write(1, &option.buffer, option.b);
	return (option.len);
}

int				ft_dprintf(int fd, char *str, ...)
{
	t_option	option;

	ft_bzero(&option, sizeof(t_option));
	if (!str || fd < 0)
		return (0);
	if (str[0] == '%' && str[1] == '\0')
		return (0);
	ft_bzero(option.buffer, BUFF_SIZE_P);
	option.fd = fd;
	va_start(option.ap, str);
	printf_loop(str, &option);
	va_end(option.ap);
	if (option.buffer[0] != '\0')
		write(fd, &option.buffer, option.b);
	return (option.len);
}

char			*ft_sprintf(char *str, ...)
{
	t_option	option;

	ft_bzero(&option, sizeof(t_option));
	option.len = 0;
	if (!str)
		return (0);
	if (str[0] == '%' && str[1] == '\0')
		return (0);
	option.b = 0;
	ft_bzero(option.buffer, BUFF_SIZE_P);
	if (!(option.sbuffer = (char *)ft_memalloc(sizeof(char)
							* BUFF_SIZE_P + 1)))
		return (NULL);
	option.flag = FLAG_S;
	va_start(option.ap, str);
	printf_loop(str, &option);
	va_end(option.ap);
	return (option.sbuffer);
}

int				ft_bprintf(int last, char *str, ...)
{
	static t_option	option;

	if (last == 1)
	{
		write(1, &option.buffer, option.b);
		return (option.b);
	}
	option.sub_word = 0;
	option.flag = 0;
	if (!str)
		return (0);
	if (str[0] == '%' && str[1] == '\0')
		return (0);
	option.fd = 1;
	va_start(option.ap, str);
	printf_loop(str, &option);
	va_end(option.ap);
	return (option.len);
}
