/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_fsqrt.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/27 13:42:24 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/11 13:20:15 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

double	ft_fsqrt(double n, double prec)
{
	double	min;
	double	max;
	double	test;

	min = 0.0;
	max = 46341.0;
	test = (max - min) / 2.0 + min;
	while (test * test != n)
	{
		if (test * test > n)
			max = test;
		if (test * test < n)
			min = test;
		if (max - min < prec)
			return (max);
		test = (max - min) / 2.0 + min;
	}
	return (test);
}
