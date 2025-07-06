#ifndef HID_MANAGER_H
#define HID_MANAGER_H

#include "utils/CoordinateUtils.h"
#include <typeindex>
#include <unordered_map>
#include <vector>

// TODO:
// Я прям вижу как у меня Left == A, хотя вроде при enum class такого быть не должно
// крч надо проверить на потенциальные ошибки приведени одниго перечисления к другому

enum class KeyboardButtons { Unknown = -1, A = 0, W, S, D, Z, X, C, Escape, Left, Right, Up, Down, Count };
enum class MouseButtons { Left, Right, Count };
enum class ButtonStatus { Default, Pressed, Clicked, Released };

// Cast for ButtonStatus to string
const std::unordered_map<ButtonStatus, std::string> ButtonStatusToString = {
    {ButtonStatus::Default, "Default"},
    {ButtonStatus::Pressed, "Pressed"},
    {ButtonStatus::Clicked, "Held"},
    {ButtonStatus::Released, "Released"},
};

const std::unordered_map<KeyboardButtons, std::string> KeyboardButtonToString = {{KeyboardButtons::Unknown, "Unknown"},
                                                                                 {KeyboardButtons::A, "A"},
                                                                                 {KeyboardButtons::W, "W"},
                                                                                 {KeyboardButtons::S, "S"},
                                                                                 {KeyboardButtons::D, "D"},
                                                                                 {KeyboardButtons::Z, "Z"},
                                                                                 {KeyboardButtons::X, "X"},
                                                                                 {KeyboardButtons::C, "C"},
                                                                                 {KeyboardButtons::Escape, "Escape"},
                                                                                 {KeyboardButtons::Left, "Left"},
                                                                                 {KeyboardButtons::Right, "Right"},
                                                                                 {KeyboardButtons::Up, "Up"},
                                                                                 {KeyboardButtons::Down, "Down"},
                                                                                 {KeyboardButtons::Count, "Count"}};

const std::unordered_map<MouseButtons, std::string> MouseButtonToString = {
    {MouseButtons::Left, "Left"}, {MouseButtons::Right, "Right"}, {MouseButtons::Count, "Count"}};

class HIDManager {
  public:
    void setMousePosition(Vec2 pos) { mousePosition = pos; }
    Vec2 getMousePosition() { return mousePosition; }

    void setMouseButtonStatus(MouseButtons button, ButtonStatus status) { mouseStatus[button] = status; }
    ButtonStatus getMouseButtonStatus(MouseButtons button) {
        auto it = mouseStatus.find(button);
        if (it != mouseStatus.end())
            return it->second;
        return ButtonStatus::Default;
    }

    void setKeyboardButtonStatus(KeyboardButtons button, ButtonStatus status) { keyboardStatus[button] = status; }
    ButtonStatus getKeyboardButtonStatus(KeyboardButtons button) {
        auto it = keyboardStatus.find(button);
        if (keyboardStatus.find(button) != keyboardStatus.end())
            return it->second;
        return ButtonStatus::Default;
    }

    void clearStatus() {
        keyboardStatus.clear();
        mouseStatus.clear();
    }

  private:
    Vec2 mousePosition;
    std::unordered_map<KeyboardButtons, ButtonStatus> keyboardStatus;
    std::unordered_map<MouseButtons, ButtonStatus> mouseStatus;
};

#endif // HID_MANAGER_H
