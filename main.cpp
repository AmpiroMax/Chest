// main.cpp  (корень проекта)

#ifdef EDITOR_BUILD
#include "applications/EditorApp.h"
#else
#include "applications/GameApp.h"
#endif

int main() {
#ifdef EDITOR_BUILD
    EditorApp app;
#else
    GameApp app;
#endif
    app.run();
    return 0;
}