#include "website.h"
#include "authform.h"
#include "toolshack.h"
#include "cipher.h"



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

QString Encryption(QString name)
{
    if (QString(name.toUtf8()) == "")return QByteArray();

    QByteArray plan = QString(name).toUtf8();

    QByteArray testPrivateKey = GetCipher::getPrivateKey();
    QByteArray testPublicKey = GetCipher::getPublicKey();

    RSA* publickey = GetCipher::getPublicKey(testPublicKey);

    QByteArray encrypted = GetCipher::encryptRSA(publickey, plan);

    return QString(encrypted.toBase64()).toUtf8();
}

QString Decrypted(QJsonObject root, QString name)
{
    if (QString(root.value(name).toString()).toUtf8() == "")return QByteArray();

    QByteArray testPrivateKey = GetCipher::getPrivateKey();
    QByteArray testPublicKey = GetCipher::getPublicKey();
    RSA* privatekey = GetCipher::getPrivateKey(testPrivateKey);

    QByteArray encrypted = QString(root.value(name).toString()).toUtf8();
    encrypted = encrypted.fromBase64(encrypted);
    QByteArray decrypted = GetCipher::decryptRSA(privatekey, encrypted);

    return QString(decrypted).toUtf8();
}

QString DecryptedToObject(QJsonObject root, QString type, QString name)
{
    if (QString(root[type].toObject()[name].toString()).toUtf8() == "")return QByteArray();

    QByteArray testPrivateKey = GetCipher::getPrivateKey();
    QByteArray testPublicKey = GetCipher::getPublicKey();
    RSA* privatekey = GetCipher::getPrivateKey(testPrivateKey);

    QByteArray encrypted = QString(root[type].toObject()[name].toString()).toUtf8();
//    qDebug() << encrypted;

    encrypted = encrypted.fromBase64(encrypted);
    QByteArray decrypted = GetCipher::decryptRSA(privatekey, encrypted);

    return QString(decrypted).toUtf8();
}

