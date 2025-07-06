#ifndef DEBUG_MANAGER_H
#define DEBUG_MANAGER_H

#include <string>

class DebugManager {
  public:
    void setString(const std::string &s) { str = s; }
    const std::string &getString() const { return str; }

    void setVisible(bool v) { visible = v; }
    bool isVisible() const { return visible; }

    void setChangeStatus(bool sc) { statusChanged = sc; }
    bool wasStatusChanged() const { return statusChanged; }

  private:
    std::string str;
    bool visible = false;
    bool statusChanged = false;
};

#endif // DEBUG_MANAGER_H
