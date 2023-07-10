
#include "rush01.h"

//if col or row is full we may need to validate that number visible == boundary

//may need to stay separate from the row/col value checker as the value will need to be already placed in this case
int	check_colup(t_false *whatever, int col)
{
	t_boundary_checker	checker;
	int i;

	// this is checking the the column up, top to down
	checker.boundary = whatever->boundaries[0][col];
	checker.number_visible = 0;
	checker.base = 0;
	i = 0;
	while (i < whatever->actual_size)
	{
		if (whatever->grid[i][col] == 0)
			i++;
		else if (checker.base == 0)
		{
			checker.base = whatever->grid[i++][col];
			checker.number_visible++;
		}
		else if (whatever->grid[i++][col] > checker.base)
		{
			checker.base = whatever->grid[i - 1][col];
			checker.number_visible++;
		}
		if (checker.number_visible > checker.boundary)
			return (0);
	}
	return (1);
}


int	check_coldown(t_false *whatever, int col)
{
	t_boundary_checker	checker;
	int i;

	checker.boundary = whatever->boundaries[1][col];
	checker.number_visible = 0;
	checker.base = 0;
	i = whatever->actual_size - 1;
	while (i >= 0)
	{
		if (whatever->grid[i][col] == 0)
			i--;
		else if (checker.base == 0)
		{
			checker.base = whatever->grid[i--][col];
			checker.number_visible++;
		}
		else if (whatever->grid[i--][col] > checker.base)
		{
			checker.base = whatever->grid[i + 1][col];
			checker.number_visible++;
		}
		if (checker.number_visible > checker.boundary)
			return (0);
	}
	return (1);
}

int	check_rowleft(t_false *whatever, int row)
{
	t_boundary_checker	checker;
	int i;

	checker.boundary = whatever->boundaries[2][row];
	checker.number_visible = 0;
	checker.base = 0;
	i = 0;
	while (i < whatever->actual_size)
	{
		if (whatever->grid[row][i] == 0)
			i++;
		else if (checker.base == 0)
		{
			checker.base = whatever->grid[row][i++];
			checker.number_visible++;
		}
		else if (whatever->grid[row][i++] > checker.base)
		{
			checker.base = whatever->grid[row][i - 1];
			checker.number_visible++;
		}
		if (checker.number_visible > checker.boundary)
			return (0);
	}
	return (1);
}

int	check_rowright(t_false *whatever, int row)
{
	t_boundary_checker	checker;
	int i;

	checker.boundary = whatever->boundaries[3][row];
	checker.number_visible = 0;
	checker.base = 0;
	i = whatever->actual_size - 1;
	while (i >= 0)
	{
		if (whatever->grid[row][i] == 0)
			i--;
		else if (checker.base == 0)
		{
			checker.base = whatever->grid[row][i--];
			checker.number_visible++;
		}
		else if (whatever->grid[row][i--] > checker.base)
		{
			checker.base = whatever->grid[row][i + 1];
			checker.number_visible++;
		}
		if (checker.number_visible > checker.boundary)
			return (0);
	}
	return (1);
}

int	check_all_bounds(t_false *whatever, int row, int col)
{
	if (check_coldown(whatever, col) == 0)
		return (0);
	if (check_colup(whatever, col) == 0)
		return (0);
	if (check_rowleft(whatever, row) == 0)
		return (0);
	if (check_rowright(whatever, row) == 0)
		return (0);
	return (1);
}
	// checker[1].boundary = whatever->boundaries[1][x];
	// checker[2].boundary = whatever->boundaries[2][y];
	// checker[3].boundary = whatever->boundaries[3][y];


	// whatever->boundaries[0][x] -> from top to down
	// whatever->boundaries[1][x] -> from bottom to up 
	// whatever->boundaries[2][y] -> from left to right
	// whatever->boundaries[3][y] -> from right to left

/*
	boudary moves in given direction, first non 0 encountered == base value. 
	if boundary # of evaled dir are greater than the base, placement fails
*/

int	valid_placement(t_false *whatever, int row, int col, int to_check)
{
	int	i;
	int	boundary_vals[4];

	i = 0;
	// check for duplicate in col or row
	while (i < whatever->actual_size)
	{
		if (whatever->grid[row][i] == to_check || whatever->grid[i][col] == to_check)
			return (0);
		i++;
	}
	return (1);
}
