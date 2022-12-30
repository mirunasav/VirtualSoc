

#ifndef QT1_LOGINWIDGET_H
#define QT1_LOGINWIDGET_H


#include <QLineEdit>
#include <QPushButton>
#include "QLabel"
#include "MainWindow.h"


class LoginWidget : public QWidget {
    Q_OBJECT


private slots:
    //evenimentul care se intampla cand apas login : e trimis un request catre server;
    //                                                verific daca datele sunt ok
    //                                                daca sunt ok, intru in app -> AppHomeWidget
    //                                                altfel, deny login

    void onConfirmLogin();

    //ce se intampla cand apas SignUp : verific in server daca pot crea contul
    void onSignUp();

    void onSkip();

private:

    QLabel *pWidgetTitle {nullptr};
    QLabel *pUsernameLabel {nullptr};
    QLabel *pPasswordLabel {nullptr};

    QLineEdit *pUsernameTextBox { nullptr };
    QLineEdit *pPasswordTextBox { nullptr };

    QLayout *pLoginLayout {nullptr};
    QLayout *pCredentialsLayout {nullptr};
    QLayout *pLabelLayout {nullptr};
    QLayout *pTextBoxLayout {nullptr};
    QLayout *pLoginButtonsLayout {nullptr};
    QLayout *pButtonsLayout {nullptr};

    QPushButton *pLoginButton {nullptr};
    QPushButton *pSignUpButton {nullptr};
    QPushButton *pContinueWithoutLogginInButton {nullptr};


    bool validateInput(); //validez inputul : verific ori daca userul exista deja,
                        // ori daca am pus un username valid


signals:
    //semnale pe care le trimit daca am pus userul si parola corecte;
    void loginSuccess();
    void notLoggedIn();




public:
    //costantele:
    //constantele de text
    constexpr static const char *pTitleLabelText = "Welcome to VirtualSoc !";
    constexpr static const char *pUsernameLabelText = "Username : ";
    constexpr static const char *pPasswordLabelText = "Password : ";
    constexpr static const char *pLoginButtonText = "Login";
    constexpr static const char *pSignUpButtonText = "Sign Up";
    constexpr static const char *pContinueWithoutLogginInButtonText = "Skip";

    constexpr static const char *pUsernameLabelEmpty = "Please enter username!";
    constexpr static const char *pPasswordLabelEmpty = "Please enter password!";
    constexpr static const char *pMessageLoginFailed = "Login Failed";
    constexpr static const char *pMessageUserAlreadyConnected = "User is already connected!";

    constexpr static const char *pMessageSignUpFailed = "Username is taken! Choose another one.";
    constexpr static const char *pMessageAccountCreated = "Your account was created!";
    constexpr static const char *pMessageInvalidCharacters = "Username field contains invalid characters!";

    constexpr static const char *pServerDown = "Connection to server failed";


public:
    //functiile
   explicit LoginWidget(QWidget *);

    //creeaza componentele, conecteaza semnalele de evenimente
    //apeleaza createComponents, settleLayouts,adjustLayouts, styleComponents
    void initWidget();

    void createComponents();

    void settleLayouts(); //le pune pe mijlocul ecranului

    void connectComponents();

    void adjustLayouts();

    void styleComponents();

    void notificationPopUp(char const * ) ; //cand primesc request / mesaj


    void keyPressEvent(QKeyEvent * event) override;//cand apas enter fac login

    ~LoginWidget() override = default;


};


#endif //QT1_LOGINWIDGET_H
