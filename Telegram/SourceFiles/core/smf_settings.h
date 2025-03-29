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

    [[nodiscard]] bool spamFilter() const {
        return _spamFilter;
    }

    void setSpamFilter(bool newValue) {
        _spamFilter = newValue;
    }

private:
    bool _antiRecall = true;
    bool _spamFilter = true;
};
}
