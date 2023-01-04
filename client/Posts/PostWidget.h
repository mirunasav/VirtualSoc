//
// Created by mrnk on 1/3/23.
//

#ifndef QT1_POSTWIDGET_H
#define QT1_POSTWIDGET_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>

class PostWidget: public QWidget {
Q_OBJECT
private:
    QLayout *pMainLayout {nullptr};
    QLayout *pUserDateLayout{nullptr};//username si data
    QLayout *pPostBodyLayout {nullptr};
    QLayout *pVisibilityLayout {nullptr};

    QLabel *pUsernameLabel {nullptr};
    QLabel *pDateLabel {nullptr};
    QLabel *pPostTextLabel {nullptr};
    QLabel *pVisibleToLabel {nullptr};//visible to:

    QPushButton *pDeletePostButton {nullptr};

    std::string visibility;

    bool isOwnerOfPost;
    int postID;
private slots:
    void onRemoveClick ();
signals:
    void remove (int id);

public:
    constexpr static const char *pVisibleToText= "Visible To :";
    constexpr static const char *pDeletePostButtonText= "Delete Post";

    //in ordine: user, text, visibleTo, date
    explicit PostWidget(QWidget *, int ID ,const std::string &,const std::string &, const std::string &, const std::string &, const std::string &);

    void initWidget (const std::string &,const std::string &,const std::string &,const std::string &);

    void createComponents (const std::string &, const std::string &,const std::string &,const std::string &);

    void settleLayouts();

    ~PostWidget() override = default;

};


#endif //QT1_POSTWIDGET_H
