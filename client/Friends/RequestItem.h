//
// Created by mrnk on 1/7/23.
//

#ifndef QT1_REQUESTITEM_H
#define QT1_REQUESTITEM_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class RequestItem : public QWidget {
Q_OBJECT
private:
    QLayout *pMainLayout {nullptr};
    QLayout *pLabelsLayout{nullptr};
    QLayout *pButtonsLayout{nullptr};

    QPushButton *pAcceptButton {nullptr};
    QPushButton *pDenyButton {nullptr};

    QLabel *pUsername {nullptr};
private slots:
    void onAcceptClick();
    void onDenyClick();
signals:
    void accept(const std::string &);
    void deny(const std::string &);
public:
    constexpr static const char *pAcceptButtonText = "Accept";
    constexpr static const char *pDenyButtonText= "Deny";

    explicit RequestItem (QWidget *, const std::string &);

    void initWidget (const std::string &);

    void createComponents (const std::string &);

    void settleLayouts();

    ~RequestItem() override = default;
};



#endif //QT1_REQUESTITEM_H
