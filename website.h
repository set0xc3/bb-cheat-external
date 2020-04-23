#ifndef WEBSITE_H
#define WEBSITE_H

#include <QThread>
#include <QtWidgets>
#include <QDebug>
#include <QObject>
#include <QNetworkReply>
#include <QAuthenticator>
#include <QMessageBox>
#include <QString>
#include <iostream>
#include <thread>

#include "authform.h"
#include "threads.h"
#include "toolshack.h"
#include "cipher.h"


using namespace std;

class website : public QObject
{
    Q_OBJECT
public:
    explicit website(QObject *parent = nullptr);

signals:
    void loaderFormSignal();
    void loadSettingSignal();

public:
    QString _version = "";
    QString version = "";
    QString buffupdatelog = "";
    QString updatelog = "";
    QString name = "";
    QString day = "";
    bool authorized = false;


    struct UserData
    {
        QByteArray day;
        QByteArray dayBuff = "kJRDyCLbUaSj+McYgQoHBX+CRE/6v03Zthk0Kbn7/9rLMClIAjrXKVpccZPJXwCh+FouszJr4o5auR07lfaTMngyyREu/dB2Dq4lnVONPo8RNbybgQBw7jUI85O35UwnfVsH4wltkNoo16CYT/InIWMBCX+0mAbmXcV99nG4+sgveJ4BMDfiNJen6MEPSQ+LZJeGTAiHQ8UBMIChdK4bJL05NPcobHL1bNmQCQ2ZFNRkXRAMYQ+rkuN/qYsWzlD2fdx3SFcYxIg9ubvij3sMJQFux2CI4G1GU2CXKFowJ7sFKKQgj6ywQ9vDwFkrVAfYbtaS494jLjHCCwqNX0TMeQ==";

        QString online;
        QString name;
        QByteArray password;
        QByteArray version;
        QByteArray versionBuff = "CoAhpdkfiDYGGvHzdkqQdxtVhbUvg8/Uv0A839MrBoZTg3a6W7oa7Eln8GbNo8eoU7JhapgkeS/Gx8qgpIvjU3PoM2Y05FCOcDhu3j1VmcuWhz53Z28bgvuN3e0UalBBrizKfLSGhREm3oR5UNIHwoVW6zxFnDO8DGcajqlOUoPlkFVAk10p6B3vi/nEI9K/HsP6WrotHxIJszXKvJKILLG+X7OHxEh7gXB9ipel/rNeCK0rXZe1b83596i3+dF1gJHvCte+nZD+OtLz4BZ3CeGH19k1+6VV1vLn8lz0728YATz23RwHztgIU1CNjzO/iOrVrIzvu4NMRdNRwWRLSQ==";

        QByteArray servercommBuff = "a/The3CW+rTkyNrMzDTtz+I/NTryxd2r/bweQTxjQaf5H9OKi0hl3Uvm/yMeDAx7STFzfqWKO0wLTAzzJriKhUcTFGZMIND6VxF5Y0BrVbk4mXdihBez7F0z/7ET0VsamHCChriuqz2Wul06Tr3pQuA4bz77MQ3vW4+9/qhcRXJKXLRX5mIxWfv2xLmuyGiiW1E/Bj+McmspcmQvaGHc9hJX++ozeugbKPP2K6ZvA0mg4KjjEOslk2GE/wXTu47fryCpHtFr6fIzMyfJhuJY5fP7hTir5RmJPNJfv52mdRudb98Xssw/LsAw0kl/eTghU5ortpgk2AL7K117Av5PLw==";
        QByteArray servercomm;

        QByteArray banned = "";
        QByteArray frozen = "";

        int status = 0;
        int typeGame = -1;
        bool authorized = false;
        bool authorizedS = true;
    };
    UserData userData;

public:
    AuthForm *authForm;
    Threads *threads;

public slots:
    void get(QString location);
    void getHTML(QString location);
    void post(QString location, QByteArray data);
    void auth(QString login, QString pass);
    void load(QString typegame);
    void save(QString typegame);
    void heartbeat();

private:
    void loadSetting(QJsonObject root);

private slots:
    void readyRead();
    void readyReadHTML();
    void	authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);
    void	finished(QNetworkReply *reply);
    void	networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility accessible);
    void	proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator);


private:

    QNetworkAccessManager manager;

};


#endif // WEBSITE_H
