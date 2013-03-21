#ifndef LAUNCHERHANDLER_H
#define LAUNCHERHANDLER_H

#include <QObject>

namespace RocketBar {

class LauncherHandler : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(QString description READ description NOTIFY descriptionChanged)

protected:
    const QString mTitle;
    const QString mCommand;
    const QString mDescription;

public:
    LauncherHandler(QString _title, QString _command,
                    QString _description=tr("Launch Application"));

    QString title() const;
    QString description() const;

signals:
    void titleChanged();
    void descriptionChanged();
    void imagePathChanged();

public slots:
    void handleClick();
};

} //namespace RocketBar

#endif // LAUNCHERHANDLER_H
