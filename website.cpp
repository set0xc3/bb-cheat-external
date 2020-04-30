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

void website::loadSetting(QJsonObject root)
{
    // type_game
    {
        QJsonValue authorized = root["type_game"];
        QString s_data = authorized.toString();
        QByteArray b_data; b_data = s_data.toUtf8(); // QString to QByteArray

        this->userData.typeGame = b_data.toInt();
    }

    //LoadSetting
    {
        int i = this->userData.typeGame;
        this->threads->section[i].aimSetting.isActive = root["aim_isactive"].toString().toInt();
        this->threads->section[i].aimSetting.keybind = root["aim_keybind"].toString().toInt();
        this->threads->section[i].aimSetting.keybindText = root["aim_keybindtext"].toString();
        this->threads->section[i].aimSetting.isRadius = root["aim_isradius"].toString().toInt();
        this->threads->section[i].aimSetting.bone = root["aim_bone"].toString().toInt();
        this->threads->section[i].aimSetting.smoothness = root["aim_smooth"].toString().toInt();

        this->threads->section[i].aimSetting.radius = root["aim_radius"].toString().toInt();
        this->threads->section[i].aimSetting.colorRadius = root["aim_color"].toString();

        this->threads->section[i].espSetting.isActive = root["esp_isactive"].toString().toInt();
        this->threads->section[i].espSetting.colorRD = root["esp_color"].toString();
        this->threads->section[i].espSetting.isBox = root["esp_is2dbox"].toString().toInt();
        this->threads->section[i].espSetting.is3DBox = root["esp_is3dbox"].toString().toInt();
        this->threads->section[i].espSetting.isOutline = root["esp_isline"].toString().toInt();
        this->threads->section[i].espSetting.isName = root["esp_isname"].toString().toInt();
        this->threads->section[i].espSetting.isHealth = root["esp_ishealth"].toString().toInt();
        this->threads->section[i].espSetting.isArmor = root["esp_isprotection"].toString().toInt();

        this->threads->section[i].weaponSetting.isActive = root["weapon_isactive"].toString().toInt();
        this->threads->section[i].weaponSetting.isInfiniteAmmo = root["weapon_isinfiniteammo"].toString().toInt();
        this->threads->section[i].weaponSetting.isAutomaticWeapon = root["weapon_isautomatic"].toString().toInt();
        this->threads->section[i].weaponSetting.isNoRecoil = root["weapon_isnorecoil"].toString().toInt();
        this->threads->section[i].weaponSetting.rangeShovels = root["weapon_rangeshovels"].toString().toInt();

        this->threads->section[i].miscSetting.isUnhookCamera = root["misc_isunhookcamera"].toString().toInt();
        this->threads->section[i].miscSetting.isFreezing = root["misc_isfreeze"].toString().toInt();
        this->threads->section[i].miscSetting.keybind = root["misc_keybind"].toString().toInt();
        this->threads->section[i].miscSetting.keybindText = root["misc_keybindtext"].toString();

        emit loadSettingSignal();
    }

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

//      qDebug() << GetCipher::Encryption("0");

        if (root["server"] == 1 && root["type"] == 0)
        {
            // userData.status
            // 1-обнова, 2-техю работы, 3-дни замароженны, 4-бан.

            //-- version
            {
                QJsonValue authorized = root["version"];
                QString s_data = authorized.toString();
                QByteArray b_data; b_data = s_data.toUtf8(); // QString to QByteArray

                this->userData.version = b_data;

                if (GetCipher::Decrypted(b_data) == "-1" || GetCipher::Decrypted(b_data) == "")
                {
                    this->userData.authorized = false;
                    exit(0);
                }

                // Если вышла обнова, то говорим пользователю обновитья
                if (GetCipher::Decrypted(b_data) != GetCipher::Decrypted(this->userData.versionBuff)) this->userData.status = 1;
                else  if (GetCipher::Decrypted(b_data) == GetCipher::Decrypted(this->userData.versionBuff)) this->userData.status = 0;
            }

            //-- day
            {
                QJsonValue authorized = root["day"];
                QString s_data = authorized.toString();
                QByteArray b_data; b_data = s_data.toUtf8(); // QString to QByteArray

                if (GetCipher::Decrypted(b_data) == "-1" || GetCipher::Decrypted(b_data) == "")
                {
                    this->userData.authorized = false;
                    exit(0);
                }

                this->userData.day = b_data;

                // Если у ползователья закончелись дни
                if (GetCipher::Decrypted(b_data) != GetCipher::Decrypted(this->userData.dayBuff)) this->userData.authorized = true;
                else this->userData.authorized = false;
            }

            //-- name
            {
                QJsonValue authorized = root["name"];
                QString s_data = authorized.toString();
                QByteArray b_data; b_data = s_data.toUtf8(); // QString to QByteArray

                this->userData.name = b_data;
            }

            //-- Online
            {
                QJsonValue authorized = root["online"];
                QString s_data = authorized.toString();
                QByteArray b_data; b_data = s_data.toUtf8(); // QString to QByteArray

                this->userData.online = b_data;
            }

            //-- servercomm
            {
                QJsonValue authorized = root["servercomm"];
                QString s_data = authorized.toString();
                QByteArray b_data; b_data = s_data.toUtf8(); // QString to QByteArray

                if (GetCipher::Decrypted(b_data) == "-1" || GetCipher::Decrypted(b_data) == "")
                {
                    this->userData.authorized = false;
                    exit(0);
                }

                this->userData.servercomm = b_data;

                // Если видутся работы на сервере
                if (GetCipher::Decrypted(b_data) == GetCipher::Decrypted(this->userData.servercommBuff)) this->userData.status = 2;
            }

            //-- frozen
            {
                QJsonValue authorized = root["frozen"];
                QString s_data = authorized.toString();
                QByteArray b_data; b_data = s_data.toUtf8(); // QString to QByteArray

                if (GetCipher::Decrypted(b_data) == "-1" || GetCipher::Decrypted(b_data) == "")
                {
                    this->userData.authorized = false;
                    exit(0);
                }

                this->userData.servercomm = b_data;

                // Если у дни ползователья замароженны
                if (GetCipher::Decrypted(b_data) == "1") this->userData.authorized = false;
            }

            emit loaderFormSignal();
            if (this->userData.authorizedS == true)
            {
                this->load("0"); // Получаем настройки пользователя - launcher
                this->load("1"); // Получаем настройки пользователя - steam

                this->userData.authorizedS = false;
            }
        }

        if (root["server"] == 1 && root["type"] == 1)
        {
            loadSetting(root);
        }

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
            this->updatelog = html;
            buff = false;
        }

        if(this->updatelog != html)
        {
            this->updatelog = html;
            this->newlog = true;
        }
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

    this->userData.name = login;
    this->userData.password = GetCipher::Encryption(pass);


    this->post("https://shredhack.ru/api/api.php", data);
    this->getHTML("https://shredhack.ru/update-log.php/");
}

