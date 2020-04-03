#include "cipher.h"



Cipher::Cipher(QObject *parent)
{
    initalize();
}

Cipher::~Cipher()
{
    finelize();
}

QByteArray GetCipher::getPublicKey()
{
    QByteArray testPublicKey;

    testPublicKey.append("-----BEGIN PUBLIC KEY-----\n");
    testPublicKey.append("MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA+S6ZUPvw2UjMrBSFKYPc\n");
    testPublicKey.append("OZDJXVfrg6m+S+t64zQCdbreP5mnML7HfjCBaHAaxBjZ8SteZk4s8jDa4lMf5Lom\n");
    testPublicKey.append("V5vRhiBjMoVJ4b/s7e+vd9PqQJoqy9Gd55gjADZwQwGsvLStSaM4AtcBK5Z2rIZO\n");
    testPublicKey.append("aqoWlOZQF0hMcU1Ot3hkjpSCIjVY8d7SvP3XxbW6kRWo/wwmjqmnQ3cAQF65sRDF\n");
    testPublicKey.append("ddq9XKwWVdyNIEcFDfSplDPdlFve4fTmFOf6LE6vmWHXfBJ3W74db/lOsatuxosg\n");
    testPublicKey.append("RtaENuLF+pbvgCca0yxHbOk6etAspAuu1F0FYwgMUY0w/tuoI3EvusWwtuAE25XR\n");
    testPublicKey.append("kQIDAQAB\n");
    testPublicKey.append("-----END PUBLIC KEY-----");

    return testPublicKey;
}

