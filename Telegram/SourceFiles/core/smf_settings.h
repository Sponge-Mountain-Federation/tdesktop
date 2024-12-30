/**
 * Author: SpCo
 */
#pragma once

namespace Core {
class SMFSettings final {
public:
    SMFSettings();

    [[nodiscard]] QByteArray serialize() const;
    void addFromSerialized(const QByteArray& serialized);

    void resetOnLastLogout();

    [[nodiscard]] bool antiRecall() const {
        return _antiRecall;
    }

    void setAntiRecall(bool newValue) {
        _antiRecall = newValue;
    }

private:
    bool _antiRecall = true;
};
}
