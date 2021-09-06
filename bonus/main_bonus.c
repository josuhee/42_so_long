/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 15:51:53 by sujo              #+#    #+#             */
/*   Updated: 2021/07/18 22:32:39 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	main(int argc, char *argv[])
{
	if (argc == 2)
		so_long(argv[1]);
	else
		write(1, "Error\nInvalid argument number !\n", 32);
	return (0);
}
