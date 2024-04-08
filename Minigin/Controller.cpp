#include <iostream>

#include "InputManager.h"
#include <XInput.h>
#pragma comment(lib,"xinput.lib")

namespace bew
{
    class InputManager::ControllerImpl
    {

    public:
        void HandleControllerContinually(const std::vector<CommandInfo>& Commands)
        {
            UpdateControllerInfo();

            for (auto&& command : Commands)
            {
                for (auto&& controllerButton : command.m_Action.ControllerButtons)
                {
                    if (command.m_ButtonState == ButtonState::Held && IsHeld(controllerButton, command.m_ControllerIndex))
                    {
                        command.m_Command->Execute();
                        break;
                    }
                    else if (command.m_ButtonState == ButtonState::Down && IsDownThisFrame(controllerButton, command.m_ControllerIndex))
                        command.m_Command->Execute();
                    else if (command.m_ButtonState == ButtonState::Up && IsUpThisFrame(controllerButton, command.m_ControllerIndex))
                        command.m_Command->Execute();
                }
            }
        }

    private:

        struct XINPUT_GAMEPAD_STATE
        {
            XINPUT_STATE CurrentControllerState;
            XINPUT_STATE PriviusControllerState;
            WORD ButtonsPressedThisFrame;
            WORD ButtonsReleasedThisFrame;
        };

        bool IsDownThisFrame(WORD button, int controllerIndex = 0) const
        {
            return m_ControllerStates[controllerIndex].ButtonsPressedThisFrame & button;
        }
        bool IsUpThisFrame(WORD button, int controllerIndex = 0) const
        {
            return m_ControllerStates[controllerIndex].ButtonsReleasedThisFrame & button;
        }
        bool IsHeld(WORD button, int controllerIndex = 0) const
        {
            return m_ControllerStates[controllerIndex].CurrentControllerState.Gamepad.wButtons & button;
        }

        void UpdateControllerInfo()
        {
            //todo find a way to detect how many controllers are connected 
            const int joystickCount = XUSER_MAX_COUNT;
            m_ControllerStates.resize(joystickCount);

            for (int controllerIndex = 0; controllerIndex < joystickCount; controllerIndex++)
            {
                XINPUT_GAMEPAD_STATE& gamepadState = m_ControllerStates[controllerIndex];

                memcpy(&gamepadState.PriviusControllerState, &gamepadState.CurrentControllerState, sizeof(XINPUT_STATE));

                ZeroMemory(&gamepadState.CurrentControllerState, sizeof(XINPUT_STATE));

            	XInputGetState(controllerIndex, &gamepadState.CurrentControllerState);

                WORD buttonChanges = gamepadState.CurrentControllerState.Gamepad.wButtons ^ gamepadState.PriviusControllerState.Gamepad.wButtons;
                gamepadState.ButtonsPressedThisFrame = buttonChanges & gamepadState.CurrentControllerState.Gamepad.wButtons;
                gamepadState.ButtonsReleasedThisFrame = buttonChanges & ~gamepadState.CurrentControllerState.Gamepad.wButtons;
            }
        }

        std::vector<XINPUT_GAMEPAD_STATE> m_ControllerStates{};
    };
}

bew::InputManager::InputManager() : m_ControllerImpl{std::make_unique<ControllerImpl>()}
{
}

bew::InputManager::~InputManager() = default;

void bew::InputManager::HandleControllerContinually() 
{
    m_ControllerImpl->HandleControllerContinually(m_Commands);
}

