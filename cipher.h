#ifndef CIPHER_H
#define CIPHER_H

#include <QDebug>
#include <openssl/rsa.h>
#include <openssl/engine.h>
#include <openssl/pem.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

#include <openssl/modes.h>
#include <openssl/sha.h>
#include <openssl/md5.h>

#define PADDING RSA_PKCS1_PADDING
#define KEYSIZE 32
#define IVSIZE 32
#define BLOCKSIZE 256
#define SALTSIZE 8

#include <QObject>

class Cipher : QObject
{
    Q_OBJECT
public:
    explicit Cipher(QObject *parent = 0);
    ~Cipher();

private:
    void initalize();
    void finelize();

};

namespace GetCipher
{
    RSA *getPublicKey(QByteArray &data);
    RSA *getPrivateKey(QByteArray &data);
    QByteArray encryptRSA(RSA *key, QByteArray &data);
    QByteArray decryptRSA(RSA *key, QByteArray &data);
    QByteArray encryptAES(QByteArray passphrase, QByteArray &data);
    QByteArray decryptAES(RSA *key, QByteArray &data);
    QByteArray randomBytes(int size);
    void freenRSAKey(RSA *key);

    QByteArray getPublicKey();
    QByteArray getPrivateKey();
}

#endif // CIPHER_H