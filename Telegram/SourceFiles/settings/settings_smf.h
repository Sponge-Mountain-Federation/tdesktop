/**
* Author: SpCo
 */
#pragma once

#include "settings/settings_common_session.h"

namespace Window {
class Controller;
}

namespace Settings {
void SetupChat(
    not_null<Window::SessionController*> controller,
    not_null<Ui::VerticalLayout*> container);

class SMF : public Section<SMF> {
public:
    SMF(QWidget* parent, not_null<Window::SessionController*> controller);

    [[nodiscard]] rpl::producer<QString> title() override;

private:
    void setupContent(not_null<Window::SessionController*> controller);

    const not_null<Window::SessionController*> _controller;
};
}
