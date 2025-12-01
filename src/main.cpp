#include <iostream>

enum class OrderType {
    GoodTillCancel,
    FillAndKill
};

enum class Side {
    Buy,
    Sell
};

int main() {
	std::cout << "sanity check\n";
	return 0;
}

