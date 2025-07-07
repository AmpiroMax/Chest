#ifndef I_MANAGER_H
#define I_MANAGER_H
struct IManager {
    virtual ~IManager() = default;
    virtual void shutdown() {} // по умолчанию делает ничего
};
#endif
