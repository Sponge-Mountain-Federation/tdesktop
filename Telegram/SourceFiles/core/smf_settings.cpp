/**
 * Author: SpCo
 */
#include "smf_settings.h"

#include "storage/serialize_common.h"

#include "base/debug_log.h"

namespace Core {
SMFSettings::SMFSettings() {}

QByteArray SMFSettings::serialize() const {
    auto size = sizeof(qint32) * 1;
    auto result = QByteArray();
    result.reserve(size);
    {
        QDataStream stream(&result, QIODevice::WriteOnly);
        stream.setVersion(QDataStream::Qt_5_1);
        stream
            << qint32(_antiRecall ? 1 : 0);
    }
    return result;
}

void SMFSettings::addFromSerialized(const QByteArray& serialized) {
    if (serialized.isEmpty()) {
        return;
    }

    QDataStream stream(serialized);
    stream.setVersion(QDataStream::Qt_5_1);

    qint32 antiRecall = _antiRecall;

    if (!stream.atEnd()) {
        stream
            >> antiRecall;
    }

    if (stream.status() != QDataStream::Ok) {
        LOG(("App Error: "
            "Bad data for Core::SMFSettings::constructFromSerialized()"));
        return;
    }
    _antiRecall = (antiRecall == 1);
}

void SMFSettings::resetOnLastLogout() {
    _antiRecall = true;
}
}
