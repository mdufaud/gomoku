/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gomoku.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:42:07 by mdufaud           #+#    #+#             */
/*   Updated: 2016/07/01 14:03:48 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GOMOKU_HPP
# define GOMOKU_HPP

# define MAX(x,y) ((x) > (y)) ? (x) : (y)
# define MIN(x,y) ((x) < (y)) ? (x) : (y)

//# define W_WIDTH 1380
# define W_WIDTH 1390
# define MIN_WIN_WIDTH 820
//# define W_HEIGHT 1024
# define W_HEIGHT 1360
# define MIN_WIN_HEIGHT 580
# define MAX_INPUTS 16

# ifdef __APPLE__
#  define FONT_PATH "/Library/Fonts/"
#  define MAIN_FONT "Courier New.ttf"
# endif
# ifdef __linux__
#  define FONT_PATH "/usr/share/fonts/truetype/liberation/"
#  define MAIN_FONT "LiberationSans-Regular.ttf"
# endif

# define SCROLL_Y_VALUE -800
# define SCROLL_X_VALUE -200

# define MENU_FONT 100
# define HEADER_FONT 101
# define BOARD_FONT 102

# define BOARD_FONTSIZE 12
# define MENU_FONTSIZE 24
# define HEADER_FONTSIZE 50

# define GOMOKU_NO_MENU 0
# define GOMOKU_MAIN_MENU 1
# define GOMOKU_CONFIG_MENU 2
# define GOMOKU_PLAYER_SELECT 3
# define GOMOKU_GAME_INTERFACE 4
# define GOMOKU_HOTSEAT 5

# define ABLOCK_TYPE 0
# define TEXTBLOCK_TYPE 10
# define MENUBLOCK_TYPE 11
# define INPUTBLOCK_TYPE 12
# define INFOBLOCK_TYPE 13
# define GAMEBLOCK_TYPE 14
# define BOOLBLOCK_TYPE 15
# define LOGBLOCK_TYPE 16

# define GO_BOARD_BMP "assets/Blank_Go_board.bmp"
# define GO_WHITE_PAWN_BMP "assets/white_pawn.bmp"
# define GO_BLACK_PAWN_BMP "assets/black_pawn.bmp"
# define INFO_WHITE_PAWN_BMP "assets/infoWhitePawn.bmp"
# define INFO_BLACK_PAWN_BMP "assets/infoBlackPawn.bmp"
# define BACKGROUND_BMP "assets/hd_background.bmp"
# define LOG_BLOCK_BMP "assets/logblock.bmp"
# define INFO_BLOCK_BMP "assets/infoblock.bmp"
# define SUGGESTED_BLACK_BMP "assets/suggestedBlackPlay.bmp"
# define SUGGESTED_WHITE_BMP "assets/suggestedWhitePlay.bmp"

# define DEPTH_VALUE 10
# define VICTORY_VALUE 50000000
# define ALPHA_VALUE -2000000000
# define BETA_VALUE 2000000000

# include <iostream>
# include <stdlib.h>
# include <stdio.h>
# include <string>
# ifdef __APPLE__
#  include <SDL2/SDL.h>
#  include <SDL2/SDL_ttf.h>
# endif
# ifdef __linux__
#  include <SDL2/SDL.h>
#  include <SDL2/SDL_ttf.h>
# endif
# include <list>
# include <vector>
# include <sstream>
# include <time.h>
# include "Board.class.hpp"
# include "Player.class.hpp"
# include "ClassicRule.class.hpp"
# include "AlignRule.class.hpp"

class			Graph;

std::string		to_string(int i);
std::string		to_string(double d);
void			debugs(std::string s);
void			debugi(int i);
void			debugs(std::string s, std::string s1);
void			sdl_error(std::string message);
void			apply_surface(int x, int y, SDL_Surface *src, SDL_Surface *dest);
void			apply_surface(int x, int y, int x2, int y2, SDL_Surface *src, SDL_Surface *dest);
void			apply_surface(Graph *graph, SDL_Texture *text, SDL_Rect *src, SDL_Rect *dst);
bool			init(SDL_Window **window);
bool			load_media(SDL_Surface **media, std::string filename);
SDL_Surface		*load_media(std::string filename);
SDL_Surface		*load_image(std::string filename);
TTF_Font		*load_font(std::string path, int size);
void			sdl_close(SDL_Window *window);
void			sdl_error(std::string message);
SDL_Surface		*resize_image(SDL_Surface *src, int w, int h);
SDL_Rect		make_rect(int x, int y, int w, int h);

void			set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void			draw_circle(SDL_Surface *surface, int n_cx, int n_cy, int radius, Uint32 pixel);
void			fill_circle(SDL_Surface *surface, int cx, int cy, int radius, Uint32 pixel);
SDL_Texture		*createMessageTexture(std::string text, SDL_Renderer *renderer, TTF_Font *font, SDL_Color color);


typedef std::vector< std::vector<int> > t_matrix;
typedef std::vector<int>				t_matrixLine;

void							printPuzzle(t_matrix container);
std::vector<std::string> &		split(const std::string & s, char delim, std::vector<std::string> & elem);
std::vector<std::string>		split(const std::string & s, char delim);
std::string						getRealPath(void);

#endif