QByteArray GetCipher::getPrivateKey()
{
    QByteArray testPrivateKey;

    testPrivateKey.append("-----BEGIN PRIVATE KEY-----\n");
    testPrivateKey.append("MIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQD5LplQ+/DZSMys\n");
    testPrivateKey.append("FIUpg9w5kMldV+uDqb5L63rjNAJ1ut4/macwvsd+MIFocBrEGNnxK15mTizyMNri\n");
    testPrivateKey.append("Ux/kuiZXm9GGIGMyhUnhv+zt76930+pAmirL0Z3nmCMANnBDAay8tK1JozgC1wEr\n");
    testPrivateKey.append("lnashk5qqhaU5lAXSExxTU63eGSOlIIiNVjx3tK8/dfFtbqRFaj/DCaOqadDdwBA\n");
    testPrivateKey.append("XrmxEMV12r1crBZV3I0gRwUN9KmUM92UW97h9OYU5/osTq+ZYdd8Endbvh1v+U6x\n");
    testPrivateKey.append("q27GiyBG1oQ24sX6lu+AJxrTLEds6Tp60CykC67UXQVjCAxRjTD+26gjcS+6xbC2\n");
    testPrivateKey.append("4ATbldGRAgMBAAECggEBAIfpdNKJOKsrXAeYAbHNLDdx04NISzs7QIJkZFi8q4LP\n");
    testPrivateKey.append("dB24j0q1JFad2le+nbrL20QB5bFjfnxzTVAZCtJU/kjWwoen7rNFpDCv4Gk/TLPN\n");
    testPrivateKey.append("MH4gGKunH7uMbbrV9pF1vmQHIGWD0y8pWogNv5kGgIsJTtvUa2bnllpOUlscHazu\n");
    testPrivateKey.append("HC3UA8XXkjIQWZwohpavrWf7zIlkaf9CPqxprr12rAtja44Y60BP29NUEPUDY0MY\n");
    testPrivateKey.append("Ug7wBcnEoR1lue0OCSsMI+4oExmY17n/s7oxBh0urM9q4W54WIGyRrC1vRg3qave\n");
    testPrivateKey.append("y7RxDiB/x+Awg/eHP42xJuy38QPtp2H5eniHbVGzReECgYEA/i14Q1lQeztIi+Z/\n");
    testPrivateKey.append("5QTx9dr6s0urhF7YbcxV8lXveMtSk5EOAqnVQHXoJyQPeCEjsnvtgLERRNeNeL9z\n");
    testPrivateKey.append("YPTjNZy0/Pi0ZkdjWHc4yiUYH/bxE1foRHjDEPfkvJbFoXv1dpRZaVAUYgUULkyu\n");
    testPrivateKey.append("6NQOMGu7FuMMLQcp96NSdzH1QXUCgYEA+vf1wAeYRICWSe9EBe/mMeeD2Lgi0pWy\n");
    testPrivateKey.append("SAoCxN6t5nvBgcW91hK0RDTOTMhOAks0Vzdpa9QHQoUFbhyh2twWmGcXr6D8jqVy\n");
    testPrivateKey.append("J9Sh77Y6BfRuFDQ7eCOwfO0mPRPuqbJ/1eylaOwxyyt+uSa9WdN1mgyycAXAEY64\n");
    testPrivateKey.append("PMdllAOaEC0CgYAf60nc+0xWDV3Q48NP2U0hWLx+45PIbbi0ISLx6cTG4JGgImkm\n");
    testPrivateKey.append("AHndPHFI6QhgR5kaAuISdSn8AS2s6i3tEROvWdyIoBrXdUOOinpBOGNNME+Z5EIw\n");
    testPrivateKey.append("xxGIAflhjXWID+8FUx/fT8Ufgg/EuLCGYIrfncfC2gRfazTj+kiS2103OQKBgQDE\n");
    testPrivateKey.append("AEmGaqgJv98f6ORYOq6uBOCcrdpMWqr8xgy5kiuAWOCcqEGFYeA1cIQ5xSnfcrpy\n");
    testPrivateKey.append("7wy/ML1mvxqpj2T812wyJDmEaZc1FJMd9ltuKgQQyH/7+XsEbeMU/eUiSGHZWFWs\n");
    testPrivateKey.append("TgA0/Fo7EUIL+exhrdsnr4jgIi2JyMusdBGp0lJNFQKBgHpUGO5Dhp/B2PuTXfZv\n");
    testPrivateKey.append("F4a4B12TR8UseVXuAf7fhgToNxPZ8iHs+Q5VNGUUNwvNMdr9NixiQ/7+Nljfols5\n");
    testPrivateKey.append("m50QwVZLiepEzwix9HbKcabOyqzJZHzMzZb6S2/vJetx6BJYemPAZkZ5L+fBaKON\n");
    testPrivateKey.append("FzyHGCmwZlgsKQZcyINHutBN\n");
    testPrivateKey.append("-----END PRIVATE KEY-----");

    return testPrivateKey;
}

RSA *GetCipher::getPublicKey(QByteArray &data)
{
    const char* publicKeyStr = data.constData();
    BIO* bio = BIO_new_mem_buf((void*)publicKeyStr, -1);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);

    RSA* rsaPubKey = PEM_read_bio_RSA_PUBKEY(bio, NULL, NULL, NULL);
    if (!rsaPubKey)
    {
//        qCritical() << "Cloud not load public key" << ERR_error_string(ERR_get_error(), NULL);
    }

    BIO_free(bio);
    return rsaPubKey;
}

RSA *GetCipher::getPrivateKey(QByteArray &data)
{
    const char* privateKeyStr = data.constData();
    BIO* bio = BIO_new_mem_buf((void*)privateKeyStr, -1);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);

    RSA* rsaPrivKey = PEM_read_bio_RSAPrivateKey(bio, NULL, NULL, NULL);
    if (!rsaPrivKey)
    {
//        qCritical() << "Cloud not load private key" << ERR_error_string(ERR_get_error(), NULL);
    }

    BIO_free(bio);
    return rsaPrivKey;
}

QByteArray GetCipher::encryptRSA(RSA *key, QByteArray &data)
{
    QByteArray buffer;
    int dataSize = data.length();
    const unsigned char* str = (const unsigned char*)data.constData();
    int rsaLen = RSA_size(key);

    unsigned char* ed = (unsigned char*)malloc(rsaLen);

    int resultLen = RSA_public_encrypt(dataSize, (const unsigned char*)str, ed, key, PADDING);

    if (resultLen == -1)
    {
//        qCritical() << "Coult not encrypt: " << ERR_error_string(ERR_get_error(), NULL);
        return buffer;
    }

    buffer = QByteArray(reinterpret_cast<char*>(ed), resultLen);

    return buffer;
}

