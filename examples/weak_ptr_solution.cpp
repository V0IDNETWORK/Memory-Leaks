#include <iostream>
#include <memory>

class Node
{
public:
    std::weak_ptr<Node> next;

    Node()
    {
        std::cout << "Node created\n";
    }

    ~Node()
    {
        std::cout << "Node destroyed\n";
    }
};

int main()
{
    std::shared_ptr<Node> first =
        std::make_shared<Node>();

    std::shared_ptr<Node> second =
        std::make_shared<Node>();

    first->next = second;
    second->next = first;

    std::cout << "Weak pointer avoids leak\n";

    std::cout << "Objects will now clean correctly\n";

    return 0;
}