void website::readyRead()
{
//     qInfo() << "ReadyRead";

    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if (reply->error() == QNetworkReply::NoError)
    {
//        QByteArray content= reply->readAll();
//        QTextCodec *codec = QTextCodec::codecForName("cp1251");


        // То создаём объект Json Document, считав в него все данные из ответа
        QJsonDocument deleted;
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
        QJsonObject root = document.object();


        this->version = Decrypted(root, "version");
        this->name = Decrypted(root, "name");
        this->day = Decrypted(root, "day");



        if(Decrypted(root, "setting") == "load")
        {
            if (this->authForm->loadSetting == 0)
            {
                int i = 0;
                static QString typeGame = "type_game0";
                this->threads->section[i].aimSetting.isActive = DecryptedToObject(root, typeGame, "aim_isactive").toInt();
                this->threads->section[i].aimSetting.isRadius = DecryptedToObject(root, typeGame, "aim_isradius").toInt();
                this->threads->section[i].aimSetting.bone = DecryptedToObject(root, typeGame, "aim_bone").toInt();
                this->threads->section[i].aimSetting.smoothness = DecryptedToObject(root, typeGame, "aim_smooth").toInt();

                this->threads->section[i].aimSetting.radius = DecryptedToObject(root, typeGame, "aim_radius").toInt();
                this->threads->section[i].aimSetting.colorRadius = QString(DecryptedToObject(root, typeGame, "aim_color"));

                 this->threads->section[i].espSetting.isActive = DecryptedToObject(root, typeGame, "esp_isactive").toInt();
                 this->threads->section[i].espSetting.colorRD = QString(DecryptedToObject(root, typeGame, "esp_color"));
                 this->threads->section[i].espSetting.isBox = DecryptedToObject(root, typeGame, "esp_is2dbox").toInt();
                 this->threads->section[i].espSetting.is3DBox = DecryptedToObject(root, typeGame, "esp_is3dbox").toInt();
                 this->threads->section[i].espSetting.isOutline =  DecryptedToObject(root, typeGame, "esp_isline").toInt();
                 this->threads->section[i].espSetting.isName = DecryptedToObject(root, typeGame, "esp_isname").toInt();
                 this->threads->section[i].espSetting.isHealth = DecryptedToObject(root, typeGame, "esp_ishealth").toInt();
                 this->threads->section[i].espSetting.isArmor = DecryptedToObject(root, typeGame, "esp_isprotection").toInt();

                this->threads->section[i].weaponSetting.isActive = DecryptedToObject(root, typeGame, "weapon_isactive").toInt();
                this->threads->section[i].weaponSetting.isInfiniteAmmo = DecryptedToObject(root, typeGame, "weapon_isinfiniteammo").toInt();
                this->threads->section[i].weaponSetting.isAutomaticWeapon = DecryptedToObject(root, typeGame, "weapon_isautomatic").toInt();
                this->threads->section[i].weaponSetting.isNoRecoil = DecryptedToObject(root, typeGame, "weapon_isnorecoil").toInt();
                this->threads->section[i].weaponSetting.rangeShovels = DecryptedToObject(root, typeGame, "weapon_rangeshovels").toInt();

                this->threads->section[i].miscSetting.isUnhookCamera =  DecryptedToObject(root, typeGame, "misc_isunhookcamera").toInt();
                this->threads->section[i].miscSetting.isFreezing =  DecryptedToObject(root, typeGame, "misc_isfreeze").toInt();
            }

            if (this->authForm->loadSetting == 1)
            {
                int i = 1;
                static QString typeGame = "type_game1";
                this->threads->section[i].aimSetting.isActive = DecryptedToObject(root, typeGame, "aim_isactive").toInt();
                this->threads->section[i].aimSetting.isRadius = DecryptedToObject(root, typeGame, "aim_isradius").toInt();
                this->threads->section[i].aimSetting.bone = DecryptedToObject(root, typeGame, "aim_bone").toInt();
                this->threads->section[i].aimSetting.smoothness = DecryptedToObject(root, typeGame, "aim_smooth").toInt();

                this->threads->section[i].aimSetting.radius = DecryptedToObject(root, typeGame, "aim_radius").toInt();
                this->threads->section[i].aimSetting.colorRadius = QString(DecryptedToObject(root, typeGame, "aim_color"));

                 this->threads->section[i].espSetting.isActive = DecryptedToObject(root, typeGame, "esp_isactive").toInt();
                 this->threads->section[i].espSetting.colorRD = QString(DecryptedToObject(root, typeGame, "esp_color"));
                 this->threads->section[i].espSetting.isBox = DecryptedToObject(root, typeGame, "esp_is2dbox").toInt();
                 this->threads->section[i].espSetting.is3DBox = DecryptedToObject(root, typeGame, "esp_is3dbox").toInt();
                 this->threads->section[i].espSetting.isOutline =  DecryptedToObject(root, typeGame, "esp_isline").toInt();
                 this->threads->section[i].espSetting.isName = DecryptedToObject(root, typeGame, "esp_isname").toInt();
                 this->threads->section[i].espSetting.isHealth = DecryptedToObject(root, typeGame, "esp_ishealth").toInt();
                 this->threads->section[i].espSetting.isArmor = DecryptedToObject(root, typeGame, "esp_isprotection").toInt();

                this->threads->section[i].weaponSetting.isActive = DecryptedToObject(root, typeGame, "weapon_isactive").toInt();
                this->threads->section[i].weaponSetting.isInfiniteAmmo = DecryptedToObject(root, typeGame, "weapon_isinfiniteammo").toInt();
                this->threads->section[i].weaponSetting.isAutomaticWeapon = DecryptedToObject(root, typeGame, "weapon_isautomatic").toInt();
                this->threads->section[i].weaponSetting.isNoRecoil = DecryptedToObject(root, typeGame, "weapon_isnorecoil").toInt();
                this->threads->section[i].weaponSetting.rangeShovels = DecryptedToObject(root, typeGame, "weapon_rangeshovels").toInt();

                this->threads->section[i].miscSetting.isUnhookCamera =  DecryptedToObject(root, typeGame, "misc_isunhookcamera").toInt();
                this->threads->section[i].miscSetting.isFreezing =  DecryptedToObject(root, typeGame, "misc_isfreeze").toInt();
            }

            emit loadSettingSignal();
        }


        if(this->day != "")
        {
            if (this->day == "H")return;

            this->authorized = true;
            if (this->day == "N")
            {
                this->day = "0";
            }
            else if (this->day == "∞")
            {
                this->day = "∞";
            }

            emit loaderFormSignal();

            static bool load = true;
            static QString typeGame = "type_game0";
            if (load == true)
            {
                for (int i = 0; i < 2; i++) {
                    this->threads->section[i].aimSetting.isActive = DecryptedToObject(root, typeGame, "aim_isactive").toInt();
                    this->threads->section[i].aimSetting.isRadius = DecryptedToObject(root, typeGame, "aim_isradius").toInt();
                    this->threads->section[i].aimSetting.bone = DecryptedToObject(root, typeGame, "aim_bone").toInt();
                    this->threads->section[i].aimSetting.smoothness = DecryptedToObject(root, typeGame, "aim_smooth").toInt();

                    this->threads->section[i].aimSetting.radius = DecryptedToObject(root, typeGame, "aim_radius").toInt();
                    this->threads->section[i].aimSetting.colorRadius = DecryptedToObject(root, typeGame, "aim_color");

                     this->threads->section[i].espSetting.isActive = DecryptedToObject(root, typeGame, "esp_isactive").toInt();
                     this->threads->section[i].espSetting.colorRD = DecryptedToObject(root, typeGame, "esp_color");
                     this->threads->section[i].espSetting.isBox = DecryptedToObject(root, typeGame, "esp_is2dbox").toInt();
                     this->threads->section[i].espSetting.is3DBox = DecryptedToObject(root, typeGame, "esp_is3dbox").toInt();
                     this->threads->section[i].espSetting.isOutline =  DecryptedToObject(root, typeGame, "esp_isline").toInt();
                     this->threads->section[i].espSetting.isName = DecryptedToObject(root, typeGame, "esp_isname").toInt();
                     this->threads->section[i].espSetting.isHealth = DecryptedToObject(root, typeGame, "esp_ishealth").toInt();
                     this->threads->section[i].espSetting.isArmor = DecryptedToObject(root, typeGame, "esp_isprotection").toInt();

                    this->threads->section[i].weaponSetting.isActive = DecryptedToObject(root, typeGame, "weapon_isactive").toInt();
                    this->threads->section[i].weaponSetting.isInfiniteAmmo = DecryptedToObject(root, typeGame, "weapon_isinfiniteammo").toInt();
                    this->threads->section[i].weaponSetting.isAutomaticWeapon = DecryptedToObject(root, typeGame, "weapon_isautomatic").toInt();
                    this->threads->section[i].weaponSetting.isNoRecoil = DecryptedToObject(root, typeGame, "weapon_isnorecoil").toInt();
                    this->threads->section[i].weaponSetting.rangeShovels = DecryptedToObject(root, typeGame, "weapon_rangeshovels").toInt();

                    this->threads->section[i].miscSetting.isUnhookCamera =  DecryptedToObject(root, typeGame, "misc_isunhookcamera").toInt();
                    this->threads->section[i].miscSetting.isFreezing =  DecryptedToObject(root, typeGame, "misc_isfreeze").toInt();

                    typeGame = "type_game1";
                }

                load = false;
            }



        }

        root = deleted.object();
    }
    else
    {
//        qDebug()<< reply->errorString();
    }
    reply->deleteLater();
}

