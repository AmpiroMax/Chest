#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "core/Components/MapSectorComponent.h"
#include "core/Components/PhysicsComponent.h"
#include "core/Components/RenderComponent.h"
#include "managers/CameraManager.h"
#include "managers/DebugManager.h"
#include "managers/EntityManager.h"
#include "managers/ResourceManager.h"
#include "managers/WindowManager.h"
#include "systems/ISystem.h"

class RenderSystem : public ISystem {
  public:
    RenderSystem(WindowManager &winMgr, EntityManager &entMgr, ResourceManager &resMgr, CameraManager &camMgr,
                 DebugManager &debMgr)
        : windowManager(winMgr), entityManager(entMgr), resourceManager(resMgr), cameraManager(camMgr),
          debugManager(debMgr) {}

    SystemSignal update() override;

  private:
    void renderMap(sf::RenderWindow &window);
    void renderEntities(sf::RenderWindow &window);
    void renderButtons(sf::RenderWindow &window);

    // В RenderSystem.h (в секции private):

    std::unique_ptr<sf::Sprite> makeBoxDrawable(const PhysicsComponent *phys, const RenderComponent *rend);

    std::unique_ptr<sf::CircleShape> makeCircleDrawable(const PhysicsComponent *phys, const RenderComponent *rend);

    std::unique_ptr<sf::VertexArray> makePolygonDrawable(const PhysicsComponent *phys, const RenderComponent *rend);

    std::unique_ptr<sf::Drawable> makeDrawableForEntity(const PhysicsComponent *phys, const RenderComponent *rend);

    WindowManager &windowManager;
    EntityManager &entityManager;
    ResourceManager &resourceManager;
    CameraManager &cameraManager;
    DebugManager &debugManager;
};

#endif // RENDER_SYSTEM_H