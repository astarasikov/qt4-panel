#ifndef LAUNCHERHANDLER_H
#define LAUNCHERHANDLER_H

#include <QObject>
#include <QList>

namespace RocketBar {

class LauncherHandler : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(QString icon READ icon NOTIFY iconChanged)

protected:
    const QString mCommand;
    const QString mIcon;
    const QString mTitle;

public:
    LauncherHandler(QString _command,
                    QString icon = "",
                    QString title = "");

    QString title() const;
    QString command() const;
    QString icon() const;

    static QList<QObject *> availableApps(void);

signals:
    void descriptionChanged();
    void titleChanged();
    void iconChanged();

public slots:
    void handleClick();
};

} //namespace RocketBar

#endif // LAUNCHERHANDLER_H
