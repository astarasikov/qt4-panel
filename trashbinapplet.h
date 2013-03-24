#ifndef TRASHBINAPPLET_H
#define TRASHBINAPPLET_H

#include "stackfolderapplet.h"
#include <QFileSystemWatcher>
#include <QMenu>

namespace RocketBar{

class TrashBinApplet : public RocketBar::StackFolderApplet
{
    Q_OBJECT
protected:
    QFileSystemWatcher *mFsWatcher;
    QImage mAppletImage;
    QMenu *mMenu;

    QPushButton *trashButton;
    QString trashPath();
    void clearDir(QString str);

public:
    TrashBinApplet();
    ~TrashBinApplet();
    virtual QImage image(void);
    virtual QString name();
public slots:
    void directoryChanged(QString str);
    void initApplet(QString str);
    void clearTrash();
    virtual void handleContextMenu(int x, int y);
};

} //namespace RocketBar

#endif // TRASHBINAPPLET_H
