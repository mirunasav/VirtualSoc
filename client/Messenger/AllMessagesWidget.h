//
// Created by mrnk on 12/29/22.
//

#ifndef QT1_ALLMESSAGESWIDGET_H
#define QT1_ALLMESSAGESWIDGET_H


#include <QWidget>
#include <QListWidget>

class AllMessagesWidget : public QWidget {
Q_OBJECT
private:
    QLayout *pMainLayout {nullptr};
    QLayout *pListLayout {nullptr};

    QListWidget *pAllChatsList {nullptr};
private slots:
    void onDoubleClick(QListWidgetItem *);
signals:
     void sendMessage(std::string &);
public:
    explicit AllMessagesWidget(QWidget *pParent);

    void initWidget();

    void createComponents();

    void createListWidget();

    void settleLayouts();

    void acquireAllChatsList(QStringList& friendList);

    ~AllMessagesWidget() override = default;

};


#endif //QT1_ALLMESSAGESWIDGET_H
