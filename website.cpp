#include "website.h"


website::website(QObject *parent) : QObject(parent)
{
    connect(&this->manager, &QNetworkAccessManager::authenticationRequired, this, &website::authenticationRequired);
    connect(&this->manager, &QNetworkAccessManager::networkAccessibleChanged, this, &website::networkAccessibleChanged);
    connect(&this->manager, &QNetworkAccessManager::proxyAuthenticationRequired, this, &website::proxyAuthenticationRequired);
}

void website::get(QString location)
{
    qInfo() << "Getting from server...";


    QNetworkReply* reply = this->manager.get(QNetworkRequest(QUrl(location)));
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)), reply, SLOT(ignoreSslErrors()));
    connect(reply, &QNetworkReply::readyRead, this, &website::readyRead);
}

void website::getHTML(QString location)
{
//    qInfo() << "Getting from server...";

    QNetworkReply* reply = this->manager.get(QNetworkRequest(QUrl(location)));
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)), reply, SLOT(ignoreSslErrors()));
    connect(reply, &QNetworkReply::finished, this, &website::readyReadHTML);
}

void website::post(QString location, QByteArray data)
{
//     qInfo() << "Posting to server...";


    QNetworkRequest request = QNetworkRequest(QNetworkRequest(QUrl(location)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Accept-Encoding","identity");


    QNetworkReply* reply = this->manager.post(request, data);

//    connect(reply, SIGNAL(sslErrors(QList<QSslError>)), reply, SLOT(ignoreSslErrors()));
    connect(reply, &QNetworkReply::finished, this, &website::readyRead);
}

void website::readyRead()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if (reply->error() == QNetworkReply::NoError)
    {
        // То создаём объект Json Document, считав в него все данные из ответа
        QJsonDocument deleted;
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
        QJsonObject root = document.object();

        // Находим type
        for (int i =0; i <  root.keys().count(); i++)
        {
            // 0 - auth, 1 - load, 2 - save
            if (root.keys().at(i) == "type")
            {
                if (root[root.keys().at(i)] == 0) // Если auth
                {

                    for (int g = 0; g< root.keys().count(); g++)
                    {
                        if (root.keys().at(g) == "version")
                        {
                            QJsonValue authorized = root[root.keys().at(g)];
                            QString s_data = authorized.toString();
                            QByteArray b_data; b_data = s_data.toUtf8(); // QString to QByteArray

                            this->userData.version = b_data;

                            // Если вышла обнова, то говорим пользователю обновитья
                            if (GetCipher::Decrypted(b_data) != this->userData.versionBuff) this->userData.status = 1;

                            continue;
                        }

                        if (root.keys().at(g) == "day")
                        {
                            QJsonValue authorized = root[root.keys().at(g)];
                            QString s_data = authorized.toString();
                            QByteArray b_data; b_data = s_data.toUtf8(); // QString to QByteArray

                            this->userData.day = b_data;

                            // Если у ползователья закончелись дни
                            if (GetCipher::Decrypted(b_data) != "0") this->userData.authorized = true;
                            else this->userData.authorized = false;

                            continue;
                        }

                        if (root.keys().at(g) == "name")
                        {
                            QJsonValue authorized = root[root.keys().at(g)];
                            QString s_data = authorized.toString();
                            QByteArray b_data; b_data = s_data.toUtf8(); // QString to QByteArray

                            this->userData.name = b_data;

                            continue;
                        }

                        if (root.keys().at(g) == "commands")
                        {
                            QJsonValue authorized = root[root.keys().at(g)];
                            QString s_data = authorized.toString();
                            QByteArray b_data; b_data = s_data.toUtf8(); // QString to QByteArray

                            this->userData.commands = b_data;

                            if (GetCipher::Decrypted(b_data) == "0") this->userData.status = 2;

                            continue;
                        }
                    }

                    emit loaderFormSignal();
                }
                break;
            }
        }

//        QByteArray reqArray = Decrypted(root, "authorized");

        // parsecffo
        // 2997teach


//        qDebug() << root.keys();
//        QJsonValue authorized = root.value("authorized");
//        if (authorized.toInt() == 1)
//        {
//            emit loaderFormSignal();
//        }

        root = deleted.object();
    }
    else
    {

    }
    reply->deleteLater();
}


void website::readyReadHTML()
{
    static bool buff = true;

   QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
   if (reply->error() == QNetworkReply::NoError)
   {
        QByteArray bytes = reply->readAll();
        QString html = QString::fromUtf8(bytes);

        if(buff == true && html != ""){
            this->buffupdatelog = html;
            buff = false;
        }

        if(this->updatelog != html)this->updatelog = html;

        html = "";
   }
   else
   {
//       qDebug()<<reply->errorString();
   }
   reply->deleteLater();
}

void website::authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator)
{
    Q_UNUSED(reply)
    Q_UNUSED(authenticator)
//    qInfo() << "authenticationRequired";
}

