//
// Created by mrnk on 12/14/22.
//

#ifndef QT1_FRIENDSMENUWIDGET_H
#define QT1_FRIENDSMENUWIDGET_H


#include <QWidget>
#include <QSplitter>
#include <QLabel>
#include <QPushButton>

class FriendsMenuWidget : public QWidget {
Q_OBJECT
private slots:
    void swapWidgetsAddFriends();
    void swapWidgetsFriendList();
    void swapWidgetsFriendRequests();
private:
    QWidget *pChangeableWidget{nullptr};
    QWidget *pButtonsWidget {nullptr};

    QLayout *pMainLayout {nullptr};//layoutul cu label si cu ce schimb si cu actiunile
    QLayout *pButtonsLayout {nullptr};

    QLabel *pFriendsLabel {nullptr};
    QFont FriendsLabelFont{ QFont("Arial", 40, QFont::Bold)} ;

    QPushButton *pAddFriendsButton {nullptr};
    QPushButton *pMyFriendsButton {nullptr};
    QPushButton *pFriendRequestsButton {nullptr};

    QSplitter *pHorizontalSplitter {nullptr};//intre butoane si lista prieteni
    QSplitter *pVerticalSplitter {nullptr};//intre label si partea de jos
public:
    constexpr static const char *pFriendsListLabelText = "My Friends";
    constexpr static const char *pFriendsAddFriendsLabelText = "Add Friends";

    constexpr static const char *pMyFriendsButtonText = "My Friends";
    constexpr static const char *pAddFriendsButtonText = "Add Friends";
    constexpr static const char *pFriendRequestsButtonText= "Friend Requests";


    explicit FriendsMenuWidget(QWidget *pParentWindow);

    void initWidget();

    void createComponents();

    void settleLayouts();

    void styleComponents();

    ~FriendsMenuWidget() override = default;


};


#endif //QT1_FRIENDSMENUWIDGET_H
