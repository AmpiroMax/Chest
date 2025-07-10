#ifndef ENTITY
#define ENTITY

#include "Components/IComponent.h"
#include <memory>
#include <typeindex>
#include <unordered_map>

class Entity {
  private:
    static size_t nextId;
    size_t id;
    std::unordered_map<std::type_index, std::unique_ptr<IComponent>> components;

  public:
    Entity() : id(nextId++) {}
    size_t getId() const { return id; }

    template <typename T> void addComponent(std::unique_ptr<T> component) {
        static_assert(std::is_base_of<IComponent, T>::value, "T must inherit from IComponent");
        components[std::type_index(typeid(T))] = std::move(component);
    }

    template <typename T> T *getComponent() const {
        auto it = components.find(std::type_index(typeid(T)));
        if (it != components.end()) {
            return static_cast<T *>(it->second.get());
        }
        return nullptr;
    }

    template <typename T> bool hasComponent() const { return components.find(std::type_index(typeid(T))) != components.end(); }

    template <typename T> void removeComponent() { components.erase(std::type_index(typeid(T))); }
};

#endif