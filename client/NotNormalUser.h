//
// Created by mrnk on 12/4/22.
//

#ifndef QT1_NOTNORMALUSER_H
#define QT1_NOTNORMALUSER_H

#include <QWidget>
#include <QSplitter>
#include <QPushButton>

//similat cu appHome : am acelasi feed care apeleaza aceleasi functii ca sa vedem postarile
//dar in stanga am alte optiuni
class NotNormalUser : public  QWidget{
Q_OBJECT
private slots:
    void swapWidgetsReturn();
    void swapWidgetsRefreshFeed();
    void onReturn();
    void onRefresh();
signals:
    void returned();
    void refreshed();
private:
    QWidget * pCentralWidget {nullptr};

    QLayout *pLayout {nullptr};
    QLayout *pMainLayout {nullptr};
    QLayout *pButtonLayout {nullptr};

    QWidget *pButtonWidget {nullptr};
    QWidget *pFeedWidget {nullptr};
    QPushButton *pReturnToStartPage {nullptr};
    QPushButton *pRefreshFeedButton {nullptr};

    QSplitter *pSplitter {nullptr};

    bool isAdmin {false};
public:
    constexpr static const char *pReturnButtonText = "Return";
    constexpr static const char *pRefreshFeedButtonText = "Refresh Feed";

    explicit NotNormalUser(QWidget *pParentWindow, bool);

    void initWidget();

    void createComponents();

    void settleLayouts();

    void styleComponents();

    ~NotNormalUser() override = default;
};


#endif //QT1_NOTNORMALUSER_H
