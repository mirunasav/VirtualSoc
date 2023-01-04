//
// Created by mrnk on 12/25/22.
//

#ifndef QT1_SETTINGSWIDGET_H
#define QT1_SETTINGSWIDGET_H


#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include "../../common/common.h"

class SettingsWidget : public QWidget{
Q_OBJECT
private slots:
   void refresh();
   void changePrivacy(int);
   void applyChanges();
private:
    QLayout *pMainLayout {nullptr};

    QLabel *pCurrentPrivacySetting {nullptr};

    QComboBox *pChangePrivacyBox {nullptr};

    QPushButton *pApplyChangesButton {nullptr};

public:
    constexpr static const char *pApplyChangesButtonText = "Apply Changes";
    constexpr static const char *pPrivateAccountText = "Your Account is Private";
    constexpr static const char *pPublicAccountText = "Your Account is Public";

    explicit SettingsWidget(QWidget *);

    void initWidget();

    void createComponents();

    void getPrivacy();

    void settleLayouts();

    void sendChangePrivacyRequest(common::privacySetting);

    ~SettingsWidget() override = default;

signals:



};


#endif //QT1_SETTINGSWIDGET_H