void website::heartbeat()
{
    QByteArray data;
    data.append("heartbeat=1");
    data.append("&login="+this->userData.name);

    this->post("https://shredhack.ru/api/api.php", data);
}

void website::load(QString typegame)
{
    QByteArray data;
    data.append("loadsetting=1");
    data.append("&login="+this->userData.name);
    data.append("&typegame="+typegame);

    this->post("https://shredhack.ru/api/api.php", data);
}

void website::save(QString typegame)
{
    QByteArray data;
    data.append("savesetting=1");
    data.append("&login="+this->userData.name);
    data.append("&typegame="+typegame);

    data.append("&aim_keybind="+QString::number(this->threads->section[this->authForm->loadSetting].aimSetting.keybind));
    data.append("&aim_keybindtext="+this->threads->section[this->authForm->loadSetting].aimSetting.keybindText);
    data.append("&aim_bone="+QString::number(this->threads->section[this->authForm->loadSetting].aimSetting.bone));
    data.append("&aim_color="+this->threads->section[this->authForm->loadSetting].aimSetting.colorRadius.name());
    data.append("&aim_isactive="+QString::number(this->threads->section[this->authForm->loadSetting].aimSetting.isActive));
    data.append("&aim_isradius="+QString::number(this->threads->section[this->authForm->loadSetting].aimSetting.isRadius));
    data.append("&aim_radius="+QString::number(this->threads->section[this->authForm->loadSetting].aimSetting.radius));
    data.append("&aim_smooth="+QString::number(this->threads->section[this->authForm->loadSetting].aimSetting.smoothness));

    data.append("&esp_isactive="+QString::number(this->threads->section[this->authForm->loadSetting].espSetting.isActive));
    data.append("&esp_color="+this->threads->section[this->authForm->loadSetting].espSetting.colorRD.name());
    data.append("&esp_is2dbox="+QString::number(this->threads->section[this->authForm->loadSetting].espSetting.isBox));
    data.append("&esp_is3dbox="+QString::number(this->threads->section[this->authForm->loadSetting].espSetting.is3DBox));
    data.append("&esp_ishealth="+QString::number(this->threads->section[this->authForm->loadSetting].espSetting.isHealth));
    data.append("&esp_isline="+QString::number(this->threads->section[this->authForm->loadSetting].espSetting.isOutline));
    data.append("&esp_isname="+QString::number(this->threads->section[this->authForm->loadSetting].espSetting.isName));
    data.append("&esp_isprotection="+QString::number(this->threads->section[this->authForm->loadSetting].espSetting.isArmor));

    data.append("&misc_isfreeze="+QString::number(this->threads->section[this->authForm->loadSetting].miscSetting.isFreezing));
    data.append("&misc_isunhookcamera="+QString::number(this->threads->section[this->authForm->loadSetting].miscSetting.isUnhookCamera));

    data.append("&misc_keybind="+QString::number(this->threads->section[this->authForm->loadSetting].miscSetting.keybind));
    data.append("&misc_keybindtext="+this->threads->section[this->authForm->loadSetting].miscSetting.keybindText);

    data.append("&weapon_isactive="+QString::number(this->threads->section[this->authForm->loadSetting].weaponSetting.isActive));
    data.append("&weapon_isautomatic="+QString::number(this->threads->section[this->authForm->loadSetting].weaponSetting.isAutomaticWeapon));
    data.append("&weapon_isinfiniteammo="+QString::number(this->threads->section[this->authForm->loadSetting].weaponSetting.isInfiniteAmmo));
    data.append("&weapon_isnorecoil="+QString::number(this->threads->section[this->authForm->loadSetting].weaponSetting.isNoRecoil));
    data.append("&weapon_rangeshovels="+QString::number(this->threads->section[this->authForm->loadSetting].weaponSetting.rangeShovels));


    this->post("https://shredhack.ru/api/api.php", data);
}

