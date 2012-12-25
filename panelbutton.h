#ifndef PANELBUTTON_H
#define PANELBUTTON_H

#include <QDeclarativeItem>

namespace RocketBar {

class PanelButton : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY(QString text
               READ text
               WRITE setText
               NOTIFY textChanged)
public:
    PanelButton(QDeclarativeItem *parent = 0);
    void setText(const QString &text);
    QString text() const;

public slots:
    void clicked();

signals:
    void textChanged();

private:
    QString mText;
};

} //namespace RocketBar

#endif // PANELBUTTON_H
