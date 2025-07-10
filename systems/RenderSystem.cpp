#include "systems/RenderSystem.h"
#include "core/Components/MapSectorComponent.h"
#include "core/Components/PhysicsComponent.h"
#include "core/Components/RenderComponent.h"
#include "utils/CoordinateUtils.h"
#include <SFML/Graphics.hpp>

SystemSignal RenderSystem::update() {
    auto &window = windowManager.getWindow();
    window.clear(sf::Color::Black);

    sf::View view;
    Vec2 camCenterSFMLCoords = fromWorldToRender(cameraManager.getCenter());
    Vec2 viewport = cameraManager.getViewportSize();
    float zoom = cameraManager.getZoom();

    view.setCenter(camCenterSFMLCoords);
    view.setSize(viewport / zoom);
    window.setView(view);

    // renderMap(window);
    renderEntities(window);

    if (debugManager.isVisible() && !debugManager.getString().empty()) {
        static sf::Font font;
        static bool loaded = false;
        if (!loaded) {
            font.loadFromFile("resources/fonts/RobotoMono-VariableFont_wght.ttf");
            loaded = true;
        }
        sf::Text debugText;
        debugText.setFont(font);
        debugText.setCharacterSize(10);
        debugText.setFillColor(sf::Color::White);
        debugText.setString(debugManager.getString());
        debugText.setPosition(8, 8);

        sf::View oldView = window.getView();
        window.setView(window.getDefaultView());
        window.draw(debugText);
        window.setView(oldView);
    }
    // window.display();
    return SystemSignal::None;
}

// void RenderSystem::renderMap(sf::RenderWindow &window) {
//     for (auto *entity : entityManager.getAll()) {
//         auto *mapSector = entity->getComponent<MapSectorComponent>();
//         auto *rend = entity->getComponent<RenderComponent>();
//         if (mapSector && rend) {
//             std::vector<sf::Vertex> poly;
//             for (const auto &v : mapSector->vertices) {
//                 Vec2 renderCoordinates = fromWorldToRender(v);
//                 poly.push_back(sf::Vertex(renderCoordinates));
//             }
//             for (auto &vert : poly)
//                 vert.color = sf::Color::White;
//             window.draw(&poly[0], poly.size(), sf::TriangleFan);
//         }
//     }
// }

std::unique_ptr<sf::Sprite> RenderSystem::makeBoxDrawable(const PhysicsComponent *phys, const RenderComponent *rend) {
    Vec2 worldPos = phys->getPosition();
    Vec2 screenPos = fromWorldToRender(worldPos);
    float angle = fromWorldAngleToRender(phys->getRotation()); // Минус — чтобы привести к системе SFML (по часовой!)

    const auto &texture = resourceManager.getTexture(rend->textureName);

    Vec2 physicsSize = phys->dynamicProperties.bodySize * RENDER_SCALE;
    auto sprite = std::make_unique<sf::Sprite>(texture);
    sprite->setPosition(screenPos.x, screenPos.y);
    sprite->setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
    sprite->setScale(physicsSize.x / texture.getSize().x, physicsSize.y / texture.getSize().y);
    sprite->setRotation(angle); // SFML: угол в градусах по часовой!
    return sprite;
}

std::unique_ptr<sf::CircleShape> RenderSystem::makeCircleDrawable(const PhysicsComponent *phys, const RenderComponent *rend) {
    Vec2 worldPos = phys->getPosition();
    Vec2 screenPos = fromWorldToRender(worldPos);
    float angle = fromWorldAngleToRender(phys->getRotation());

    const auto &texture = resourceManager.getTexture(rend->textureName);

    float radiusPx = phys->dynamicProperties.bodyRadius * RENDER_SCALE;
    auto shape = std::make_unique<sf::CircleShape>(radiusPx);
    shape->setOrigin(radiusPx, radiusPx);
    shape->setPosition(screenPos.x, screenPos.y);
    shape->setTexture(&texture);
    shape->setRotation(angle);
    return shape;
}

std::unique_ptr<sf::VertexArray> RenderSystem::makePolygonDrawable(const PhysicsComponent *phys, const RenderComponent *rend) {
    Vec2 worldPos = phys->getPosition();
    float angle = fromWorldAngleToRender(phys->getRotation()); // Угол против часовой
    float angleRad = angle * DEG2RAD;                          // В радианы для ручного поворота
    const auto &polyVerts = phys->dynamicProperties.bodyVertices;

    auto arr = std::make_unique<sf::VertexArray>(sf::TriangleFan, polyVerts.size());
    for (size_t i = 0; i < polyVerts.size(); ++i) {
        // Вращаем вершину вокруг центра (0,0), потом переносим в мировые координаты
        float x = polyVerts[i].x;
        float y = polyVerts[i].y;
        float xr = x * cos(angleRad) + y * sin(angleRad);
        float yr = -x * sin(angleRad) + y * cos(angleRad);

        Vec2 vertexScreen = fromWorldToRender(worldPos + Vec2(xr, yr));
        (*arr)[i].position = sf::Vector2f(vertexScreen.x, vertexScreen.y);
        (*arr)[i].color = sf::Color::White;
    }
    return arr;
}

std::unique_ptr<sf::Drawable> RenderSystem::makeDrawableForEntity(const PhysicsComponent *phys, const RenderComponent *rend) {
    if (!phys || !rend)
        return nullptr;

    switch (phys->dynamicProperties.bodyShape) {
    case PhysicBodyDef::BodyShape::Box:
        return makeBoxDrawable(phys, rend);
    case PhysicBodyDef::BodyShape::Circle:
        return makeCircleDrawable(phys, rend);
    case PhysicBodyDef::BodyShape::Polygon:
        return makePolygonDrawable(phys, rend);
    }
    return nullptr;
}

void RenderSystem::renderEntities(sf::RenderWindow &window) {
    for (auto *entity : entityManager.getAll()) {
        auto *phys = entity->getComponent<PhysicsComponent>();
        auto *rend = entity->getComponent<RenderComponent>();
        auto drawable = makeDrawableForEntity(phys, rend);
        if (!drawable)
            continue;

        // Для полигона надо указать текстуру отдельно:
        if (phys && phys->dynamicProperties.bodyShape == PhysicBodyDef::BodyShape::Polygon)
            window.draw(*dynamic_cast<sf::VertexArray *>(drawable.get()), &resourceManager.getTexture(rend->textureName));
        else
            window.draw(*drawable);
    }
}
