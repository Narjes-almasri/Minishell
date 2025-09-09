/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalmahth <lalmahth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 20:56:45 by lalmahth          #+#    #+#             */
/*   Updated: 2025/08/29 21:06:40 by lalmahth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_closing_quote(char *s, int start, char quote_char)
{
	int	i;

	i = start + 1;
	while (s[i] != '\0')
	{
		if (s[i] == quote_char)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

long int	ft_atol(char *str)
{
	int		i;
	char	sign;

	sign = '0';
	i = 0;
	while (str[i] != '\0' && (ft_isspace(str[i]) == 1))
		i++;
	if ((str[i] != '\0') && (str[i] == '+' || str[i] == '-'))
	{
		sign = str[i];
		i++;
	}
	if (ft_isdigit(str[i]) == 0)
		return (9223372036854775807);
	if (ft_strlen((str + i)) > 19)
		return (9223372036854775807);
	if (ft_strlen(str + i) == 19)
	{
		if (ft_strncmp((str + i), "9223372036854775807", 19) > 0)
			return (9223372036854775807);
	}
	return (ft_return_nbr(str, i, sign));
}

int	ft_isdigit(int digit)
{
	if (digit >= '0' && digit <= '9')
		return (1);
	else
		return (0);
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

char	*ft_strstr(char *big, char *little)
{
	size_t	c;
	size_t	size;

	c = 0;
	size = ft_strlen(little);
	if (!big)
	{
		ft_putendl_fd("strstr error: Big doesn't exist", 2);
		return (NULL);
	}
	if (!little)
		return (NULL);
	while (big[c])
	{
		if (ft_strncmp(big + c, little, size) == 0)
			return (big + c);
		c++;
	}
	return (NULL);
}
