#include <iostream>

class Player
{
public:
    Player()
    {
        std::cout << "Player created\n";
    }

    ~Player()
    {
        std::cout << "Player destroyed\n";
    }
};

void createLeak()
{
    Player* player = new Player();

    std::cout << "Using player object...\n";

    // Forgot to delete memory
    // delete player;
}

int main()
{
    for (int i = 0; i < 5; ++i)
    {
        createLeak();
    }

    std::cout << "Program finished\n";

    return 0;
}
