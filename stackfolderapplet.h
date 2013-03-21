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

namespace RocketBar {

    class StackFolderApplet : public Applet{
        Q_OBJECT
    protected:
        QMenu *mMenu;
        QWidget *mWidget;
        QDir folder;
        QStack<QFileInfo> *folderStack;
        QGridLayout *layout;
        QPushButton *backButton;
        QPushButton *openDolphin;
        QListWidget *listItem;

    public:
        enum {
            Width = 500,
            Height = 400,
        };

        StackFolderApplet();
        virtual ~StackFolderApplet();
        QImage image(void);
        QString name();
        void initApplet(QString path);

    public slots:
        virtual void handleClick();
        virtual void handleClick(int x, int y);
        virtual void openFile(QListWidgetItem* item);
        virtual void openFolder();
        virtual void goBack();
        virtual void showMenu();
    };
}


#endif // STACKFOLDERAPPLET_H
