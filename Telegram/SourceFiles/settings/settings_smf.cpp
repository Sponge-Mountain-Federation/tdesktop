/**
 * Author: SpCo
 */
#include "settings_smf.h"

#include "boxes/connection_box.h"
#include "boxes/stickers_box.h"
#include "ui/wrap/vertical_layout.h"
#include "ui/wrap/slide_wrap.h"
#include "ui/widgets/fields/input_field.h"
#include "ui/widgets/checkbox.h"
#include "ui/vertical_list.h"
#include "lang/lang_keys.h"
#include "window/window_session_controller.h"
#include "window/window_controller.h"
#include "storage/localstorage.h"
#include "core/application.h"
#include "data/data_session.h"
#include "styles/style_settings.h"

namespace Settings {
void SetupChat(
    not_null<Window::SessionController*> controller,
    not_null<Ui::VerticalLayout*> container) {
    Ui::AddDivider(container);
    Ui::AddSkip(container);

    Ui::AddSubsectionTitle(container, tr::lng_settings_messages());

    auto wrap = object_ptr<Ui::VerticalLayout>(container);
    const auto inner = wrap.data();
    container->add(object_ptr<Ui::OverrideMargins>(
        container,
        std::move(wrap),
        QMargins(0, 0, 0, st::settingsCheckbox.margin.bottom())));

    const auto checkbox = [&](const QString &label, bool checked) {
        return object_ptr<Ui::Checkbox>(
            container,
            label,
            checked,
            st::settingsCheckbox);
    };
    const auto add = [&](const QString &label, bool checked, auto &&handle) {
        inner->add(
            checkbox(label, checked),
            st::settingsCheckboxPadding
        )->checkedChanges(
        ) | rpl::start_with_next(
            std::move(handle),
            inner->lifetime());
    };

    add(
        tr::lng_settings_messages_anti_recall(tr::now),
        Core::App().settings().smf().antiRecall(),
        [=](bool checked) {
            Core::App().settings().smf().setAntiRecall(checked);
            Core::App().saveSettings();
        });

    Ui::AddSkip(container, st::settingsCheckboxesSkip);
    Ui::AddSkip(container);
}

SMF::SMF(QWidget* parent, not_null<Window::SessionController*> controller)
: Section(parent)
, _controller(controller){
    setupContent(_controller);
}

rpl::producer<QString> SMF::title() {
    return tr::lng_settings_smf();
}

void SMF::setupContent(not_null<Window::SessionController*> controller) {
    const auto content = Ui::CreateChild<Ui::VerticalLayout>(this);

    SetupChat(controller, content);

    Ui::ResizeFitChild(this, content);
}
}
