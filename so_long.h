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
	void *mlx_ptr;
	void *win_ptr;
	void *wall_img;
	int wall_width;
	int wall_height;
	void *img;
	int img_width;
	int img_height;
	void *empty_img;
	int empty_width;
	int empty_height;
	void *c_img;
	int c_width;
	int c_height;
	void *e_img;
	int e_width;
	int e_height;
	int playerX;
	int playerY;
	int row;
	int col;
	int row_len;
	int cols_len;
	int i;
	char **matrice;
	char **matrice2;
	int c_char;
	int e_char;
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