QByteArray GetCipher::decryptRSA(RSA *key, QByteArray &data)
{
    QByteArray buffer;
    const unsigned char* encryptedData = (const unsigned char*)data.constData();

//    int dataSize = data.length();
//    const unsigned char* str = (const unsigned char*)data.constData();
    int rsaLen = RSA_size(key);

    unsigned char* ed = (unsigned char*)malloc(rsaLen);

    int resultLen = RSA_private_decrypt(rsaLen, (const unsigned char*)encryptedData, ed, key, PADDING);

    if (resultLen == -1)
    {
//        qCritical() << "Coult not decrypt: " << ERR_error_string(ERR_get_error(), NULL);
        return buffer;
    }

//    buffer = QByteArray(reinterpret_cast<char*>(ed), resultLen);
    buffer = QByteArray::fromRawData((const char*)ed, resultLen);
    return buffer;
}

QByteArray GetCipher::encryptAES(QByteArray passphrase, QByteArray &data)
{
    QByteArray msalt = randomBytes(SALTSIZE);
       int rounds = 1;
       unsigned char key[KEYSIZE];
       unsigned char iv[IVSIZE];
       const unsigned char *password = (const unsigned char*) passphrase.constData();
       const unsigned char *salt = (const unsigned char*) msalt.constData();

       int i = EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), salt, password, passphrase.length(), rounds, key, iv);

       if (i != KEYSIZE) {
//           qCritical() << "EVP_BytesToKey() -- " << ERR_error_string(ERR_get_error(), NULL);
           return QByteArray();
       }

       EVP_CIPHER_CTX *en = EVP_CIPHER_CTX_new();
       EVP_CIPHER_CTX_init(en);

       if (!EVP_EncryptInit_ex(en, EVP_aes_256_cbc(), NULL, key, iv)) {
//           qCritical() << "EVP_EncryptInit_ex() -- " << ERR_error_string(ERR_get_error(), NULL);
           return QByteArray();
       }

       char *input = data.data();
       char *out;
       int length = data.size();


       int cLength = length + AES_BLOCK_SIZE;
       int fLength = 0;
       unsigned char *cipherText = (unsigned char*) malloc(cLength);

       if (!EVP_EncryptInit_ex(en, NULL, NULL, NULL, NULL)) {
//           qCritical() << "EVP_EncryptInit_ex() -- " << ERR_error_string(ERR_get_error(), NULL);
           return QByteArray();
       }

       if (!EVP_EncryptUpdate(en, cipherText, &cLength, (unsigned char*) input, length)) {
//           qCritical() << "EVP_EncryptUpdate() -- " << ERR_error_string(ERR_get_error(), NULL);
           free(cipherText);
           return QByteArray();
       }

       if (!EVP_EncryptFinal(en, cipherText + cLength, &fLength)) {
//           qCritical() << "EVP_EncryptFinal() -- " << ERR_error_string(ERR_get_error(), NULL);
           free(cipherText);
           return QByteArray();
       }

       length = cLength + fLength;
       out = (char*) cipherText;
       EVP_CIPHER_CTX_cipher(en);

       free(cipherText);

       QByteArray output;
       output.append("Salted__");
       output.append(msalt);
       output.append(out, length);

       return output;
}

QByteArray GetCipher::decryptAES(RSA *key, QByteArray &data)
{
    return nullptr;
}

QByteArray GetCipher::randomBytes(int size)
{
    return nullptr;
}

void GetCipher::freenRSAKey(RSA *key)
{
    RSA_free(key);
}

void Cipher::initalize()
{
    ERR_load_CRYPTO_strings();
    OpenSSL_add_all_algorithms();
    OPENSSL_config(NULL);
}

void Cipher::finelize()
{
    EVP_cleanup();
    ERR_free_strings();
}
