
#include "rush01.h"

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\r')
		return (1);
	return (0);
}

int	ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	to_int(char **str, int flag)
{
	int	arg;

	arg = -1;
	if (is_whitespace(**str) && flag != 0)
		(*str)++;
	else if (!is_whitespace(**str) && flag != 0)
		return (arg);
	if (**str == '+')
		(*str)++;
	if (ft_is_digit(**str))
	{
		arg = **str - '0';
		(*str)++;
	} // TODO maybe add condition for leading zero
	return (arg);
}

int	find_size(int index)
{
	if (index == 16)
		return (4);
	else if (index == 20)
		return (5);
	else if (index == 24)
		return (6);
	else if (index == 28)
		return (7);
	else if (index == 32)
		return (8);
	else if (index == 36)
		return (9);
	else 
		return (ERROR);
}

int	copy_and_validate(int raw_input[], t_false *whatever, int index)
{
	int i;
	int j;
	int	k;

	whatever->actual_size = find_size(index);
	if (whatever->actual_size == ERROR)
		return (ERROR);
	
	j = 0;
	i = 0;
	k = 0;
	while (i < BOUNDARY_SIZE)
	{
		while (j < whatever->actual_size)
		{
			if (raw_input[k] <= 0 || raw_input[k] > whatever->actual_size)
				return (ERROR);
			whatever->boundaries[i][j] = raw_input[k];
			j++;
			k++;
		}
		j = 0;
		i++;
	}
	return (SUCCESS);
}

int	process_input(char *input, t_false *whatever)
{
	char	*input_ptr;
	int		raw_input[36]; // TODO make macro for this
	int 	index;

	input_ptr = input;
	index = 0;
	while (*input_ptr && index < 36)
	{
		raw_input[index] = to_int(&input_ptr, index);
		if (raw_input[index] == -1)
			return (ERROR);
		index++;
	}
	if (*input_ptr || copy_and_validate(raw_input, whatever, index) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
void	zero_arrays(t_false *whatever)
{
	int i;
	int j;

	i = 0;
	while (i < GRID_SIZE)
	{
		j = 0;
		while (j < GRID_SIZE)
		{
			whatever->grid[i][j] = 0;
			j++;
		}
		i++;
	}
	i = 0;
	while (i < BOUNDARY_SIZE)
	{
		j = 0;
		while (j < GRID_SIZE)
		{
			whatever->boundaries[i][j] = 0;
			j++;
		}
		i++;
	}
}

void print_result(t_false *whatever)
{
	int i;
	int j;
	char c;
	

	i = 0;
	while (i < whatever->actual_size)
	{
		j = 0;
		while (j < whatever->actual_size)
		{
			c = whatever->grid[i][j] + '0';
			write(1, &c, 1);
			if (j != whatever->actual_size - 1)
				write(1, " ", 1);
			j++;
		}
		i++;
		write(1, "\n", 1);
	}
}

int	main(int argc, char **argv)
{
	t_false	 whatever;

	if (argc != 2)
		return (1); //TODO make error printer
	zero_arrays(&whatever);
	if (process_input(argv[1], &whatever) == ERROR)
		return (1);
	if (solve_it(&whatever, 0, 0) == 1)
		print_result(&whatever);
	else
		write (1, "no solution found\n", 18);
	// TODO make solution printer
	return (0);
}
