/** @file jut/fun/chess.hpp Models the game of chess. */

#ifndef JUT_FUN_CHESS_INCLUDED
#define JUT_FUN_CHESS_INCLUDED

// C++ standard
#include <array>
#include <vector>
#include <experimental/optional>

using std::experimental::nullopt;
using std::experimental::optional;

namespace jut { // Jeff's UTilitites
namespace fun { // FUN and games

namespace chess {

int const rank_count = 8, file_count = 8;   // by time-honored tradition
enum class color { white, black };
enum class man { pawn, rook, knight, bishop, queen, king };
struct occupation { color side; man kind; };

using cell_state = optional<occupation>;

using board = std::array<                   // algebraic notation (e.g., a1)
    std::array<cell_state, rank_count>,     // is file-major; think file and
    file_count>;                            // rank, not rank and file

class game {
    std::vector<board> _boards;
  public:

    game();
};

}

}
}

#endif
