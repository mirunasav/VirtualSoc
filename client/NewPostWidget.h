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
    QComboBox *pPostToWhichGroup {nullptr};

    bool isPrivateVariable;
private slots:
    void changePostVisibility(const std::string &);

signals:
    void onPostClick(const std::string &, const std::string &); //postare, vizibilitate
    //dau clear si la textbox tot aici
public:
    constexpr static const char *pPostButtonText = "Post";

    explicit NewPostWidget(QWidget *) ;

    void initWidget ();

    void createComponents();

    void settleLayouts();

    bool isPrivate();
    ~NewPostWidget() override = default;
};


#endif //QT1_NEWPOSTWIDGET_H
