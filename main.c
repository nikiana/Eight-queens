/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcarrot <kcarrot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 13:13:16 by kcarrot           #+#    #+#             */
/*   Updated: 2019/02/11 14:10:48 by kcarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	print_solution(unsigned char *board)
{
	int				i;
	int				j;
	unsigned char	c;
	static int		num = 1;

	printf("Solution #%i:\n", num);
	num++;
	i = 0;
	while (i < 8)
	{
		j = 8;
		c = board[i];
		while (j--)
		{
			c & (unsigned char)128 ? write(1, "1", 1) : write(1, "0", 1);
			c <<= 1;
		}
		write(1, "\n", 1);
		i++;
	}
	write(1, "\n\n", 2);
}

int		check_cross(unsigned char *board, int i, int j)
{
	int new_j;

	new_j = j - 1;
	while (new_j >= 0)
	{
		if ((board[i] << new_j) & (unsigned char)128)
			return (1);
		new_j--;
	}
	i = i - 1;
	while (i >= 0)
		if ((board[i--] << j) & (unsigned char)128)
			return (1);
	return (0);
}

int		check_diagonal(unsigned char *board, int i, int j)
{
	int new_j;

	i = i - 1;
	new_j = j;
	while (i >= 0)
	{
		j--;
		new_j++;
		if (j >= 0)
			if (board[i] << j & (unsigned char)128)
				return (1);
		if (new_j < 8)
			if (board[i] << new_j & (unsigned char)128)
				return (1);
		i--;
	}
	return (0);
}

void	solution(unsigned char *board, int i, int j, int q)
{
	if (q == 8)
	{
		print_solution(board);
		return ;
	}
	while (i < 8)
	{
		while (j < 8)
		{
			if (!check_cross(board, i, j) && !check_diagonal(board, i, j))
			{
				board[i] |= ((unsigned char)128 >> j);
				solution(board, i, j + 1, q + 1);
				board[i] = 0;
			}
			j++;
		}
		i++;
		j = 0;
	}
}

int		main(void)
{
	unsigned char	*board;
	int				i;

	board = (unsigned char*)malloc(sizeof(unsigned char) * 8);
	i = 0;
	while (i < 8)
		board[i++] = 0;
	solution(board, 0, 0, 0);
	return (0);
}
