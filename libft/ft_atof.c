/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_atof.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/27 04:50:52 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/27 05:47:10 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static double	get_floating_part(char *str)
{
	double	nb;
	int		i;

	nb = 0;
	i = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		nb += (double)(str[i] - '0') / (double)(ft_pow(10, i + 1));
		i++;
	}
	return (nb);
}

double			ft_atof(char *str)
{
	double	nb;
	int		i;
	int		neg;

	i = 0;
	nb = 0;
	neg = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
	{
		neg = 1;
		str++;
	}
	if (!neg && *str == '+')
		str++;
	while (ft_isdigit(str[i]) && str[i] && str[i] != '.' && str[i] != ',')
		nb = nb * 10 + (double)(str[i++] - '0');
	if (!str[i] || (str[i] != '.' && str[i] != ','))
		return (neg ? -1 * nb : nb);
	return ((neg ? -1 : 1) * (nb + get_floating_part(&str[i + 1])));
}
