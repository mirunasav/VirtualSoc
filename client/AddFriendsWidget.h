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
    QLayout *pCenterLayout {nullptr};
    QLayout *pLineEditLayout {nullptr};
    QLayout *pLabelLayout {nullptr};
    QLayout *pTextBoxLayout {nullptr};
    QLayout *pButtonLayout{nullptr};

    QPushButton *pSendRequestButton {nullptr};

    QLabel *pSearchUserLabel {nullptr};

    QLineEdit *pSendRequestTextBox {nullptr};
private slots:
    void onSendRequest();

public:
    constexpr static const char *pSendRequestButtonText = "Send Request";
    constexpr static const char *pSearchUserText = "Send Request";
    constexpr static const char *pInvalidUserText= "Error! Username Invalid";
    constexpr static const char *pRequestSentText= "Your Friend Request Has Been Sent!";

    explicit AddFriendsWidget (QWidget *pParentWindow);

    void initWidget();

    void createComponents();

    void settleLayouts();

    bool userExists();

    void notificationPopUp(const char * message);
    ~AddFriendsWidget() override = default;

signals:
    void requestSent();
};


#endif //QT1_ADDFRIENDSWIDGET_H
