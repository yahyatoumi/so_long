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
	char *map;
	int i;
	char **matrice;
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


char	**ft_split(char const *s, char c);
void free_arr(char **arr);
int set_parsing_struct(t_pars *pars);
void set_initial_values(t_pars *list);
int check_last_line(t_pars *list, char *line);
int lines_counter(char *path);
int is_map_valid(t_pars list);
char **check_map(char *path);
int no_c_left(char **matrice);
void print_matrice(char **arr);
char **copy_matrice(t_vars m);
int find_exit(int _row, int _col, t_vars *m, int *i);
void chars_count(t_vars *m);
int char_check(char c, int c_char);
int key_hook(int keycode, t_vars *vars);
int close_window(void *param);
int ft_strcmp(char *s1, char *s2);
int ft_check_ber(char *path);
void ft_helper(char c, t_vars *vars, int x, int y);
int mlx_helper4(t_vars vars, int i, int j);
int mlx_helper3(t_vars vars);
int mlx_helper2(t_vars vars);
int mlx_helper(t_vars vars);

#endif
