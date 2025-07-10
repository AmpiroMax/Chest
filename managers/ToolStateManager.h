#ifndef TOOL_STATE_MANAGER_H
#define TOOL_STATE_MANAGER_H

#include "IManager.h"

enum class ToolType { Cursor, Rect, Polygon, Circle };

class ToolStateManager : public IManager {
  public:
    void setActiveTool(ToolType t) { activeTool = t; }
    ToolType getActiveTool() const { return activeTool; }

  private:
    ToolType activeTool = ToolType::Cursor;
};

#endif // TOOL_STATE_MANAGER_H