//
// Created by mrnk on 12/23/22.
//

#ifndef QT1_FRIENDSLIST_H
#define QT1_FRIENDSLIST_H


#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include <QTimer>

class FriendsList: public QWidget {
Q_OBJECT
private:
    QLayout *pMainLayout {nullptr};
    QLayout *pNumberOfFriendsLayout {nullptr};
    QLayout *pFriendListLayout {nullptr};

    QLabel *pNumberOfFriendsLabel {nullptr};
    QLabel *pFriendsCounter {nullptr}; //actualizam acest index

    int numberOfFriendsCounter;

//lista de prieteni, va contine widgeturi cu prieteni
//fiecare widget prieten va contine:
// nume,
// tip prietenie,
//schimbare tip prietenie,
//remove friend
    QListWidget *pFriends {nullptr};

    QTimer *pRefreshListTimer {nullptr};
private slots:
    //daca dau remove unui prieten tb sa dau refresh
    //la fel, dac schimb tipul de prietenie dau refresh
    //deci in functia asta, actualizez indexul si tipul de prietenie, dupa
    //fiecare apasare de buton
    void refreshFriendList(); //->asta genereaza schimbare in lista din server
    void acquireFriendList();//asta ia lista de la server
    void removeFriend(const std::string &);
    static void changeFriendshipType(const std::string &, const std::string &);

public:
    constexpr static const char *pNumberOfFriendsText= "Number of Friends:";

    explicit FriendsList(QWidget *);

    void initWidget();

    void createComponents();

    void settleLayouts();

    void addFriendToList(const std::string &, const std::string &);

    void clearFriendList();

    void refreshNumberOfFriendsCounter();

    ~FriendsList() override = default;



};


#endif //QT1_FRIENDSLIST_H
