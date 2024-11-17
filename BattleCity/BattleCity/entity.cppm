export module entity;

import <iostream>;
import <vector>;
import <memory>;

export class Entity {
public:
    virtual ~Entity() = default;
    virtual void display() const = 0;
};

export class Bullet : public Entity {
public:
    void display() const override {}
};



export class PowerUp : public Entity {
public:
    void display() const override {}
};

export class Bomb : public Entity {
public:
    void display() const override {}
};

export namespace game {
    class Map {
    public:
        Map() = default;
        void addEntity(std::shared_ptr<Entity> entity) {
            m_entities.push_back(entity);
        }

        void displayEntities() const {
            for (const auto& entity : m_entities) {
                entity->display();
            }
        }

    private:
        std::vector<std::shared_ptr<Entity>> m_entities;
    };
}
