/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalmahth <lalmahth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 21:03:25 by lalmahth          #+#    #+#             */
/*   Updated: 2025/08/29 21:03:26 by lalmahth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_temp_token(char **temp_token, int t, char **tokens)
{
	*temp_token = malloc(1000);
	if (!*temp_token)
	{
		tokens[t] = NULL;
		return (-1);
	}
	return (1);
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

static char	*fill_word(char const *s, char c, int start)
{
	char	*word;
	int		end;
	int		i;

	end = start;
	while (s[end] != c && s[end] != '\0')
		end++;
	word = malloc((end - start) + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

static void	*free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		words;
	int		i;
	int		j;

	words = count_words(s, c);
	arr = malloc((words + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	j = 0;
	arr[words] = NULL;
	while (i < words)
	{
		while (s[j] == c && s[j] != '\0')
			j++;
		arr[i] = fill_word(s, c, j);
		if (!arr[i])
			return (free_arr(arr));
		while (s[j] != c && s[j] != '\0')
			j++;
		i++;
	}
	return (arr);
}
