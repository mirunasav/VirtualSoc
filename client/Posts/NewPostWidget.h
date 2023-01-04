//
// Created by mrnk on 1/2/23.
//

#ifndef QT1_NEWPOSTWIDGET_H
#define QT1_NEWPOSTWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>

class NewPostWidget : public QWidget{
Q_OBJECT
private:
    QLayout *pMainLayout {nullptr};
    QLayout *pTextBoxLayout {nullptr};
    QLayout *pButtonsLayout {nullptr};

    QPushButton *pPostButton {nullptr};
    QTextEdit *pTextEdit {nullptr};
    //asta apare doar daca e contul privat
    QComboBox *pVisibleToWhomComboBox {nullptr};


    std::string textOfPost;
    std::string visibleToWhom;
    bool isPrivateVariable;
private slots:
    void onPostClick();
signals:
     //postare, vizibilitate
    //dau clear si la textbox tot aici
public:
    constexpr static const char *pPostButtonText = "Post";
    constexpr static const char *pAfterPostingMessage = "Your post has been shared!";

    explicit NewPostWidget(QWidget *) ;

    void initWidget ();

    void createComponents();

    void settleLayouts();

    bool isPrivate();

    void notificationPopUp(const char * message);

    ~NewPostWidget() override = default;
};


#endif //QT1_NEWPOSTWIDGET_H
