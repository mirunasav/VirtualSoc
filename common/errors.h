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

};


#endif //QT1_ERRORS_H
