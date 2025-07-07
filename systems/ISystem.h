#ifndef ISYSTEM_H
#define ISYSTEM_H

#include "SystemSignal.h"

class ISystem {
  public:
    virtual ~ISystem() = default;
    virtual void shutdown() {}
    virtual SystemSignal update() = 0;
};

#endif // ISYSTEM_H
