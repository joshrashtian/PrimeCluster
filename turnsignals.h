#ifndef TURNSIGNALS_H
#define TURNSIGNALS_H

#include <QObject>
#include <QQmlEngine>

struct TurnSignals {
    Q_GADGET
    QML_VALUE_TYPE(turnSignals)
    Q_PROPERTY(bool left MEMBER left)
    Q_PROPERTY(bool right MEMBER right)

public:
    bool left = false;
    bool right = false;

    bool operator==(const TurnSignals &) const = default;
};

#endif
