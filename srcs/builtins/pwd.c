/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-27 16:55:25 by thmaitre          #+#    #+#             */
/*   Updated: 2025-05-27 16:55:25 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	builtin_pwd(void)
{
	char	buf[1000];
	size_t	size;

	size = 1000;
	getcwd(buf, size);
	printf("%s\n", buf);
	return (0);
}

int	main(void)
{
	builtin_pwd();
	return (0);
}
