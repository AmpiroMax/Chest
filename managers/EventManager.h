#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <functional>
#include <memory>
#include <queue>
#include <typeindex>
#include <unordered_map>
#include <vector>

class EventManager {
  public:
    // ---------- публикация ----------
    template <typename E> void emit(const E &e) { queue_.push(std::make_unique<Wrapper<E>>(e)); }

    // ---------- подписка ------------
    template <typename E> void subscribe(std::function<void(const E &)> h) {
        subs_[typeid(E)].push_back([h](const void *e) { h(*static_cast<const E *>(e)); });
    }

    // ---------- вызов (EventSystem)--
    void update() {
        std::size_t n = queue_.size(); // обрабатываем ТОЛЬКО «старую» партию
        for (std::size_t i = 0; i < n; ++i) {
            auto &ev = queue_.front();
            auto it = subs_.find(ev->type());
            if (it != subs_.end())
                for (auto &f : it->second)
                    f(ev->ptr());
            queue_.pop();
        }
    }

    // вспомогательные операции
    void clear() {
        while (!queue_.empty())
            queue_.pop();
    }
    bool empty() const { return queue_.empty(); }

  private:
    struct Base {
        virtual ~Base() = default;
        virtual std::type_index type() const = 0;
        virtual const void *ptr() const = 0;
    };
    template <typename E> struct Wrapper : Base {
        explicit Wrapper(const E &e) : ev(e) {}
        std::type_index type() const override { return typeid(E); }
        const void *ptr() const override { return &ev; }
        E ev;
    };

    std::unordered_map<std::type_index, std::vector<std::function<void(const void *)>>> subs_;
    std::queue<std::unique_ptr<Base>> queue_;

    static std::queue<std::unique_ptr<Base>> &queuePtr() {
        static std::queue<std::unique_ptr<Base>> dummy;
        return dummy;
    }
};

#endif // EVENT_MANAGER_H
