#ifndef WEBSITE_H
#define WEBSITE_H

#include <QThread>
#include <QtWidgets>
#include <QDebug>
#include <QObject>
#include <QNetworkReply>
#include <QAuthenticator>
#include <QMessageBox>
#include <iostream>
#include <thread>
#include "authform.h"
#include "threads.h"


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
    QString _version = "v10.30";
    QString version = "";
    QString buffupdatelog = "";
    QString updatelog = "";
    QString name = "";
    QString day = "";
    bool authorized = false;

public:
    AuthForm *authForm;
    Threads *threads;

public slots:
    void get(QString location);
    void getHTML(QString location);
    void post(QString location, QByteArray data);
    void auth(QString login, QString pass);
    void load(QString login);
    void save(QString login);

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
