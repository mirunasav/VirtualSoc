//
// Created by mrnk on 12/4/22.
//

#ifndef QT1_NOTLOGGEDIN_H
#define QT1_NOTLOGGEDIN_H

#include <QWidget>
#include <QSplitter>
#include <QPushButton>

//similat cu appHome : am acelasi feed care apeleaza aceleasi functii ca sa vedem postarile
//dar in stanga am alte optiuni
class NotLoggedIn : public  QWidget{
Q_OBJECT
private slots:
    void swapWidgetsReturn();
    void onReturn();
signals:
    void returned();
private:
    QWidget * pCentralWidget {nullptr};

    QLayout *pLayout {nullptr};
    QLayout *pMainLayout {nullptr};
    QLayout *pButtonLayout {nullptr};

    QWidget *pButtonWidget {nullptr};
    QWidget *pFeedWidget {nullptr};
    QPushButton *pReturnToStartPage {nullptr};

    QSplitter *pSplitter {nullptr};
public:
    constexpr static const char *pReturnButtonText = "Return";

    explicit NotLoggedIn(QWidget *pParentWindow);

    void initWidget();

    void createComponents();

    void settleLayouts();

    void styleComponents();

    ~NotLoggedIn() override = default;
};


#endif //QT1_NOTLOGGEDIN_H
