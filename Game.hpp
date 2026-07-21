#ifndef GAME_HPP
#define GAME_HPP

struct Player {
    unsigned long start_time;
    unsigned int turn_number;
};

class Game {
    public:
        Game();
    private:
        Player red;
        Player blue;
};

#endif
