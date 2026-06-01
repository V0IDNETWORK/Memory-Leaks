#include <iostream>
#include <memory>

class Engine
{
public:
    Engine()
    {
        std::cout << "Engine created\n";
    }

    ~Engine()
    {
        std::cout << "Engine destroyed\n";
    }

    void run()
    {
        std::cout << "Engine running\n";
    }
};

void safeFunction()
{
    std::unique_ptr<Engine> engine =
        std::make_unique<Engine>();

    engine->run();

    std::cout << "Leaving function safely\n";
}

int main()
{
    safeFunction();

    std::cout << "Memory cleaned automatically\n";

    return 0;
}
