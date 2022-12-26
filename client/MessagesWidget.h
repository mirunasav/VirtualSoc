//
// Created by mrnk on 12/26/22.
//

#ifndef QT1_MESSAGESWIDGET_H
#define QT1_MESSAGESWIDGET_H


#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QSplitter>

class MessagesWidget : public QWidget{
Q_OBJECT
private slots:
    void swapWidgetsAllMessages();
    void swapWidgetsNewMessage();

private:
    QLayout *pMainLayout{nullptr};
    QLayout *pButtonsLayout{nullptr};

    QWidget *pChangeableWidget {nullptr};
    QWidget *pButtonsWidget{nullptr};

    QLabel *pMessagesLabel {nullptr};
    QFont MessagesLabelFont{QFont("Arial", 40, QFont::Bold)} ;

    QPushButton *pAllMessagesButton {nullptr};
    QPushButton *pNewMessageButton {nullptr};

    QSplitter *pHorizontalSplitter {nullptr};
    QSplitter *pVerticalSplitter {nullptr};

public:
    constexpr static const char *pAllMessagesLabelText = "All Messages";
    constexpr static const char *pNewMessageLabelText = "Send New Message";

    constexpr static const char *pAllMessagesButtonText = "All Messages";
    constexpr static const char *pNewMessageButtonText = "New Message";

    explicit MessagesWidget(QWidget *);

    void initWidget();

    void createComponents();

    void settleLayouts();

    void styleComponents();

    ~MessagesWidget() override = default;

};


#endif //QT1_MESSAGESWIDGET_H
