#include <iostream>
#include <cstdint>
#include <vector>
#include <stdexcept>
#include <format>
#include <memory>
#include <list>

enum class OrderType {
    GoodTillCancel,
    FillAndKill
};

enum class Side {
    Buy,
    Sell
};

using Price = std::int32_t;
using Quantity = std::uint32_t;
using OrderId = std::uint64_t;

struct LevelInfo {
    Price price_;
    Quantity quantity_;
};

using LevelInfos = std::vector<LevelInfo>;

class OrderBookLevelInfos {
    public:
        OrderBookLevelInfos(const LevelInfos& bids, const LevelInfos& asks)
            : bids_{ bids }, asks_{ asks }
        { }
        const LevelInfos& GetBids() const { return bids_; }
        const LevelInfos& getAsks() const { return asks_; }

    private:
        LevelInfos bids_;
        LevelInfos asks_;
};

class Order {
    public:
        Order(OrderType orderType, OrderId orderId, Side side, Price price, Quantity quantity)
            : orderType_{ orderType }
            , orderId_{ orderId }
            , side_{ side }
            , price_{ price }
            , initialQuantity_{ quantity }
            , remainingQuantity_{ quantity }
        { }
        OrderType GetOrderType() const { return orderType_; }
        OrderId GetOrderId() const { return orderId_; }
        Side GetSide() const { return side_; }
        Price GetPrice() const { return price_; }
        Quantity GetInitialQuantity() const { return initialQuantity_; }
        Quantity GetRemainingQuantity() const { return remainingQuantity_; }
        Quantity GetFilledQuantity() const { return GetInitialQuantity() - GetRemainingQuantity(); }

        void Fill(Quantity quantity) {
            if(quantity > GetRemainingQuantity()) {
                throw std::logic_error(std::format("Order ({}) cannot be filled for more than its remaining quantity.", GetOrderId()));
            }
            remainingQuantity_ -= quantity;
        }
    private:
        OrderType orderType_;
        OrderId orderId_;
        Side side_;
        Price price_;
        Quantity initialQuantity_;
        Quantity remainingQuantity_;
};

using OrderPointer = std::shared_ptr<Order>;
using OrderPointers = std::list<OrderPointer>;

class OrderModify {
    public:
        OrderModify(OrderId orderId, Side side, Price price, Quantity quantity)
            : orderId_{ orderId }
            , side_{ side }
            , price_{ price }
            , quantity_{ quantity }
        {}
        OrderId GetOrderId() const { return orderId_; }
        Side GetOrderSide() const { return side_; }
        Price GetPrice() const { return price_; }
        Quantity GetQuantity() const { return quantity_; }

        OrderPointer toOrderPointer(OrderType type) const {
            return std::make_shared<Order>(type, GetOrderId(), GetOrderSide(), GetPrice(), GetQuantity());
        }

    private:
        OrderId orderId_;
        Side side_;
        Price price_;
        Quantity quantity_;
};



int main() {
	std::cout << "sanity check\n";
	return 0;
}

