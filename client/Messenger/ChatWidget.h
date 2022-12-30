//
// Created by mrnk on 12/28/22.
//

#ifndef QT1_CHATWIDGET_H
#define QT1_CHATWIDGET_H


#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>

class ChatWidget : public QWidget{
Q_OBJECT
private:
    QLayout *pMainLayout {nullptr};
    QLayout *pUsersInChatLayout {nullptr};
    QLayout *pMessagesLayout {nullptr};
    QLayout *pSendMessageLayout {nullptr};
    QLayout *pButtonLayout{nullptr};

    QLabel *pUsersInChatLabel {nullptr};
    QListWidget *pMessagesList {nullptr};

    QLineEdit *pSendMessageLineEdit {nullptr};

    QPushButton *pSendMessageButton {nullptr};

    QTimer *pRefreshChatTimer {nullptr};

    QFont usersInChatLabelFont{QFont("Arial", 20, QFont::DemiBold)} ;

    std::string usersInChat ;
    std::string usersInChatParsedLabel ;

private slots:
    void sendMessage();
    void acquireChatFile ();
public:
    constexpr static const char * pSendMessageButtonText = "Send";

    explicit ChatWidget(QWidget *, std::string &);

    void initWidget(std::string &);

    void createComponents(std::string &);

    void settleLayouts();

    void addMessage(std::string );

    void restartTimer();

    std::string parseString(std::string );

    ~ChatWidget() override = default;
};


#endif //QT1_CHATWIDGET_H
