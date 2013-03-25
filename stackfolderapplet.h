#ifndef STACKFOLDERAPPLET_H
#define STACKFOLDERAPPLET_H

#include "applet.h"
#include <QMenu>
#include <QWidget>
#include <QStack>
#include <QListWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QFileIconProvider>
#include <QPushButton>
#include <QContextMenuEvent>

namespace RocketBar {

class StackFolderApplet : public Applet {
    Q_OBJECT

protected:
    QString mDirPath;
    QWidget *mWidget;
    QDir folder;
    QStack<QFileInfo> *mFolderStack;
    QGridLayout *mLayout;
    QPushButton *mBackButton;
    QPushButton *mOpenFile;
    QListWidget *mListItem;

public:
    enum {
        Width = 500,
        Height = 400
    };

    StackFolderApplet(QString path = QDir::homePath());
    virtual ~StackFolderApplet();
    virtual QImage image(void);
    virtual QString name();
    void initApplet(QString path);
    void initFileList();

public slots:
    virtual void openFile(QListWidgetItem* item);
    virtual void openFolder();
    virtual void goBack();
    virtual void handleClick(int x, int y);
};

} //namespace RocketBar

#endif // STACKFOLDERAPPLET_H
