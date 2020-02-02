/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 16:48:08 by saneveu           #+#    #+#             */
/*   Updated: 2020/02/02 20:51:00 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <time.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>

# include "../SDL/SDL.h"
# include "../SDL/SDL_mixer.h"
# include "../SDL/SDL_ttf.h"

# include "../libft/includes/libft.h"

# define W_WIDTH	1280
# define W_HEIGHT	720

# define FPS		60

# define SNB		29
# define WNB		4

# define KQ			0
# define KE			1
# define KW			2
# define KA			3
# define KS			4
# define KD			5
# define KM			6
# define KSPC		7
# define KB			8
# define KN			9
# define KP			10
# define ML			11
# define MR			12
# define SHIFT		13
# define MOUSE		14
# define KNB		15

typedef struct	s_rgba
{
	int			r;
	int			g;
	int			b;
	int			a;
}				t_rgba;

typedef union	u_rsqrt
{
	float		f;
	uint32_t	i;
}				t_rsqrt;

typedef struct	s_sprite
{
	SDL_Surface	*img;
}				t_sprite;

typedef struct	s_sound
{
	Mix_Music	*ingmusic;
	Mix_Music	*pausemusic;
	Mix_Chunk	*gun;
	Mix_Chunk	*shotgun;
	Mix_Chunk	*fusil;
	Mix_Chunk	*hand;
	Mix_Chunk	*nmihit;
	Mix_Chunk	*nmideath;
	Mix_Chunk	*nmispawn;
	Mix_Chunk	*nmiatk;
	Mix_Chunk	*playerhit;
	Mix_Chunk	*playerdeath;
	Mix_Chunk	*playerspawn;
	Mix_Chunk	*switchgun;
	Mix_Chunk	*tic;
	Uint8		token;
}				t_sound;

typedef struct	s_objdata
{
	int			column;
	uint32_t	zpixel;
	float		angle;
	float		mid;
	float		ratio;
	float		dst_fromplayer;
	float		ceiling;
	float		floor;
	float		height;
	float		width;
	float		samplex;
	float		sampley;
	double		invdet;
	double		transformx;
	double		transformy;
	int			spritescreenx;
	int			spriteheight;
	int			spritewidth;
	int			drawstarty;
	int			drawendy;
	int			drawendx;
	int			drawstartx;
}				t_objdata;

typedef struct	s_object
{
	int				dead;
	int				delay;
	int				hp;
	int				hp_max;
	int				i;
	int				si;
	int				type;
	float			speed;
	float			x;
	float			y;
	float			vx;
	float			vy;
	float			depth;
	t_sprite		sprite;
	t_objdata		data;
	struct s_object	*next;
}				t_object;

typedef struct	s_rect
{
	int				x;
	int				y;
	int				h;
	int				w;
}				t_rect;

typedef struct	s_wdata
{
	int			si;
	int			column;
	int			damage;
	int			delay;
	int			range;
	uint32_t	zpixel;
	float		height;
	float		width;
	float		ratio;
}				t_wdata;

typedef struct	s_player
{
	int			health;
	int			health_max;
	int			pos;
	int			weapon;
	float		angle;
	float		fov;
	float		ms;
	float		speed;
	float		x;
	float		y;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	t_wdata		wdata[WNB];
}				t_player;

typedef struct	s_ray
{
	int			wallside;
	int			wallhit;
	int			walltop;
	int			wallbot;
	double		wallx;
	double		perpwalldist;
	double		distwall;
	int			maposx;
	int			maposy;
	double		dirx;
	double		diry;
	double		deltadistx;
	double		deltadisty;
	double		sidedistx;
	double		sidedisty;
	double		camera;
	int			stepx;
	int			stepy;
	int			height;
	int			tex;
	int			wtx;
	int			wty;
	double		floorwallx;
	double		floorwally;
	double		currentfloorx;
	double		currentfloory;
	double		distcurrent;
	double		weight;
}				t_ray;

typedef struct	s_map
{
	int			len;
	int			height;
	int			width;
	int			*map;
	float		depth;
	float		depth_buffer[W_WIDTH];
	int			sc_x;
}				t_map;

typedef struct	s_point
{
	int			i;
	int			x;
	int			y;
}				t_point;

typedef struct	s_node
{
	int				bobstacle;
	int				bvisited;
	int				i;
	int				x;
	int				y;
	float			globalgoal;
	float			localgoal;
	struct s_node	*ngbhr[4];
	struct s_node	*parent;
}				t_node;

typedef struct	s_alst
{
	t_node			*node;
	struct s_alst	*next;
}				t_alst;

typedef struct	s_pf
{
	t_node		*start;
	t_node		*end;
	t_node		*list;
	t_alst		*alst;
}				t_pf;

typedef struct	s_wolf
{
	t_point					end;
	int						game;
	char					*strgame;
	int						style;
	int						floorstyle;
	int						fire_delay;
	int						fps;
	int						kill_score;
	int						sdl_on;
	int						shoot;
	int						skin_delay;
	int						wdelay;
	int						wx;
	int						wy;
	int						key[KNB];
	char					*str;
	float					cdst;
	float					frametime;
	float					oldtime;
	float					time;
	double					mv_speed;
	double					rot_speed;
	double					obj_intens;
	int						fog;
	TTF_Font				*police;
	TTF_Font				*police2;
	TTF_Font				*police3;
	TTF_Font				*policep;
	t_map					map;
	t_pf					pfdata;
	t_player				player;
	t_ray					ray;
	t_object				*monster;
	t_object				*object;
	t_object				*end_flag;
	t_sprite				sprite[SNB];
	t_rgba					rgb;
	SDL_Point				*point;
	t_sound					sound;
	SDL_MouseMotionEvent	mouse;
	SDL_Event				event;
	SDL_Renderer			*renderer;
	SDL_Surface				*screen;
	SDL_Surface				*surf_write;
	SDL_Texture				*text_write;
	SDL_Texture				*window;
	SDL_Window				*pwindow;
}				t_wolf;

void			display(t_wolf *data);
void			deal_damage_tomonster(t_wolf *data, t_object *list, int damage);
void			events(t_wolf *data);
void			game_over(t_wolf *data);
void			load_datagame(t_wolf *data);
void			monsters(t_wolf *data);
void			mouse_events(t_wolf *data);
void			mouse_motion(t_wolf *data);
void			movements(t_wolf *data);
void			objects(t_wolf *data, t_object *list);
void			object_actions(t_wolf *data, t_object *list);
void			shoot(t_wolf *data);
void			spawner(t_wolf *data);
void			sprites(t_wolf *data);
void			sprites_textures(t_wolf *data);
void			sprites_textures_asylum(t_wolf *data);
void			sprites_textures_maze(t_wolf *data);
void			switch_floor(t_wolf *d);
void			sprites_monsters_asylum(t_wolf *data);
void			sprites_monsters_maze(t_wolf *data);
void			weapons(t_wolf *data);
void			change_weapon(t_wolf *data);
void			wolf3d(t_wolf *data);
t_wolf			*minimap_alloc(t_wolf *data);
void			get_blockside(t_wolf *data, int testx, int testy);
void			raycasting(t_wolf *data);
void			draw_wall(t_wolf *d, int x);
void			get_tex(t_wolf *d);

void			minimap(t_wolf *data);
void			free_minimap(t_wolf *d);

float			distance(float x1, float y1, float x2, float y2);
float			distance_calc(float x1, float y1, float x2, float y2);
int				get_objhp(t_wolf *data, t_object *list);
uint32_t		get_pixel(t_wolf *data, int si, float samplex, float sampley);
SDL_Surface		*new_surface(int w, int h);
void			put_pixel(SDL_Surface *surface, int x, int y, uint32_t color);
Uint32			light_shade(Uint32 hexa, float distance);

void			draw_fps(t_wolf *data);
void			add_sc_x(t_wolf *data);
void			clean_exit(t_wolf *data, char *str, int token);
void			lst_free(t_object *list);
int				lst_len(t_object *list);
void			lst_pushback(t_object *list, t_object *node);

void			get_nodes(t_wolf *data);
void			astar(t_wolf *data);

void			alst_free(t_alst *list);
int				alst_len(t_alst *list);
void			alst_pushback(t_alst *list, t_node *node);
void			alst_sort(t_alst *list);

void			w_pause(t_wolf *data);
void			set_rect_to_screen(t_wolf *data, SDL_Rect *rect, int color);
SDL_Color		ft_hex_to_rgb(int hexa);
void			set_write_to_screen(t_wolf *data,
	SDL_Rect rect, int color, char *str);
void			ft_mouse_motion_x(t_wolf *data);
void			object_minimap(t_wolf *data, t_object *list);
void			minimap2(t_wolf *data);

uint32_t		get_pixel_obj(t_object *l, int texx, int texy);
uint32_t		get_pixel_ray(t_wolf *data, int si, float samplex,
	float sampley);
uint32_t		get_pixel_floor(t_wolf *data, int si, float samplex,
	float sampley);
void			draw_floor_ceilling(t_wolf *d, int x);
void			mouse(t_wolf *data, Sint16 xrel, int dir);

void			audio_init(t_wolf *data);
void			free_sound(t_wolf *data);
void			play_sound(t_wolf *data, Mix_Chunk *chunk, int channel);
void			play_music(t_wolf *data, Mix_Music *music);

void			cursor(t_wolf *data);
void			health(t_wolf *data);
void			help_pause(t_wolf *data);

t_rgba			fill_rgb(int c);
int				rgb_to_hsv(int r, int g, int b);
int				fog(t_wolf *d, Uint32 pixel, float distance);
void			switch_fog(t_wolf *d);
void			switch_texture(t_wolf *data);
void			free_surfaces(t_wolf *data, int flag);
void			choose_game(t_wolf *data, char *game);
void			set_end_pt(t_wolf *d, int i);
void			end_screen(t_wolf *d, char *str);
int				move_cursor(t_wolf *data, int *cursor);
void			draw_cursor(t_wolf *data, int cursor);

void			free_ttf(t_wolf *data);

#endif
