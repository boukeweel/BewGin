#include "Controller.h"
#include <windows.h>
#include <xinput.h>

class Controller::ControllerImpl {
public:
    ControllerImpl() : m_PreviusState{}, m_CurrentState{} {}

    bool ProcessInput() {
        memcpy(&m_PreviusState, &m_CurrentState, sizeof(XINPUT_STATE));
        ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
        DWORD dwResult = XInputGetState(0, &m_CurrentState);
        return dwResult == ERROR_SUCCESS;
    }

    bool IsDpadUpPressed() const {
        return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
    }

    bool IsDpadDownPressed() const {
        return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
    }

    bool IsDpadLeftPressed() const {
        return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
    }

    bool IsDpadRightPressed() const {
        return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
    }

    bool IsDpadUpReleased() const {
        return !(m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) && (m_PreviusState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP);
    }

    bool IsDpadDownReleased() const {
        return !(m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) && (m_PreviusState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
    }

    bool IsDpadLeftReleased() const {
        return !(m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) && (m_PreviusState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
    }

    bool IsDpadRightReleased() const {
        return !(m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) && (m_PreviusState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
    }

private:
    XINPUT_STATE m_PreviusState;
    XINPUT_STATE m_CurrentState;
};

Controller::Controller() : m_Impl(std::make_unique<ControllerImpl>()) {}

Controller::~Controller() = default;

bool Controller::ProcessInput() {
    return m_Impl->ProcessInput();
}

bool Controller::IsDpadUpPressed() const {
    return m_Impl->IsDpadUpPressed();
}

bool Controller::IsDpadDownPressed() const {
    return m_Impl->IsDpadDownPressed();
}

bool Controller::IsDpadLeftPressed() const {
    return m_Impl->IsDpadLeftPressed();
}

bool Controller::IsDpadRightPressed() const {
    return m_Impl->IsDpadRightPressed();
}

bool Controller::IsDpadUpReleased() const {
    return m_Impl->IsDpadUpReleased();
}

bool Controller::IsDpadDownReleased() const {
    return m_Impl->IsDpadDownReleased();
}

bool Controller::IsDpadLeftReleased() const {
    return m_Impl->IsDpadLeftReleased();
}

bool Controller::IsDpadRightReleased() const {
    return m_Impl->IsDpadRightReleased();
}