static bool buff = true;
void website::readyReadHTML()
{
//    qInfo() << "ReadyReadHTML";

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

void website::auth(string login, string pass)
{
    if (login == "" || pass == "")return;

    QByteArray data;
    data.append("authForm=1");
    data.append("&login="+Encryption(QString::fromStdString(login)));
    data.append("&pass="+Encryption(QString::fromStdString(pass)));
    data.append("&hwid="+Encryption(ToolsHack::GetHWID()));
    data.append("&device=pc");


    this->post("https://shredhack.ru/auth.php/", data);
    this->getHTML("https://shredhack.ru/update-log.php/");

//    string strData = "authForm=1&login="+login+"&pass="+pass;

}

void website::load(QString login)
{
    QByteArray data;
    data.append("setting=1");
    data.append("&login="+Encryption(login));
    data.append("&device=pc");

    this->post("https://shredhack.ru/setting.php/", data);
}



void website::save(QString login)
{
    QString slogin = Encryption(login);
//    qDebug() << slogin;

    QByteArray data;
    data.append("setting=2");
    data.append("&login="+slogin);
    data.append("&device=pc");

    data.append("&type_game="+Encryption(QString::number(this->authForm->loadSetting)));
    data.append("&aim_bone="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].aimSetting.bone)));
    data.append("&aim_color="+Encryption(this->threads->section[this->authForm->loadSetting].aimSetting.colorRadius.name()));
    data.append("&aim_isactive="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].aimSetting.isActive)));
    data.append("&aim_isradius="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].aimSetting.isRadius)));
    data.append("&aim_radius="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].aimSetting.radius)));
    data.append("&aim_smooth="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].aimSetting.smoothness)));

    data.append("&esp_isactive="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].espSetting.isActive)));
    data.append("&esp_color="+Encryption(this->threads->section[this->authForm->loadSetting].espSetting.colorRD.name()));
    data.append("&esp_is2dbox="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].espSetting.isBox)));
    data.append("&esp_is3dbox="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].espSetting.is3DBox)));
    data.append("&esp_ishealth="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].espSetting.isHealth)));
    data.append("&esp_isline="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].espSetting.isOutline)));
    data.append("&esp_isname="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].espSetting.isName)));
    data.append("&esp_isprotection="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].espSetting.isArmor)));

    data.append("&misc_isfreeze="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].miscSetting.isFreezing)));
    data.append("&misc_isunhookcamera="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].miscSetting.isUnhookCamera)));

    data.append("&weapon_isactive="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].weaponSetting.isActive)));
    data.append("&weapon_isautomatic="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].weaponSetting.isAutomaticWeapon)));
    data.append("&weapon_isinfiniteammo="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].weaponSetting.isInfiniteAmmo)));
    data.append("&weapon_isnorecoil="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].weaponSetting.isNoRecoil)));
    data.append("&weapon_rangeshovels="+Encryption(QString::number(this->threads->section[this->authForm->loadSetting].weaponSetting.rangeShovels)));


    this->post("https://shredhack.ru/setting.php/", data);
}

