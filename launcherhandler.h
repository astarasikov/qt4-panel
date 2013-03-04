#ifndef LAUNCHERHANDLER_H
#define LAUNCHERHANDLER_H

#include <QObject>

namespace RocketBar {

class LauncherHandler : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)

protected:
    const QString mTitle;
    const QString mCommand;

public:
    LauncherHandler(QString _title, QString _command);

    QString title() const;

signals:
    void titleChanged();
    void imagePathChanged();

public slots:
    void handleClick();
};

} //namespace RocketBar

#endif // LAUNCHERHANDLER_H
