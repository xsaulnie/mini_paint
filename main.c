#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

void ft_putchar(char c)
{
	write(1, &c, 1);
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
		}
		ft_putchar('\n');
	}
}

int carre(int nb)
{
	return (nb * nb);
}

int cond(int i, int j, t_ope *ope)
{
	float dist;

	dist = carre(i - ope->y) + carre(j - ope->x);

	if (dist > carre(ope->rad))
		return (0);
	return (1);
}

void draw(t_inf *inf, t_ope *ope)
{
	for (int i = 0 ; i < inf->hei ; i++)
	{
		for (int j = 0 ; j < inf->wid ; j++)
		{
			if (cond(i, j, ope) && ope->type == 'C')
				(inf->tab)[i][j] = ope->car;
		}
	}
}

void aff_op(t_ope *ope)
{
	printf("%c %f %f %f %c\n", ope->type, ope->x, ope->y, ope->rad, ope->car);
}
int next_ope(FILE *file, t_inf *inf, t_ope *ope)
{
	char vidbuf;
	int ret;

	ret = fscanf(file, "%c %f %f %f %c", &(ope->type), &(ope->x), &(ope->y), &(ope->rad), &(ope->car));
	//if (ret != 5 || ret == -1)
	//	return (0);
	fscanf(file, "%c", &vidbuf);
	aff_op(ope);
	draw(inf, ope);
	aff_tab(inf);
	return (1);
}

int main()
{
	FILE *file;
	t_inf inf;
	t_ope ope;
	char c;

	file = fopen("ope.txt", "r");
	fscanf(file, "%d %d %c", &(inf.wid), &(inf.hei), &(inf.back));
	fscanf(file, "%c", &c);
	inf.tab = (char **)malloc(inf.hei * sizeof(char *));
	for (int i = 0 ; i < inf.hei ; i++)
		(inf.tab)[i] = malloc(inf.wid * sizeof(char));
	ini_tab(&inf);
	next_ope(file, &inf, &ope);
	return (0);
}