/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IA.class.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/30 22:47:41 by mdufaud           #+#    #+#             */
/*   Updated: 2016/07/01 15:05:10 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IA_CLASS_HPP
# define IA_CLASS_HPP

# include <utility>
# include <vector>
# include <set>
# include <mutex>
# include <queue>
# include <list>
# include "Node.class.hpp"

class Player;
class Rules;
class Board;
class Coup;
class LogBlock;

typedef std::pair<int, int>									playPair;
typedef std::set<std::pair<int, int> >						playPairList;
typedef std::vector< std::vector<int> >						t_matrix;
typedef std::priority_queue<Coup, std::vector<Coup>, Coup>	pQueue;

typedef struct	s_iaStats
{
	int			nMoves;
	int			erasedMoves;
	int			nNodes;
	int			cutNodes;
	int			cutOffs;
	double		percentCutOffs;
}				t_iaStats;

class IA
{
	public:
		IA(Rules *rule, Player *p1, Player *p2, int depth);
		~IA();

		void			setLog(LogBlock *block);
		void			think(Player *player, Board *board);
		void			thinkDepth(Player *player, Board *board, int depth);
		int				alphaBeta(Node & node, int alpha, int beta);
		Player			*getPlayer(int number, Player *p1, Player *p2);
		std::list<Coup>	getAllMoveList(Node & node);
		void			setDepth(int depth);
		void			setSearchRect(int searchRect);
		void			getMoves(t_matrix & board, playPairList & pList, playPair & pair);

		bool			isLocked(void);
		playPair		getPlayerPlay(void);
		void			startAlphaBeta(void);
		void			getStats(t_iaStats *s);
		void			setPlayers(Player *p1, Player *p2);

	private:
		Rules			*_rule;
		Player			*_p1;
		Player			*_p2;
		int				_cutOffs;
		int				_numberOfNodes;
		int				_numberOfMoves;
		int				_cuttedNodes;
		int				_erasedMoves;
		int				_pTurn;
		int				_depth;
		int				_searchRect;
		int				_maxRect;
		Node			_tmpNode;

		std::mutex		_lock;
		LogBlock		*_logBlock;
		int				_timeOut;
};
#endif
