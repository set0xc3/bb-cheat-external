
// User
#include "website.h"

// Qt


// System
#include "authform.h"
#include "cipher.h"


using namespace std;

namespace {
std::string const default_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //abcdefghijklmnaoqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890
}

std::string random_string(size_t len = 20, std::string const &allowed_chars = default_chars) {
    std::mt19937_64 gen { std::random_device()() };

    std::uniform_int_distribution<size_t> dist { 0, allowed_chars.length()-1 };

    std::string ret;

    std::generate_n(std::back_inserter(ret), len, [&] { return allowed_chars[dist(gen)]; });
    return ret;
}


//void testRSA()
//{
//    QByteArray testPrivateKey = GetCipher::getPrivateKey();
//    QByteArray testPublicKey = GetCipher::getPublicKey();

//    Cipher cWrapper;
//    RSA* publickey = cWrapper.getPublicKey(testPublicKey);
//    RSA* privatekey = cWrapper.getPrivateKey(testPrivateKey);

//    QByteArray plan = "Hi Bob, im sending you a private message";

//    QByteArray encrypted = cWrapper.encryptRSA(publickey, plan);
//    QByteArray decrypted = cWrapper.decryptRSA(privatekey, encrypted);

////    qDebug() << plan;
////    qDebug() << encrypted.toBase64();
//    qDebug() << decrypted;

//    cWrapper.freenRSAKey(publickey);
//    cWrapper.freenRSAKey(privatekey);
//}

//void testAES()
//{
//    Cipher cWrapper;
//    QString passphrase = "password";
//    QByteArray plain = "123";

//    QByteArray encrypted = cWrapper.encryptAES(passphrase.toLatin1(), plain);
////    QByteArray decrypted = cWrapper.decryptRSA(privatekey, encrypted);

////    qDebug() << plan;
////    qDebug() << encrypted.toBase64();
//    qDebug() << encrypted.toBase64();

//}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


//    testRSA();
//    testAES();

//    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);

//    QString inputStr("123");
//    QString key("W92ZB837943A711B98D35E799DFE3Z18");
//    QString iv("tuqZQhKP48e8Piuc");

//    QByteArray hashKey = QCryptographicHash::hash(key.toLocal8Bit(), QCryptographicHash::Sha256);
//    QByteArray hashIV = QCryptographicHash::hash(iv.toLocal8Bit(), QCryptographicHash::Md5);

//    QByteArray encodeText = encryption.encode(inputStr.toLocal8Bit(), hashKey, hashIV);
//    QByteArray decodeText = encryption.decode(encodeText, hashKey, hashIV);

//    QString decodedString = QString(encryption.removePadding(decodeText));

//    qDebug() << decodedString;
//    qDebug() << encodeText.toBase64();


    AuthForm auth;
    auth.setWindowTitle(QString::fromStdString(random_string()));
    auth.setFixedSize(auth.width(), auth.height());
    //auth.setWindowFlags(Qt::CustomizeWindowHint);
    auth.show();


//    MenuSetting menuSetting;
//    menuSetting.show();

    //auth.setWindowIcon(QIcon(":/resource/images/logo.png"));

//    ExampleThreads threadA("thread A");
//    AuthForm myObject;

//    QObject::connect(&threadA, SIGNAL(MySignal()), &myObject, SLOT(test()));

//    threadA.start();
//    myObject.moveToThread(&threadA);

    return a.exec();
}
