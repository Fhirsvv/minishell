/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:24:11 by ecortes-          #+#    #+#             */
/*   Updated: 2024/08/28 11:47:24 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_set_in_s(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	i;
	size_t	start;
	size_t	end;

	start = 0;
	i = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_set_in_s(s1[start], set))
		start++;
	while (end > start && ft_set_in_s(s1[end - 1], set))
		end--;
	res = (char *)malloc(end - start + 1);
	if (!res)
		return (NULL);
	while (start < end)
	{
		res[i] = s1[start];
		i++;
		start++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_semi_strtrim(char const *s1, char const *set)
{
	int	len1;
	int	len2;
	char *ret;

	if(!s1 || !set)
		return(NULL);
	ret = NULL;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(set);
	if(ft_strncmp(s1, set, len2) == 0 && len1 >= len2)
		ret = ft_substr(s1,len2, len1 - len2);
	return(ret);
}
/*char	*ft_semi_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	i;
	size_t	start;
	size_t len;

	len = ft_strlen(s1);
	start = 0;
	i = 0;
	while (s1[start] && ft_set_in_s(s1[start], set))
		start++;
	res = (char *)malloc(len - start + 1);
	if (!res)
		return (NULL);
	while (start < len)
	{
		res[i] = s1[start];
		i++;
		start++;
	}
	res[i] = '\0';
	return (res);
}*/
