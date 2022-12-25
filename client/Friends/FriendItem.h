//
// Created by mrnk on 12/23/22.
//

#ifndef QT1_FRIENDITEM_H
#define QT1_FRIENDITEM_H


#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>

class FriendItem : public QWidget {
Q_OBJECT
private:
    QLayout *pMainLayout {nullptr};
    QLayout *pLabelsLayout{nullptr};
    QLayout *pButtonsLayout{nullptr};

    QPushButton *pRemoveFriendButton {nullptr};
    QPushButton *pApplyChangeButton {nullptr};

    QComboBox *pChangeFriendType {nullptr};

    QLabel *pFriendUsername {nullptr};
    QLabel *pFriendshipType {nullptr};

private slots:
    //genereaza mai departe semnale
    void onRemoveClick ();
    void onChangeTypeClick(int);
    void onApplyChangeClick();

signals:
    void remove(const std::string &);
    void changeType(const std::string &, const std::string &);
    void applyChange();
public:
    constexpr static const char *pRemoveFriendButtonText = "Remove";
    constexpr static const char *pApplyChangeButtonText= "Apply Change";

    explicit FriendItem(QWidget *,const std::string & ,const std::string & ); //username, friendship type

    ~FriendItem() override = default;

    void initWidget (const std::string &,const std::string &);

    void createComponents (const std::string &, const std::string &);

    void settleLayouts();




};


#endif //QT1_FRIENDITEM_H
