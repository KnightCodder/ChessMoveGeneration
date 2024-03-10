#include <iostream>
#include <set>

class sad {
    public:
    int value;

    sad(int v)
    {
        value = v;
    }
};

int main() {
    sad a(1), b(2), c(3), d(4);
    std::set<sad*> mySet = {&a, &b, &c, &d};

    // Find the element in the set
    auto it = mySet.find(&a);

    // If the element is found, erase it
    if (it != mySet.end()) {
        mySet.erase(it);
    }

    for (auto i : mySet)
    {
        std::cout << i->value << std::endl;
    }


    return 0;
}
