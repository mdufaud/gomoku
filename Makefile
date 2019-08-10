# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/27 14:59:24 by mdufaud           #+#    #+#              #
#    Updated: 2016/03/23 17:49:18 by rcherik          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS := $(shell uname)

ifeq ($(OS),Linux)
SHELL := /bin/bash
ECHO := echo -e
OFLAGS = -I ./includes/. `sdl2-config --cflags`
LFLAGS = `sdl2-config --libs` -lSDL2_ttf -lpthread
else
SHELL := /bin/sh
ECHO := echo
OFLAGS = -I ./includes/. -I ~/.brew/include
LFLAGS = -L ~/.brew/lib -lSDL2 -lSDL2_ttf -lpng
endif

NAME = gomoku
CFLAGS = g++ -Wall -Wextra -Werror -o3 -std=c++11
PATH_SRC = srcs
PATH_OBJ = obj
PATH_INCLUDES = includes
SRC = main.cpp\
	  apply_surface.cpp\
	  sdl_close.cpp\
	  to_string.cpp\
	  debugs.cpp\
	  sdl_error.cpp\
	  Graph.class.cpp\
	  AInterface.class.cpp\
	  ABlock.class.cpp\
	  MainMenu.class.cpp\
	  GameState.class.cpp\
	  GameInterface.class.cpp\
	  ConfigMenu.class.cpp\
	  GameBlock.class.cpp\
	  MenuBlock.class.cpp\
	  TextBlock.class.cpp\
	  LogBlock.class.cpp\
	  InfoBlock.class.cpp\
	  BoolBlock.class.cpp\
	  HotSeat.class.cpp\
	  IA.class.cpp\
	  PlayerSelect.class.cpp\
	  make_rect.cpp\
	  load_font.cpp\
	  load_media.cpp\
	  init.cpp\
	  InputBlock.class.cpp\
	  createMessageTexture.cpp\
	  Board.class.cpp\
	  printPuzzle.cpp\
	  Player.class.cpp\
	  ClassicRule.class.cpp\
	  AlignRule.class.cpp\
	  Rules.class.cpp\
	  Coup.class.cpp\
	  set_pixel.cpp\
	  Node.class.cpp\
	  draw_circle.cpp\
	  get_real_path.cpp\
	  fill_circle.cpp\
	  split.cpp

OBJ = $(patsubst %.cpp, $(PATH_OBJ)/%.o, $(SRC))

NO_PATH_INCLUDES = gomoku.hpp\
				   Graph.class.hpp\
				   MainMenu.class.hpp\
				   MenuBlock.class.hpp\
				   GameInterface.class.hpp\
				   GameBlock.class.hpp\
				   TextBlock.class.hpp\
	  			   InputBlock.class.hpp\
	  			   InfoBlock.class.hpp\
	  			   LogBlock.class.hpp\
	  			   PlayerSelect.class.hpp\
				   AInterface.class.hpp\
				   HotSeat.class.hpp\
	  			   GameState.class.hpp\
				   ABlock.class.hpp\
				   BoolBlock.class.hpp\
	  			   ConfigMenu.class.hpp\
				   Player.class.hpp\
				   IA.class.hpp\
				   Node.class.hpp\
				   Board.class.hpp\
				   Rules.class.hpp\
				   ClassicRule.class.hpp\
				   AlignRule.class.hpp\
				   Coup.class.hpp

INCLUDES = $(patsubst %.hpp, $(PATH_INCLUDES)/%.hpp, $(NO_PATH_INCLUDES))

all: $(NAME)

$(PATH_OBJ)/%.o : $(addprefix $(PATH_SRC)/, %.cpp) $(INCLUDES)
	@mkdir -p $(PATH_OBJ)
	@$(CFLAGS) $(OFLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	@$(ECHO) "\033[32m[ $(NAME) objects done ]\033[00m"
	@$(CFLAGS) $(OBJ) $(LFLAGS) -o $(NAME)
	@$(ECHO) "\033[32m[ $(NAME) compiled ]\033[00m"

clean:
	@rm -f $(OBJ)
	@rm -rf $(NAME).dSYM
	@rm -rf $(PATH_OBJ)
	@$(ECHO) "\033[31m[ $(NAME) : objects deleted ]\033[00m"

fclean: clean
	@rm -f $(NAME)
	@$(ECHO) "\033[31m[ $(NAME) : ./$(NAME) deleted ]\033[00m"

re: fclean all

#profiling: $(eval CFLAGS += -pg)
#profiling: fclean all
#	@$(ECHO) "Compiled with profiling !"

.PHONY : fclean re clean all prof_var profiling
