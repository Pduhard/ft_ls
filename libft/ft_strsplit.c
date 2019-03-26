/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 04:07:41 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/15 05:39:32 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int		len_max(char const *s, char c)
{
	int nb;
	int i;

	nb = 0;
	i = 0;
	if (s)
	{
		while (s[i])
		{
			while (s[i] && s[i] == c)
				i++;
			if (s[i] && s[i] != c)
				nb++;
			while (s[i] && s[i] != c)
				i++;
			if (s[i])
				i++;
		}
	}
	return (nb);
}

static int		cut(char const *s, char c, int i)
{
	int nb;

	nb = 0;
	if (s)
	{
		while (s[i] && s[i] != c)
		{
			nb++;
			i++;
		}
	}
	return (nb);
}

static int		check(char const *s, char c, int i)
{
	if (s)
	{
		while (s[i] && s[i] == c)
			i++;
	}
	return (i);
}

static char		**test(char const *s, char **str, char c, int i)
{
	int y;
	int x;

	y = 0;
	while (s[i])
	{
		x = 0;
		i = check(s, c, i);
		if (!(str[y] = (char*)malloc(sizeof(char) * (cut(s, c, i) + 1))))
			return (NULL);
		while (s[i] != c && s[i])
			str[y][x++] = s[i++];
		i = check(s, c, i);
		str[y][x] = '\0';
		y++;
	}
	str[y] = 0;
	return (str);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**str;
	int		i;

	i = 0;
	i = check(s, c, i);
	if (!(str = (char**)malloc(sizeof(char*) * (len_max(s, c) + 1))))
		return (NULL);
	if (s)
		str = test(s, str, c, i);
	return (str);
}
