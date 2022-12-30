//
// Created by mrnk on 12/29/22.
//

#ifndef QT1_ALLMESSAGESWIDGET_H
#define QT1_ALLMESSAGESWIDGET_H


#include <QWidget>
#include <QListWidget>
#include <QPushButton>

class AllMessagesWidget : public QWidget {
Q_OBJECT
private:
    QLayout *pMainLayout {nullptr};
    QLayout *pListLayout {nullptr};

    QPushButton *pOpenChatButton {nullptr};

    QListWidget *pAllChatsList {nullptr};

    std::string chatSelected;
private slots:
    void onClick(QListWidgetItem *);
    void sendMessage();
signals:
     void sendMessage(std::string &);
public:
    constexpr static const char * pOpenChatButtonText = "Open Chat";

    explicit AllMessagesWidget(QWidget *pParent);

    void initWidget();

    void createComponents();

    void createListWidget();

    void settleLayouts();

    void acquireAllChatsList(QStringList& friendList);

    ~AllMessagesWidget() override = default;

};


#endif //QT1_ALLMESSAGESWIDGET_H
