#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

typedef struct s_ope
{
	float rad;
	float x;
	float y;
	char type;
	char car;
} t_ope;

typedef struct s_inf
{
	int wid;
	int hei;
	char **tab;
	char back;
} t_inf;

int ft_strlen(char *str)
{
	int res;

	res = 0;

	while (str[res] != '\0')
	{
		res++;
	}
	return (res);
}

void ft_putchar(char c)
{
	write(1, &c, 1);
}


void ft_putstr(char *str)
{
	int len;

	len = ft_strlen(str);
	write(1, str, len);

}
void ini_tab(t_inf *inf)
{
	for (int i = 0 ; i < inf->hei ; i++)
	{
		for (int j = 0 ; j < inf->wid ; j++)
		{
			(inf->tab)[i][j] = inf->back;
		}
	}
}

void aff_tab(t_inf *inf)
{
	for (int i = 0 ; i < inf->hei ; i++)
	{
		for (int j = 0 ; j < inf->wid ; j++)
		{
			ft_putchar((inf->tab)[i][j]);
			//ft_putchar(' ');
		}
		ft_putchar('\n');
	}
}

float carre(float nb)
{
	return (nb * nb);
}

int cond(int i, int j, t_ope *ope)
{
	float dist;

	dist = sqrtf(carre(i - ope->y) + carre(j - ope->x));

	if (dist > ope->rad)
		return (0);
	if (ope->rad - (dist) < 1)
		return(2);
	return (1);
}

void draw(t_inf *inf, t_ope *ope)
{
	for (int i = 0 ; i < inf->hei ; i++)
	{
		for (int j = 0 ; j < inf->wid ; j++)
		{
			if ((cond(i, j, ope) && ope->type == 'C' )|| (cond(i, j, ope) == 2 && ope->type == 'c'))
				(inf->tab)[i][j] = ope->car;
		}
	}
}

void aff_op(t_ope *ope)
{
	printf("%c %f %f %f %c\n", ope->type, ope->x, ope->y, ope->rad, ope->car);
}

void print_err(void)
{
	int len;

	len = ft_strlen("Error: Operation file corrupted\n");
	write(1, "Error: Operation file corrupted\n", len);
}

int next_ope(FILE *file, t_inf *inf, t_ope *ope)
{
	int ret;

	ret = fscanf(file, "%c %f %f %f %c\n", &(ope->type), &(ope->x), &(ope->y), &(ope->rad), &(ope->car));
	if (ret == -1)
		return (1);
	if (ret != 5 || (ope->type != 'c' && ope->type != 'C') || ope->rad <= 0)
	{
		//printf("%d", ret);
		return(2);
	}
	draw(inf, ope);
	return (0);
}

int main(int argc, char *argv[])
{
	FILE *file;
	t_inf inf;
	t_ope ope;
	int status;

	status = 0;
	if (argc != 2)
	{
		ft_putstr("Error: argument\n");
		return (1);
	}
	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		print_err();
		return (1);
	}
	status = fscanf(file, "%d %d %c\n", &(inf.wid), &(inf.hei), &(inf.back));
	if (status == -1)
	{
		print_err();

		return (1);
	}
	if (status != 3)
	{
		print_err();

		return (1);
	}
	if (inf.wid > 300 || inf.hei > 300 || inf.wid <= 0 || inf.hei <= 0)
	{
		print_err();

		return (1);
	}
	inf.tab = (char **)malloc(inf.hei * sizeof(char *));
	for (int i = 0 ; i < inf.hei ; i++)
		(inf.tab)[i] = malloc(inf.wid * sizeof(char));
	ini_tab(&inf);
	status = 0;
	while (status == 0)
		status = next_ope(file, &inf, &ope);
	if (status == 2)
	{
		print_err();
		return (1);
	}
	aff_tab(&inf);
	return (0);
}