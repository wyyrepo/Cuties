#ifndef KCUNIBODYPANEL_H
#define KCUNIBODYPANEL_H

#include "kctextpanel.h"

class KCUnibodyPanel : public KCTextPanel
{
    Q_OBJECT
public:
    explicit KCUnibodyPanel(QWidget *parent = 0);
    void drawContent(int x, int y, int width, int height, QTextBlock block, QTextCursor cursor);
    void setPanelWidth(int lineNumberPanelWidth);

signals:

public slots:

private:
    QPixmap foldMark, foldEndMark;
    QPixmap compileErrorMark;
    int foldMarkWidth, foldMarkHeight;
    int errorMarkWidth, errorMarkHeight;
};

#endif // KCUNIBODYPANEL_H