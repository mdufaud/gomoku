/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:37:44 by mdufaud           #+#    #+#             */
/*   Updated: 2016/03/17 19:37:47 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gomoku.hpp"
#include "Graph.class.hpp"

int		main(int argc, char **argv)
{
	Graph		graph;
	bool		running = true;

	(void)argc;
	(void)argv;
	printf("Keys for interface:\n\t- S for printing IA stats\n\
\t- B and N to go back and forth in game state\n\
\t- P to activate or deactivate auto play\n\t- I to activate or deactivate IA\n\
\t- Backspace to go back to main menu\n\t- Page up and down to go through logs\n\
\t- Up, left, down, right to navigate through the game window\n\
\t- H to activate help for next move\n");
	srand(time(NULL));
	if (graph.getError())
		return (1);
	while (running && graph.doContinue())
	{
		graph.parseEvent(running);
		graph.draw();
	}
	return (0);
}
