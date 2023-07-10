
#include "rush01.h"

int	existing_digit(t_false *whatever, int row, int col)
{
	if ((col + 1) < whatever->actual_size)
		return (solve_it(whatever, row, col + 1));
	else if ((row + 1) < whatever->actual_size)
		return (solve_it(whatever, row + 1, 0));
	else
		return (1);
}

// case of 0 digit: checks digits 1..actual size
int	new_digit(t_false *whatever, int row, int col)
{
	int	max_index;
	int	digit;

	max_index = whatever->actual_size;
	digit = 1;
	while (digit <= max_index)
	{
		if (valid_placement(whatever, row, col, digit))
		{
			whatever->grid[row][col] = digit;
			if (check_all_bounds(whatever, row, col) == 1)
			{
				if (solve_it(whatever, row, col))
					return (1);
			}
			whatever->grid[row][col] = 0;
		}
		digit++;
	}
	return (0);
}

// Returns 1 if the solution is found, otherwise 0.
// Parameters: program struct, row, column.
int	solve_it(t_false *whatever, int row, int col)
{
	
	if (row >= whatever->actual_size || col >= whatever->actual_size)
		return (1);
	else
	{
		if (whatever->grid[row][col] != 0)
			return (existing_digit(whatever, row, col));
		else
			return (new_digit(whatever, row, col));
		return (0);
	}
}