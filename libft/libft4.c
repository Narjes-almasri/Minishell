/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalmahth <lalmahth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 20:58:14 by lalmahth          #+#    #+#             */
/*   Updated: 2025/08/29 21:11:32 by lalmahth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	len_(int n)
{
	int	i;

	i = 1;
	while (n / 10 != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*to_char(int i, int f, int n, char *s)
{
	int	x;

	while (i >= 0)
	{
		x = n % 10;
		n /= 10;
		s[i] = x + '0';
		i--;
	}
	if (f)
		s[0] = '-';
	return (s);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}

char	*ft_itoa(int n)
{
	char	*s;
	int		i;
	int		f;

	f = 0;
	i = len_(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
		i++;
	s = malloc((i + 1) * sizeof(char));
	if (!s)
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		f = 1;
	}
	s[i] = '\0';
	i--;
	s = to_char(i, f, n, s);
	return (s);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}
