QT       += core gui
QT       += core
QT       += network
QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += windows
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES -= UNICODE
DEFINES += _MBCS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

##ifdef Q_OS_WIN32
#INCLUDEPATH += "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include"
#LIBS += -L"C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Lib\x86"

#LIBS += -L-L"C:\Users\admin\Desktop\OpenSSL-1.1.1-pre10-dev-vs2017\static\Win32\Release\lib" -llibcrypto
#LIBS += -L"C:\Users\admin\Desktop\OpenSSL-1.1.1-pre10-dev-vs2017\static\Win32\Release\lib" -llibssl
#INCLUDEPATH += "C:\Users\admin\Desktop\OpenSSL-1.1.1-pre10-dev-vs2017\static\Win32\Release\include"
##endif

##ifdef Q_OS_WIN64
#INCLUDEPATH += "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include"
#LIBS += -L"C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Lib\x64"

#LIBS += -L-L"C:\Users\admin\Desktop\OpenSSL-1.1.1-pre10-dev-vs2017\static\x64\Release\lib" -llibcrypto
#LIBS += -L"C:\Users\admin\Desktop\OpenSSL-1.1.1-pre10-dev-vs2017\static\x64\Release\lib" -llibssl
#INCLUDEPATH += "C:\Users\admin\Desktop\OpenSSL-1.1.1-pre10-dev-vs2017\static\x64\Release\include"
##endif


INCLUDEPATH += "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include"
LIBS += -L"C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Lib\x86"

LIBS += -L-L"C:\Users\admin\Desktop\OpenSSL-1.1.1-pre10-dev-vs2017\static\Win32\Release\lib" -llibcrypto
LIBS += -L"C:\Users\admin\Desktop\OpenSSL-1.1.1-pre10-dev-vs2017\static\Win32\Release\lib" -llibssl
INCLUDEPATH += "C:\Users\admin\Desktop\OpenSSL-1.1.1-pre10-dev-vs2017\static\Win32\Release\include"


SOURCES += \
    authform.cpp \
    blockpost.cpp \
    cipher.cpp \
    drawing.cpp \
    functions.cpp \
    main.cpp \
    maths_functions.cpp \
    mem.cpp \
    overlay.cpp \
    signaturescanner.cpp \
    threadmem.cpp \
    threads.cpp \
    toolshack.cpp \
    website.cpp

HEADERS += \
    aestest.h \
    authform.h \
    blockpost.h \
    cipher.h \
    drawing.h \
    functions.h \
    maths_functions.h \
    mem.h \
    overlay.h \
    signaturescanner.h \
    threadmem.h \
    threads.h \
    toolshack.h \
    website.h

FORMS += \
    authform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include(QtAwesome/QtAwesome.pri)

DISTFILES += \
    logo.png \
    smallest_pixel-7.ttf

RESOURCES += \
    main.qrc

