export module ShopInterface;

export class ShopInterface {
public:
    virtual ~ShopInterface() = default;

    // Metode abstracte pentru upgrade-uri
    virtual void upgradeWaitTime() = 0;
    virtual void upgradeSpeed() = 0;
};
;