#pragma once
#include <memory>

#pragma comment(lib,"xinput.lib")

class Controller {
public:
    Controller();
    ~Controller();

    bool ProcessInput();
    bool IsDpadUpPressed() const;
    bool IsDpadDownPressed() const;
    bool IsDpadLeftPressed() const;
    bool IsDpadRightPressed() const;

    bool IsDpadUpReleased() const;
    bool IsDpadDownReleased() const;
    bool IsDpadLeftReleased() const;
    bool IsDpadRightReleased() const;

private:
    class ControllerImpl;
    std::unique_ptr<ControllerImpl> m_Impl;
};

