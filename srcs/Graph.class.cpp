/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Graph.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 17:24:04 by mdufaud           #+#    #+#             */
/*   Updated: 2016/03/23 17:05:28 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Graph.class.hpp"
#include "MainMenu.class.hpp"
#include "ConfigMenu.class.hpp"
#include "HotSeat.class.hpp"
#include "GameInterface.class.hpp"
#include "PlayerSelect.class.hpp"
#include "SDL2/SDL_ttf.h"

Graph::Graph(void)
{
	_path = getRealPath();
	_error = false;
	_minimized = false;
	_fullScreen = false;
	_exit = false;
	_screen = NULL;
	if (!(init(&_window)))
		this->error("Could not load window");
	SDL_GetWindowSize(_window, &_w, &_h);
	SDL_SetWindowMinimumSize(_window, MIN_WIN_WIDTH, MIN_WIN_HEIGHT);
	_mouseFocus = true;
	_keyboardFocus = true;
	if (TTF_Init() == -1)
		this->ttf_error("Could not init fonts");
	if (!_error && !(_renderer = SDL_CreateRenderer(_window,
													-1,
													SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		this->sdl_error("Could not load renderer");
	if (!_error && !(_texture = SDL_CreateTexture(_renderer,
									SDL_PIXELFORMAT_ARGB8888,
									SDL_TEXTUREACCESS_STREAMING,
									_w, _h)))
		this->sdl_error("Could not load texture");
	if (_error)
		return ;
	this->setSurfaces();
	this->setFonts();
	this->setMenus();
	_interface = _menus[GOMOKU_MAIN_MENU];
	//_interface = _menus[GOMOKU_GAME_INTERFACE];
	//static_cast<GameInterface *>(_interface)->startGame("PlayerTest", "ALPHA GAD", false);
}

Graph::~Graph(void)
{
	if (_renderer)
		SDL_DestroyRenderer(_renderer);
	if (_screen)
		SDL_FreeSurface(_screen);
	if (_texture)
		SDL_DestroyTexture(_texture);
	TTF_Quit();
	sdl_close(_window);
}

void			Graph::setMinWinSize(void)
{
	if (_w < MIN_WIN_WIDTH || _h < MIN_WIN_HEIGHT)
	{
		_w = _w < MIN_WIN_WIDTH ? MIN_WIN_WIDTH : _w;
		_h = _h < MIN_WIN_HEIGHT ? MIN_WIN_HEIGHT : _h;
		SDL_SetWindowSize(_window, _w, _h);
	}
}

void			Graph::draw(void)
{
	SDL_RenderClear(_renderer);
	SDL_Rect fillRect = {0, 0, _w, _h};
	SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderFillRect(_renderer, &fillRect);
	if (_interface)
	{
		_interface->draw();
		SDL_RenderPresent(_renderer);
	}
	else
		_exit = true;
	//SDL_UpdateWindowSurface(_window);
}

void			Graph::mouseMotion(void)
{
	int	x;
	int	y;

	SDL_GetMouseState(&x, &y);
	switch (_event.type)
	{
		case SDL_MOUSEMOTION:
			_interface->hoover(x, y);
			break ;
		case SDL_MOUSEBUTTONDOWN:
			break ;
		case SDL_MOUSEBUTTONUP:
			if (_event.button.button == SDL_BUTTON_LEFT)
			{
				//printf("Clicked at x: %d, y: %d\n", x, y);
				_interface->click(x, y);
			}
			break ;
		default:
			break ;
	}
}

void			Graph::input(bool & loop_bool)
{
	switch (_event.key.keysym.sym)
	{
		case SDLK_ESCAPE:
			loop_bool = false;
			break ;
		case SDLK_F5:
			if (_fullScreen)
			{
				SDL_SetWindowFullscreen(_window, SDL_FALSE);
				_fullScreen = false;
			}
			else
			{
				SDL_SetWindowFullscreen(_window, SDL_TRUE);
				_fullScreen = true;
			}
		default:
			break ;
	}
	if (loop_bool)
		_interface->parseKey(_event);
}

void			Graph::windowEvent(void)
{
	bool	updateCaption = false;

	switch (_event.window.event)
	{
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			_w = _event.window.data1;
			_h = _event.window.data2;
			this->setMinWinSize();
			this->reloadInterfaces();
			SDL_RenderPresent(_renderer);
			break ;
		case SDL_WINDOWEVENT_EXPOSED:
			SDL_RenderPresent(_renderer);
			break ;
		case SDL_WINDOWEVENT_ENTER:
			_mouseFocus = true;
			updateCaption = true;
			break ;
		case SDL_WINDOWEVENT_LEAVE:
			_mouseFocus = false;
			updateCaption = true;
			break ;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			_keyboardFocus = true;
			updateCaption = true;
			break ;
		case SDL_WINDOWEVENT_FOCUS_LOST:
			_keyboardFocus = false;
			updateCaption = true;
			break ;
		case SDL_WINDOWEVENT_MINIMIZED:
			_minimized = true;
			break ;
		case SDL_WINDOWEVENT_MAXIMIZED:
			_minimized = false;
			break ;
		case SDL_WINDOWEVENT_RESTORED:
			_minimized = false;
			break ;
	}
	if (updateCaption)
	{
	}
}

int				Graph::parseEvent(bool & loop_bool)
{
	while (SDL_PollEvent(&_event) != 0)
	{
		if (_event.type == SDL_QUIT)
			loop_bool = false;
		else if (_event.type == SDL_MOUSEMOTION
				|| _event.type == SDL_MOUSEBUTTONDOWN
				|| _event.type == SDL_MOUSEBUTTONUP)
		{
			this->mouseMotion();
		}
		else if (_event.type == SDL_KEYDOWN
				|| _event.type == SDL_TEXTINPUT
				|| _event.type == SDL_TEXTEDITING)
		{
			this->input(loop_bool);
		}
		else if (_event.type == SDL_WINDOWEVENT)
		{
			this->windowEvent();
		}
	}
	return (1);
}

void			Graph::reloadInterfaces(void)
{
	MapMenus::iterator		it = _menus.begin();

	while (it != _menus.end())
	{
		it->second->resetSelectedBlocks();
		it->second->recalc_draw();
		it++;
	}
}

void			Graph::setSurfaces(void)
{
	_surfaces[BACKGROUND_BMP] = load_media(_path + BACKGROUND_BMP);
	_surfaces[LOG_BLOCK_BMP] = load_media(_path + LOG_BLOCK_BMP);
	_surfaces[INFO_BLOCK_BMP] = load_media(_path + INFO_BLOCK_BMP);
	_surfaces[GO_BOARD_BMP] = load_media(_path + GO_BOARD_BMP);
	_surfaces[GO_WHITE_PAWN_BMP] = load_media(_path + GO_WHITE_PAWN_BMP);
	_surfaces[GO_BLACK_PAWN_BMP] = load_media(_path + GO_BLACK_PAWN_BMP);
	_surfaces[INFO_WHITE_PAWN_BMP] = load_media(_path + INFO_WHITE_PAWN_BMP);
	_surfaces[INFO_BLACK_PAWN_BMP] = load_media(_path + INFO_BLACK_PAWN_BMP);
	_surfaces[SUGGESTED_BLACK_BMP] = load_media(_path + SUGGESTED_BLACK_BMP);
	_surfaces[SUGGESTED_WHITE_BMP] = load_media(_path + SUGGESTED_WHITE_BMP);

	MapSurfaces::iterator		it = _surfaces.begin();

	while (it != _surfaces.end())
	{
		if (it->second == NULL)
		{
			this->error(std::string("Could not load ") + std::string(it->first));
			break ;
		}
		it++;
	}
}

void			Graph::setMenus(void)
{
	if (!(_menus[GOMOKU_CONFIG_MENU] = new ConfigMenu(this)))
		this->error("Could not load config interface");
	if (!(_menus[GOMOKU_HOTSEAT] = new HotSeat(this)))
		this->error("Could not load hotseat interface");
	if (!(_menus[GOMOKU_GAME_INTERFACE] = new GameInterface(this)))
		this->error("Could not load game interface");
	if (!(_menus[GOMOKU_MAIN_MENU] = new MainMenu(this)))
		this->error("Could not load main menu");
	if (!(_menus[GOMOKU_PLAYER_SELECT] = new PlayerSelect(this)))
		this->error("Could not load game player select interface");
}

void			Graph::setFonts(void)
{
	if (!(_fonts[BOARD_FONT] = load_font(std::string(FONT_PATH)
											+ std::string(MAIN_FONT),
											BOARD_FONTSIZE)))
		this->error("Could not load board font");
	if (!(_fonts[MENU_FONT] = load_font(std::string(FONT_PATH)
											+ std::string(MAIN_FONT),
											MENU_FONTSIZE)))
		this->error("Could not load menu font");
	if (!(_fonts[HEADER_FONT] = load_font(std::string(FONT_PATH)
											+ std::string(MAIN_FONT),
											HEADER_FONTSIZE)))
		this->error("Could not load header font");

	if (!_error)
		TTF_SetFontStyle(_fonts[HEADER_FONT], TTF_STYLE_BOLD);
}

SDL_Surface		*Graph::getSurface(std::string name)
{
	return (_surfaces[name]);
}

TTF_Font		*Graph::getFont(int font)
{
	return (_fonts[font]);
}

AInterface		*Graph::getMenu(int type)
{
	return (_menus[type]);
}

int				Graph::error(std::string message)
{
	_error = true;
	std::cerr << "Graphical error: " << message << std::endl;
	return (1);
}

int				Graph::sdl_error(std::string message)
{
	_error = true;
	std::cout << message << " SDL_ERROR: " << SDL_GetError() << std::endl;
	return (1);
}

int				Graph::ttf_error(std::string message)
{
	_error = true;
	std::cout << message << " TTF_ERROR: " << TTF_GetError() << std::endl;
	return (1);
}

/*
int				Graph::img_error(std::string message)
{
	_error = true;
	std::cout << message << " IMG_ERROR: " << IMG_GetError() << std::endl;
	return (1);
}
*/

SDL_Texture		*Graph::getTexture(void)
{
	return (this->_texture);
}

SDL_Renderer	*Graph::getRenderer(void)
{
	return (this->_renderer);
}

bool			Graph::doContinue(void) const
{
	return (!this->_exit);
}

bool			Graph::hasMouseFocus(void) const
{
	return (this->_mouseFocus);
}

bool			Graph::hasKeyboardFocus(void) const
{
	return (this->_keyboardFocus);
}

bool			Graph::isMinimized(void) const
{
	return (this->_minimized);
}

int				Graph::getH(void) const
{
	return (this->_h);
}

int				Graph::getW(void) const
{
	return (this->_w);
}

SDL_Window		*Graph::getWindow(void) const
{
	return (this->_window);
}

SDL_Surface		*Graph::getScreen(void) const
{
	return (this->_screen);
}

AInterface		*Graph::getInterface(void) const
{
	return (this->_interface);
}

void			Graph::setInterface(AInterface *interface)
{
	//std::cout << "Interface: " << interface << std::endl;
	this->_interface = interface;
}

bool			Graph::getError(void) const
{
	return (this->_error);
}
