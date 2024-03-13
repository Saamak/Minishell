/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:27:30 by ppitzini          #+#    #+#             */
/*   Updated: 2023/11/10 19:33:59 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int				i;
	char			*tmp;
	int				len;
	unsigned char	cc;

	cc = c;
	len = 0;
	i = 0;
	tmp = (char *)s;
	while (tmp[len] != '\0')
		len ++;
	while (i <= len)
	{
		if (tmp[i] == cc)
			return (tmp + i);
		i++;
	}
	return (0);
}
