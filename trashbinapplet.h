#ifndef TRASHBINAPPLET_H
#define TRASHBINAPPLET_H

#include "stackfolderapplet.h"
#include <QFileSystemWatcher>

namespace RocketBar{

class TrashBinApplet : public RocketBar::StackFolderApplet
{
    Q_OBJECT
protected:
    QFileSystemWatcher *mFsWatcher;
    QImage mAppletImage;
    bool confirmDeleting;
    QPushButton *trashButton;
    bool removeDir(const QString &dirName);

public:
    TrashBinApplet();
    ~TrashBinApplet();
    virtual QImage image(void);
    virtual QString name();
public slots:
    void directoryChanged(QString str);
    void initApplet(QString str);
    void trash();

};

} //namespace RocketBar

#endif // TRASHBINAPPLET_H
