#ifndef SO_LONG_H
#define SO_LONG_H

typedef struct s_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_data;

typedef struct s_vars
{
	void *mlx;
	void *win;
} t_vars;

typedef struct s_pars
{
	int c_char;
	int e_char;
	int p_char;
	int line_len;
	int number_of_lines;
	char *line;
	int fd;
} t_pars;

typedef struct s_matrice
{
	int row;
	int col;
	int row_len;
	int cols_len;
	int i;
	char **matrice;
	int c_char;
	int e_char;
} t_matrice;

#endif
