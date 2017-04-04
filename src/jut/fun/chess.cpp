#include "jut/fun/chess.hpp"

// C++ standard

namespace jut {
namespace fun {

namespace chess {

game::game():
    _boards{{{{{   // five deep: vector (1) of array (2) of array (2)
        {{  color::white, man::rook     }}, // optional struct
        {{  color::white, man::knight   }},
        {{  color::white, man::bishop   }},
        {{  color::white, man::king     }},
        {{  color::white, man::queen    }},
        {{  color::white, man::bishop   }},
        {{  color::white, man::knight   }},
        {{  color::white, man::rook     }},
    }}, {{
        {{  color::white, man::pawn     }},
        {{  color::white, man::pawn     }},
        {{  color::white, man::pawn     }},
        {{  color::white, man::pawn     }},
        {{  color::white, man::pawn     }},
        {{  color::white, man::pawn     }},
        {{  color::white, man::pawn     }},
        {{  color::white, man::pawn     }},
    }}, {{
        nullopt, nullopt, nullopt, nullopt,
        nullopt, nullopt, nullopt, nullopt,
    }}, {{
        nullopt, nullopt, nullopt, nullopt,
        nullopt, nullopt, nullopt, nullopt,
    }}, {{
        {{  color::black, man::pawn     }},
        {{  color::black, man::pawn     }},
        {{  color::black, man::pawn     }},
        {{  color::black, man::pawn     }},
        {{  color::black, man::pawn     }},
        {{  color::black, man::pawn     }},
        {{  color::black, man::pawn     }},
        {{  color::black, man::pawn     }},
    }}, {{
        {{  color::black, man::rook     }},
        {{  color::black, man::knight   }},
        {{  color::black, man::bishop   }},
        {{  color::black, man::king     }},
        {{  color::black, man::queen    }},
        {{  color::black, man::bishop   }},
        {{  color::black, man::knight   }},
        {{  color::black, man::rook     }},
    }}}}} { }

}

}
}
