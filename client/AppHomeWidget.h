

#ifndef QT1_APPHOMEWIDGET_H
#define QT1_APPHOMEWIDGET_H


#include "MainWindow.h"
#include <QWidget>
#include <QSplitter>
#include "FeedWidget.h"
class AppHomeWidget : public QWidget{
Q_OBJECT
private slots:
    void swapWidgetsLogOut();
private:
    QWidget * pCentralWidget {nullptr};

    QLabel *pHomeWidgetTitle {nullptr};
    QLayout *pLayout {nullptr};
    QLayout *pMainLayout {nullptr};


    QWidget * pFeedWidget { nullptr };
    QWidget * pActionsWidget { nullptr };

    QSplitter *pSplitter {nullptr};
public:
    constexpr static const char *pHomeWidgetTitleLabel = "Home";
    explicit AppHomeWidget(QWidget *pParentWindow);

    void initWidget();

    void createComponents();

    void settleLayouts();

    void styleComponents();

    ~AppHomeWidget() override;



};



#endif //QT1_APPHOMEWIDGET_H
