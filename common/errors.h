//
// Created by mrnk on 12/22/22.
//

#ifndef QT1_ERRORS_H
#define QT1_ERRORS_H


namespace errors {
    void throwException(const char *);

    //erori
    constexpr static const char * writeStringLengthError = "eroare la writeString la transmis lungime!\n";
    constexpr static const char * writeStringStringError = "eroare la writeString la transmis string!\n";
    constexpr static const char * readStringError = "eroare la readString\n";
    constexpr static const char * writeRequestNumberError = "eroare la writeRequestNumber!\n";
    constexpr static const char * errorAtListen = "Error at listen!\n";
    constexpr static const char * errorAtBind = "Bind error\n" ;
    constexpr static const char * errorAtSettingReusableAddress = "Set reusable address error!\n" ;
    constexpr static const char * errorAtSocketInitialization = "Failure at socket initialization!\n" ;

};


#endif //QT1_ERRORS_H
