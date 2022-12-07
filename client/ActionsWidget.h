//
// Created by mrnk on 12/2/22.
//

#ifndef QT1_ACTIONSWIDGET_H
#define QT1_ACTIONSWIDGET_H

#include <QWidget>
#include <QPushButton>

class ActionsWidget: public QWidget{
    Q_OBJECT
private slots:
    void onMyProfile(); //mergem la profilul nostru si vedem ce am postat
    void onPost(); //deschide un dialogue box (pop up) si putem posta
    void onAddFriends(); //deschide tot un pop up? poate
    void onSendMessage(); //deschidem o fereastra de messenger
    void onSettings(); //deschidem o fereastra cu setari
    void onLogout(); //deconectez userul de la server si ma intorc la run window

private:

    QPushButton *pMyProfileButton {nullptr};
    QPushButton *pPostButton {nullptr};
    QPushButton *pAddFriendsButton {nullptr};
    QPushButton *pSendMesssageButton {nullptr};
    QPushButton *pSettingsButton {nullptr};
    QPushButton *pLogoutButton {nullptr};

    QLayout *pActionsLayout {nullptr};

signals:
    void loggedOut();
public:
    //constantele
    constexpr static const char *pMyProfileButtonText = "My Profile";
    constexpr static const char *pPostButtonText = "New Post";
    constexpr static const char *pAddFriendsButtonText = "Add Friends";
    constexpr static const char *pSendMesssageButtonText = "Send a Message";
    constexpr static const char *pSettingsButtonText = "Settings";
    constexpr static const char *pLogoutButtonText = "Logout";

public:
    //functiile
    explicit ActionsWidget(QWidget *pParentWindow);

    //initWidget: createComponents, settleLayouts, adjustLayouts
    void initWidget();

    void createComponents();
    void settleLayouts();
    void adjustLayouts(); //minimum /maximum size for buttons, alignment

    void newPostPopUp();
    ~ActionsWidget() override;

};


#endif //QT1_ACTIONSWIDGET_H
