//
// Created by mrnk on 12/26/22.
//

#ifndef QT1_NEWMESSAGEWIDGET_H
#define QT1_NEWMESSAGEWIDGET_H


#include <QWidget>
#include <QListWidget>
#include <QPushButton>

class NewMessageWidget : public QWidget {
Q_OBJECT
private slots:

    void highlightChecked(QListWidgetItem *);

    void sendMessage();

signals:

    void sendMessage(std::string &);

private:
    QLayout *pMainLayout{nullptr};
    QLayout *pListLayout{nullptr};
    QLayout *pButtonLayout{nullptr};

    QListWidget *pFriendList{nullptr};

    QPushButton *pSendMessageButton{nullptr};
public:
    constexpr static const char *pSendMessageButtonText = "Send Message";

    explicit NewMessageWidget(QWidget *);

    void initWidget();

    void createComponents();

    void createListWidget();

    void settleLayouts();

    void acquireFriendList(QStringList &);

    ~NewMessageWidget() override = default;
};
#endif //QT1_NEWMESSAGEWIDGET_H
