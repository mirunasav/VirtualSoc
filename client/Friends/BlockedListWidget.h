//
// Created by mrnk on 1/10/23.
//

#ifndef QT1_BLOCKEDLISTWIDGET_H
#define QT1_BLOCKEDLISTWIDGET_H


#include <QWidget>
#include <QListWidget>

class BlockedListWidget : public QWidget{
Q_OBJECT
private:
    QLayout *pMainLayout {nullptr};
    QLayout *pBlockedListLayout {nullptr};

    QListWidget *pBlockedListWidget {nullptr};
private slots:
    void refreshBlockedList();
    void acquireBlockedList();
    void unblock (const std::string &);
public:
    explicit BlockedListWidget(QWidget *);

    void initWidget();

    void createComponents();

    void settleLayouts();

    void addItemToList(const std::string &);

    void clearList();

    ~BlockedListWidget() override = default;
};


#endif //QT1_BLOCKEDLISTWIDGET_H
