/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalmahth <lalmahth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 20:57:53 by lalmahth          #+#    #+#             */
/*   Updated: 2025/08/29 21:11:47 by lalmahth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long int	ft_return_nbr(char *str, int i, int sign)
{
	long int	nbr;

	nbr = 0;
	while ((str[i] != '\0') && (ft_isdigit(str[i]) == 1))
	{
		nbr *= 10;
		nbr += str[i] - '0';
		i++;
	}
	if (sign == '-')
		return ((nbr * -1));
	else
		return (nbr);
}

int	ft_isspace(int c)
{
	if ((c == '\f') || (c == '\n') || (c == '\r') || (c == '\t') || (c == '\v')
		|| (c == ' '))
		return (1);
	return (0);
}

static int	ft_one(const char *big, const char *little, size_t i, size_t len)
{
	size_t	j;

	j = 0;
	while (big[i] != '\0' && little[j] != '\0' && big[i] == little[j]
		&& i < len)
	{
		i++;
		j++;
	}
	return (little[j] == '\0');
}

int	ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!big && !little)
		return (0);
	if (*little == '\0')
		return (0);
	while (i < len && big[i])
	{
		j = 0;
		if (big[i] == little[j])
		{
			if (ft_one(big, little, i, len))
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
