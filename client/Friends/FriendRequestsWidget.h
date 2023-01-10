//
// Created by mrnk on 1/7/23.
//

#ifndef QT1_FRIENDREQUESTSWIDGET_H
#define QT1_FRIENDREQUESTSWIDGET_H

#include <QWidget>
#include <QListWidget>

class FriendRequestsWidget : public QWidget {
Q_OBJECT
private:
    QLayout *pMainLayout {nullptr};
    QLayout *pFriendRequestsLayout {nullptr};

    QListWidget *pFriendRequestsList {nullptr};
private slots:
    void refreshRequestsList ();
    void acquireRequestsList();
    void acceptRequest(const std::string &);
    void denyRequest(const std::string &);
    void blockUser(const std::string &);
public:
    explicit FriendRequestsWidget(QWidget *);

    void initWidget();

    void createComponents();

    void settleLayouts();

    void addRequestToList (const std::string &);

    void clearList();

    ~FriendRequestsWidget() override = default;




};


#endif //QT1_FRIENDREQUESTSWIDGET_H
