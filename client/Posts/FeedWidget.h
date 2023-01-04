//
// Created by mrnk on 12/2/22.
//

#ifndef QT1_FEEDWIDGET_H
#define QT1_FEEDWIDGET_H


#include <QWidget>
#include <QPushButton>
#include <QListWidget>

class FeedWidget : public QWidget{
    Q_OBJECT
private:
    QLayout *pLayout{nullptr};
    QLayout *pPostsLayout {nullptr};

    QListWidget *pPostsList {nullptr};//in care pun widgeturi tip postare

    bool loggedIn {false};

private slots:
    void refreshFeed();
    void acquireFeed();
    void removePost(int);

public:
    explicit FeedWidget(QWidget *pParentWindow,bool loggedIn);

    void initWidget();

    void createComponents();

    void settleLayouts();

    void clearFeed();

    void addToFeed(int ,const std::string&, const std::string&, const std::string&,const std::string&, const std::string&);
    ~FeedWidget() override = default;

};


#endif //QT1_FEEDWIDGET_H
