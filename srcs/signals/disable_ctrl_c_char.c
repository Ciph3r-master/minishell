/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disable_ctrl_char.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-11 21:23:44 by thmaitre          #+#    #+#             */
/*   Updated: 2025-06-11 21:23:44 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

void	disable_ctrl_c_char(void)
{
	struct termios	termios_p;

	if (tcgetattr(STDIN_FILENO, &termios_p) == -1)
		exit(EXIT_FAILURE);
	termios_p.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &termios_p) == -1)
		exit(EXIT_FAILURE);
	return ;
}
