#include "panelbutton.h"
#include <QtCore/QProcess>

RocketBar::PanelButton::PanelButton(QDeclarativeItem *parent)
    : QDeclarativeItem(parent), mText(QString(""))
{
    setFlag(QGraphicsItem::ItemHasNoContents, false);
}

void RocketBar::PanelButton::clicked() {
    qDebug() << "RocketBar::PanelButton::clicked()";
    QProcess::startDetached("/usr/bin/rxvt");
}

void RocketBar::PanelButton::setText(const QString &text)
{
    if (mText != text) {
        mText = text;
        emit textChanged();
    }
}

QString RocketBar::PanelButton::text() const
{
    return mText;
}