void website::finished(QNetworkReply *reply)
{
    Q_UNUSED(reply)

    //qInfo() << "finished";
}

void website::networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility accessible)
{
    Q_UNUSED(accessible)
//    qInfo() << "networkAccessibleChanged";
}

void website::proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
{
    Q_UNUSED(proxy)
    Q_UNUSED(authenticator)
//    qInfo() << "proxyAuthenticationRequired";
}

void website::auth(QString login, QString pass)
{
    if (login == "" || pass == "")return;

    QByteArray data;
    data.append("auth=1");
    data.append("&login="+GetCipher::Encryption(login));
    data.append("&password="+GetCipher::Encryption(pass));
    data.append("&hwid="+GetCipher::Encryption(ToolsHack::GetHWID()));


    this->post("https://shredhack.ru/api/api.php", data);
//    this->getHTML("https://shredhack.ru/update-log.php/");
}

void website::load(QString login)
{
//    QByteArray data;
//    data.append("setting=1");
//    data.append("&login="+Encryption(login));
//    data.append("&device=pc");

//    this->post("https://shredhack.ru/setting.php/", data);
}

void website::save(QString login)
{
//    QString slogin = Encryption(login);
////    qDebug() << slogin;

//    QByteArray data;
//    data.append("setting=2");
//    data.append("&login="+slogin);
//    data.append("&device=pc");

//    data.append("&type_game="+Encryption(QString::number(this->authForm->loadSetting)));
//    data.append("&aim_bone="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].aimSetting.bone)));
//    data.append("&aim_color="+Encryption(this->threads->section[this->authForm->loadSetting].aimSetting.colorRadius.name()));
//    data.append("&aim_isactive="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].aimSetting.isActive)));
//    data.append("&aim_isradius="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].aimSetting.isRadius)));
//    data.append("&aim_radius="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].aimSetting.radius)));
//    data.append("&aim_smooth="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].aimSetting.smoothness)));

//    data.append("&esp_isactive="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].espSetting.isActive)));
//    data.append("&esp_color="+Encryption(this->threads->section[this->authForm->loadSetting].espSetting.colorRD.name()));
//    data.append("&esp_is2dbox="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].espSetting.isBox)));
//    data.append("&esp_is3dbox="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].espSetting.is3DBox)));
//    data.append("&esp_ishealth="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].espSetting.isHealth)));
//    data.append("&esp_isline="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].espSetting.isOutline)));
//    data.append("&esp_isname="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].espSetting.isName)));
//    data.append("&esp_isprotection="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].espSetting.isArmor)));

//    data.append("&misc_isfreeze="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].miscSetting.isFreezing)));
//    data.append("&misc_isunhookcamera="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].miscSetting.isUnhookCamera)));

//    data.append("&weapon_isactive="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].weaponSetting.isActive)));
//    data.append("&weapon_isautomatic="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].weaponSetting.isAutomaticWeapon)));
//    data.append("&weapon_isinfiniteammo="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].weaponSetting.isInfiniteAmmo)));
//    data.append("&weapon_isnorecoil="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].weaponSetting.isNoRecoil)));
//    data.append("&weapon_rangeshovels="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].weaponSetting.rangeShovels)));


//    this->post("https://shredhack.ru/setting.php/", data);
}
