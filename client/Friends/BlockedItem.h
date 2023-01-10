//
// Created by mrnk on 1/10/23.
//

#ifndef QT1_BLOCKEDITEM_H
#define QT1_BLOCKEDITEM_H


#include <QWidget>
#include <QPushButton>
#include <QLabel>

class BlockedItem : public QWidget {
Q_OBJECT
private:
    QLayout *pMainLayout {nullptr};
    QLayout *pLabelsLayout{nullptr};
    QLayout *pButtonsLayout{nullptr};

    QPushButton *pUnblockButton {nullptr};

    QLabel *pUsername {nullptr};
private slots:
    void onUnblockClick();
signals:
    void unblock(const std::string&);
public:
    constexpr static const char *pUnblockButtonText = "Unblock";

    explicit BlockedItem(QWidget *, const std::string &);

    void initWidget (const std::string &);

    void createComponents (const std::string &);

    void settleLayouts();

    ~BlockedItem() override = default;

};


#endif //QT1_BLOCKEDITEM_H
