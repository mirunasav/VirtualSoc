//
// Created by mrnk on 12/19/22.
//

#ifndef QT1_ADDFRIENDSWIDGET_H
#define QT1_ADDFRIENDSWIDGET_H


#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

class AddFriendsWidget  : public QWidget {
Q_OBJECT
private :

  QLayout *pMainLayout {nullptr};
  QLayout *pSendRequestLayout {nullptr};
  QLayout *pLineEditLayout {nullptr};
  QLayout *pButtonLayout {nullptr};

  QLabel *pSearchUsernameLabel {nullptr};

  QLineEdit *pUsernameLineEdit {nullptr};

  QPushButton *pSendRequestButton {nullptr};

private slots:
    void onSendRequest();

public:
    constexpr static const char *pSendRequestButtonText = "Send Request";
    constexpr static const char *pSearchUserText = "Search User :  ";
    constexpr static const char *pInvalidUserText= "Error! Username Invalid";
    constexpr static const char *pOwnUsername= "Error! You cannot enter your own username!";
    constexpr static const char *pUserAlreadyFriend= "Error! Username already in your friend List";
    constexpr static const char *pRequestAlreadySent= "Error! You already sent a friend request to this username";
    constexpr static const char *pUserBlockedYou= "Error! You cannot send a request to this user";
    constexpr static const char *pUserBlockedByYou= "Error! You have blocked this username";
    constexpr static const char *pRequestSentText= "Your Friend Request Has Been Sent!";

    explicit AddFriendsWidget (QWidget *pParentWindow);

    void initWidget();

    void createComponents();

    void settleLayouts();

    void notificationPopUp(const char * message);

    void keyPressEvent(QKeyEvent * event) override;

    ~AddFriendsWidget() override = default;

signals:
    void requestSent();
};


#endif //QT1_ADDFRIENDSWIDGET_H
