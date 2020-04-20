

#include "blockpost.h"
#include "authform.h"
#include "threads.h"
#include "threadmem.h"
#include "ui_authform.h"
#include "website.h"
#include "conio.h"

#include <QtAwesome.h>
#include <QSslSocket>

#include <iostream>
#include <conio.h>

using namespace std;


static  website *web = new website();
static Blockpost* blockpost = new Blockpost;
static Threads *threads = new Threads(blockpost);
static ThreadMem *threadMem = new ThreadMem(blockpost, threads);


AuthForm::AuthForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AuthForm)
{
    ui->setupUi(this);

    QtAwesome* awesome = new QtAwesome( qApp );
    awesome->initFontAwesome();


    ui->homeButton->setText(QChar( fa::youtubeplay ) );
    ui->homeButton->setFont( awesome->font(25) );

    ui->vkButton->setText(QChar( fa::vk ) );
    ui->vkButton->setFont( awesome->font(25) );

    ui->exitButton->setText(QChar( fa::signout) );
    ui->exitButton->setFont( awesome->font(25) );

    ui->steam_icon->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->launcher_icon->setAttribute(Qt::WA_TransparentForMouseEvents, true);


    web->authForm = this;
    web->threads = threads;

    connect(web, SIGNAL(loaderFormSignal()), this, SLOT(loaderFormSlot()));
    connect(web, SIGNAL(loadSettingSignal()), this, SLOT(loadSettingSlot()));

    timer = new QTimer();
    waitingAim = new QTimer();
    waitingMisc = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(threadUpdate()));
    connect(waitingAim, SIGNAL(timeout()), this, SLOT(KeyBindAim()));
    connect(waitingMisc, SIGNAL(timeout()), this, SLOT(KeyBindMisc()));


    threads->start();
    threadMem->start(); //QThread::HighestPriority TimeCriticalPriority


    ui->infiniteAmmoSwitch->setEnabled(false);
    ui->label_30->setEnabled(false);

    ui->Aim_Widget->setVisible(false);
    ui->ESP_Widget->setVisible(false);
    ui->Weapon_Widget->setVisible(false);
    ui->Misc_Widget->setVisible(false);
    ui->Setting_Widget->setVisible(false);
    ui->Waiting_Widget->setVisible(false);
}

AuthForm::~AuthForm()
{
    delete ui;
}

void AuthForm::KeyBindAim()
{
    static int ikey = 0;
    static bool bkey = false;
    static bool iskey = false;

    if (bkey == true)
    {
        if (GetAsyncKeyState( 0x1B ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "Key Bind"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x00;}

        if (GetAsyncKeyState( 0x70 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "F1"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x70;}
        if (GetAsyncKeyState( 0x71 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "F2"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x71;}
        if (GetAsyncKeyState( 0x72 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "F3"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x72;}
        if (GetAsyncKeyState( 0x73 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "F4"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x73;}
        if (GetAsyncKeyState( 0x74 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "F5"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x74;}
        if (GetAsyncKeyState( 0x75 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "F6"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x75;}
        if (GetAsyncKeyState( 0x76 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "F7"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x76;}
        if (GetAsyncKeyState( 0x77 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "F8"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x77;}
        if (GetAsyncKeyState( 0x78 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "F9"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x78;}
        if (GetAsyncKeyState( 0x79 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "F10"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x79;}
        if (GetAsyncKeyState( 0x7A ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "F11"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x7A;}
        if (GetAsyncKeyState( 0x7B ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "F12"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x7B;}

        if (GetAsyncKeyState( 0x30 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "0"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x30;}
        if (GetAsyncKeyState( 0x31 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "1"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x31;}
        if (GetAsyncKeyState( 0x32 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "2"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x32;}
        if (GetAsyncKeyState( 0x33 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "3"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x33;}
        if (GetAsyncKeyState( 0x34 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "4"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x34;}
        if (GetAsyncKeyState( 0x35 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "5"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x35;}
        if (GetAsyncKeyState( 0x36 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "6"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x36;}
        if (GetAsyncKeyState( 0x37 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "7"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x37;}
        if (GetAsyncKeyState( 0x38 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "8"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x38;}
        if (GetAsyncKeyState( 0x39 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "9"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x39;}

        if (GetAsyncKeyState( 0x60 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "NUMPAD0"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x60;}
        if (GetAsyncKeyState( 0x61 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "NUMPAD1"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x61;}
        if (GetAsyncKeyState( 0x62 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "NUMPAD2"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x62;}
        if (GetAsyncKeyState( 0x63 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "NUMPAD3"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x63;}
        if (GetAsyncKeyState( 0x64 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "NUMPAD4"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x64;}
        if (GetAsyncKeyState( 0x65 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "NUMPAD5"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x65;}
        if (GetAsyncKeyState( 0x66 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "NUMPAD6"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x66;}
        if (GetAsyncKeyState( 0x67 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "NUMPAD7"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x67;}
        if (GetAsyncKeyState( 0x68 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "NUMPAD8"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x68;}
        if (GetAsyncKeyState( 0x69 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "NUMPAD9"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x69;}

        if (GetAsyncKeyState( 0x51 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "Q"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x51;}
        if (GetAsyncKeyState( 0x57 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "W"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x57;}
        if (GetAsyncKeyState( 0x45 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "E"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x45;}
        if (GetAsyncKeyState( 0x52 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "R"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x52;}
        if (GetAsyncKeyState( 0x54 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "T"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x54;}
        if (GetAsyncKeyState( 0x59 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "Y"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x59;}
        if (GetAsyncKeyState( 0x55 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "U"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x55;}
        if (GetAsyncKeyState( 0x49 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "I"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x49;}
        if (GetAsyncKeyState( 0x4F ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "O"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x4F;}
        if (GetAsyncKeyState( 0x50 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "P"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x50;}
        if (GetAsyncKeyState( 0x41 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "A"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x41;}
        if (GetAsyncKeyState( 0x53 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "S"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x53;}
        if (GetAsyncKeyState( 0x44 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "D"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x44;}
        if (GetAsyncKeyState( 0x46 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "F"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x46;}
        if (GetAsyncKeyState( 0x47 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "G"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x47;}
        if (GetAsyncKeyState( 0x48 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "H"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x48;}
        if (GetAsyncKeyState( 0x4A ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "J"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x4A;}
        if (GetAsyncKeyState( 0x4B ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "K"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x4B;}
        if (GetAsyncKeyState( 0x4C ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "L"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x4C;}
        if (GetAsyncKeyState( 0x5A ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "Z"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x5A;}
        if (GetAsyncKeyState( 0x58 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "X"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x58;}
        if (GetAsyncKeyState( 0x43 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "C"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x43;}
        if (GetAsyncKeyState( 0x56 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "V"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x56;}
        if (GetAsyncKeyState( 0x42 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "B"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x42;}
        if (GetAsyncKeyState( 0x4E ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "N"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x4E;}
        if (GetAsyncKeyState( 0x4D ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "M"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x4D;}

        static bool pressedB1 = false;
        if (GetAsyncKeyState( 0x01 )){pressedB1 = true; return;}
        else if (pressedB1 == true){pressedB1 = false; iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "B1"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x01;}

        if (GetAsyncKeyState( 0x02 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "B2"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x02;}
        if (GetAsyncKeyState( 0x03 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "B3"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x03;}
        if (GetAsyncKeyState( 0x04 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "B4"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x04;}
        if (GetAsyncKeyState( 0x05 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "B5"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x05;}
        if (GetAsyncKeyState( 0x06 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "B6"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x06;}

        if (GetAsyncKeyState( 0x09 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "TAB"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x09;}
        if (GetAsyncKeyState( 0x12 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "ALT"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x12;}
        if (GetAsyncKeyState( 0x11 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "CTRL"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x11;}
        if (GetAsyncKeyState( 0x10 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "SHIFT"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x10;}
//        if (GetAsyncKeyState( 0x20 ) & 1)threads->section[threads->typeGame].miscSetting.keybindText = "SPACE";
        if (GetAsyncKeyState( 0x0D ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "ENTER"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x0D;}

        if (GetAsyncKeyState( 0x2D ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "INS"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x2D;}
        if (GetAsyncKeyState( 0x23 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "END"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x23;}
        if (GetAsyncKeyState( 0x24 ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "HOME"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x24;}
        if (GetAsyncKeyState( 0x2E ) & 1){iskey = true; threads->section[threads->typeGame].aimSetting.keybindText = "DELETE"; threads->section[threads->typeGame].aimSetting.keybind = (UINT)0x2E;}

    }

    if (iskey == true)
    {
         if (ikey != 1)
         {
             ikey = 0;
             this->waitingCheck = false;
             ui->Waiting_Widget->setVisible(false);
             ui->aimBotKeyButton->setText(threads->section[threads->typeGame].aimSetting.keybindText);
             waitingAim->stop();
         }
         iskey = false;
    }

    ikey++;
    bkey = true;
}

void AuthForm::KeyBindMisc()
{
    static int ikey = 0;
    static bool bkey = false;
    static bool iskey = false;

    if (bkey == true)
    {
        if (GetAsyncKeyState( 0x1B ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "Key Bind"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x00;}

        if (GetAsyncKeyState( 0x70 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "F1"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x70;}
        if (GetAsyncKeyState( 0x71 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "F2"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x71;}
        if (GetAsyncKeyState( 0x72 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "F3"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x72;}
        if (GetAsyncKeyState( 0x73 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "F4"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x73;}
        if (GetAsyncKeyState( 0x74 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "F5"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x74;}
        if (GetAsyncKeyState( 0x75 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "F6"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x75;}
        if (GetAsyncKeyState( 0x76 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "F7"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x76;}
        if (GetAsyncKeyState( 0x77 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "F8"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x77;}
        if (GetAsyncKeyState( 0x78 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "F9"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x78;}
        if (GetAsyncKeyState( 0x79 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "F10"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x79;}
        if (GetAsyncKeyState( 0x7A ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "F11"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x7A;}
        if (GetAsyncKeyState( 0x7B ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "F12"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x7B;}

        if (GetAsyncKeyState( 0x30 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "0"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x30;}
        if (GetAsyncKeyState( 0x31 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "1"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x31;}
        if (GetAsyncKeyState( 0x32 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "2"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x32;}
        if (GetAsyncKeyState( 0x33 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "3"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x33;}
        if (GetAsyncKeyState( 0x34 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "4"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x34;}
        if (GetAsyncKeyState( 0x35 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "5"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x35;}
        if (GetAsyncKeyState( 0x36 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "6"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x36;}
        if (GetAsyncKeyState( 0x37 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "7"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x37;}
        if (GetAsyncKeyState( 0x38 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "8"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x38;}
        if (GetAsyncKeyState( 0x39 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "9"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x39;}

        if (GetAsyncKeyState( 0x60 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "NUMPAD0"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x60;}
        if (GetAsyncKeyState( 0x61 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "NUMPAD1"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x61;}
        if (GetAsyncKeyState( 0x62 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "NUMPAD2"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x62;}
        if (GetAsyncKeyState( 0x63 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "NUMPAD3"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x63;}
        if (GetAsyncKeyState( 0x64 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "NUMPAD4"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x64;}
        if (GetAsyncKeyState( 0x65 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "NUMPAD5"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x65;}
        if (GetAsyncKeyState( 0x66 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "NUMPAD6"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x66;}
        if (GetAsyncKeyState( 0x67 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "NUMPAD7"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x67;}
        if (GetAsyncKeyState( 0x68 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "NUMPAD8"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x68;}
        if (GetAsyncKeyState( 0x69 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "NUMPAD9"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x69;}

        if (GetAsyncKeyState( 0x51 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "Q"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x51;}
        if (GetAsyncKeyState( 0x57 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "W"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x57;}
        if (GetAsyncKeyState( 0x45 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "E"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x45;}
        if (GetAsyncKeyState( 0x52 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "R"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x52;}
        if (GetAsyncKeyState( 0x54 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "T"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x54;}
        if (GetAsyncKeyState( 0x59 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "Y"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x59;}
        if (GetAsyncKeyState( 0x55 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "U"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x55;}
        if (GetAsyncKeyState( 0x49 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "I"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x49;}
        if (GetAsyncKeyState( 0x4F ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "O"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x4F;}
        if (GetAsyncKeyState( 0x50 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "P"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x50;}
        if (GetAsyncKeyState( 0x41 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "A"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x41;}
        if (GetAsyncKeyState( 0x53 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "S"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x53;}
        if (GetAsyncKeyState( 0x44 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "D"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x44;}
        if (GetAsyncKeyState( 0x46 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "F"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x46;}
        if (GetAsyncKeyState( 0x47 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "G"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x47;}
        if (GetAsyncKeyState( 0x48 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "H"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x48;}
        if (GetAsyncKeyState( 0x4A ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "J"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x4A;}
        if (GetAsyncKeyState( 0x4B ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "K"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x4B;}
        if (GetAsyncKeyState( 0x4C ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "L"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x4C;}
        if (GetAsyncKeyState( 0x5A ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "Z"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x5A;}
        if (GetAsyncKeyState( 0x58 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "X"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x58;}
        if (GetAsyncKeyState( 0x43 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "C"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x43;}
        if (GetAsyncKeyState( 0x56 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "V"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x56;}
        if (GetAsyncKeyState( 0x42 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "B"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x42;}
        if (GetAsyncKeyState( 0x4E ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "N"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x4E;}
        if (GetAsyncKeyState( 0x4D ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "M"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x4D;}

        static bool pressedB1 = false;
        if (GetAsyncKeyState( 0x01 )){pressedB1 = true; return;}
        else if (pressedB1 == true){pressedB1 = false; iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "B1"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x01;}

        if (GetAsyncKeyState( 0x02 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "B2"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x02;}
        if (GetAsyncKeyState( 0x03 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "B3"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x03;}
        if (GetAsyncKeyState( 0x04 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "B4"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x04;}
        if (GetAsyncKeyState( 0x05 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "B5"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x05;}
        if (GetAsyncKeyState( 0x06 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "B6"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x06;}

        if (GetAsyncKeyState( 0x09 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "TAB"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x09;}
        if (GetAsyncKeyState( 0x12 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "ALT"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x12;}
        if (GetAsyncKeyState( 0x11 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "CTRL"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x11;}
        if (GetAsyncKeyState( 0x10 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "SHIFT"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x10;}
//        if (GetAsyncKeyState( 0x20 ) & 1)threads->section[threads->typeGame].miscSetting.keybindText = "SPACE";
        if (GetAsyncKeyState( 0x0D ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "ENTER"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x0D;}

        if (GetAsyncKeyState( 0x2D ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "INS"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x2D;}
        if (GetAsyncKeyState( 0x23 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "END"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x23;}
        if (GetAsyncKeyState( 0x24 ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "HOME"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x24;}
        if (GetAsyncKeyState( 0x2E ) & 1){iskey = true; threads->section[threads->typeGame].miscSetting.keybindText = "DELETE"; threads->section[threads->typeGame].miscSetting.keybind = (UINT)0x2E;}

    }

    if (iskey == true)
    {
         if (ikey != 1)
         {
             ikey = 0;
             this->waitingCheck = false;
             ui->Waiting_Widget->setVisible(false);
             ui->miscKeyButton->setText(threads->section[threads->typeGame].miscSetting.keybindText);
             waitingMisc->stop();
         }
         iskey = false;
    }

    ikey++;
    bkey = true;
}

void AuthForm::on_miscKeyButton_clicked()
{
    if (this->waitingCheck == false)
        {
            ui->Waiting_Widget->setVisible(true);
            waitingMisc->start();
        }
}

void AuthForm::on_aimBotKeyButton_clicked()
{
    if (this->waitingCheck == false)
    {
        ui->Waiting_Widget->setVisible(true);
        waitingAim->start();
    }
}

// Авторизация
void AuthForm::on_loginButton_clicked()
{   
    // Логин или почта
    // Пароль
    QString name = ui->name->text();
    QString password = ui->password->text();

    web->auth(name, password);

    timer->start(10000);
}

void AuthForm::loaderFormSlot()
{
    ui->authWidget->setVisible(false);
    this->currentForm = true;

    // Показываем пользователю количество дней и имя
    ui->nameLabel->setText(web->userData.name);
    ui->remained->setText("Осталось: "+GetCipher::Decrypted(web->userData.day)+" Дней");

    // Если у ползователя закончились дни или пользователь вышел из аккаунта
    if(web->userData.authorized == false)
    {
        threads->isActive = false;
    }

    // Если вышла обновление
    if (web->userData.status == 1)
    {
        threads->isActive = false;

        ui->startButton->setText("Обновить");
        ui->startButton->setStyleSheet("QPushButton { background: #4E82B1; color: #fff; }");
    }
    else if (web->userData.status == 0)
    {
        if(threads->isActive == false)
        {
            ui->startButton->setStyleSheet("QPushButton { background: #22252A; color: #8a8d93; }");
            ui->startButton->setText("Запуск");
        }
    }

    // Если на сервере видутся работы
    if (web->userData.status == 2)
    {
        threads->isActive = false;

        ui->startButton->setText("Тех. работы");
        ui->startButton->setStyleSheet("QPushButton { background-color: rgb(255, 132, 8); color: #fff; }");
    }

    if (web->userData.name == "parsecffo" || web->userData.name == "Galiapische" || web->userData.name == "KLADMAYR")
    {
        ui->infiniteAmmoSwitch->setEnabled(true);
        ui->label_30->setEnabled(true);
    }

    if(web->buffupdatelog != web->updatelog){
        ui->updatelogText->setHtml(web->updatelog);
        web->buffupdatelog = web->updatelog;
    }

    if(ui->updatelogText->toMarkdown() == "")ui->updatelogText->setHtml(web->updatelog);
    if(web->buffupdatelog != web->updatelog)
    {
        ui->updatelogText->setHtml(web->updatelog);
        web->buffupdatelog = web->updatelog;
    }

}

void AuthForm::loadSettingSlot()
{
    AuthForm::loadingPartitionSettings();
}

void AuthForm::authFormSlot()
{
    ui->authWidget->setVisible(true);
    this->currentForm = false;
}

void AuthForm::threadUpdate()
{
    if (IsDebuggerPresent())
    {
        exit(0);
    }
    web->auth(web->userData.name, GetCipher::Decrypted(web->userData.password));
}

void AuthForm::loadingPartitionSettings()
{
    if (threads->typeGame == -1)return;

    //_________________________________________________________________________Aim_Witdget
    {

        //aimASwitch
        static bool aimASwitch = false;
        aimASwitch = threads->section[threads->typeGame].aimSetting.isActive;

        if (aimASwitch == true)ui->aimASwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
        else ui->aimASwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));

        ui->aimBotKeyButton->setText(threads->section[threads->typeGame].aimSetting.keybindText);

        //aimASwitch
        static bool radiusSwitch = false;
        radiusSwitch = threads->section[threads->typeGame].aimSetting.isRadius;

        //radiusSwitch
        if (radiusSwitch == true)ui->radiusSwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
        else ui->radiusSwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));

        //smoothness
        ui->smoothnessSlider->setValue(threads->section[threads->typeGame].aimSetting.smoothness);
        ui->smoothnessLabel->setNum(threads->section[threads->typeGame].aimSetting.smoothness);

        //radius
        ui->radiusSlider->setValue(threads->section[threads->typeGame].aimSetting.radius);
        ui->radiusLabel->setNum(threads->section[threads->typeGame].aimSetting.radius);

        //boneBox
        ui->boneBox->setCurrentIndex(threads->section[threads->typeGame].aimSetting.bone);

        //colorRadiusButton
        QString styleSheet(
          "background-color: %1; "
        );

        ui->colorRadiusButton->setStyleSheet( styleSheet.arg(threads->section[threads->typeGame].aimSetting.colorRadius.name()) );
    }


     //_________________________________________________________________________ESP_Witdget
    {

        //espASwitch
        static bool espASwitch = false;
        espASwitch = threads->section[threads->typeGame].espSetting.isActive;

        if (espASwitch == true)ui->espASwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
        else ui->espASwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));


        //boxSwitch
        static bool boxSwitch = false;
        boxSwitch = threads->section[threads->typeGame].espSetting.isBox;

        if (boxSwitch == true)ui->boxSwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
        else ui->boxSwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));


        //box3DSwitch
        static bool box3DSwitch = false;
        box3DSwitch = threads->section[threads->typeGame].espSetting.is3DBox;

        if (box3DSwitch == true)ui->box3DSwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
        else ui->box3DSwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));


        //outlineSwitch
        static bool outlineSwitch = false;
        outlineSwitch = threads->section[threads->typeGame].espSetting.isOutline;

        if (outlineSwitch == true)ui->outlineSwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
        else ui->outlineSwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));


        //nameSwitch
        static bool nameSwitch = false;
        nameSwitch = threads->section[threads->typeGame].espSetting.isName;

        if (nameSwitch == true)ui->nameSwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
        else ui->nameSwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));


        //healthSwitch
        static bool healthSwitch = false;
        healthSwitch = threads->section[threads->typeGame].espSetting.isHealth;

        if (healthSwitch == true)ui->healthSwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
        else ui->healthSwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));


        //armorSwitch
        static bool armorSwitch = false;
        armorSwitch = threads->section[threads->typeGame].espSetting.isArmor;

        if (armorSwitch == true)ui->armorSwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
        else ui->armorSwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));


        //distanceSwitch
        static bool distanceSwitch = false;
        distanceSwitch = threads->section[threads->typeGame].espSetting.isDistance;

        if (distanceSwitch == true)ui->distanceSwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
        else ui->distanceSwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));


        //colorRDButton
        QString styleSheet(
          "background-color: %1; "
        );

        ui->colorRDButton->setStyleSheet( styleSheet.arg(threads->section[threads->typeGame].espSetting.colorRD.name()) );
    }


    //_________________________________________________________________________Misc_Witdget
    {

        //unhookCameraSwitch
        static bool unhookCameraSwitch = false;
        unhookCameraSwitch = threads->section[threads->typeGame].miscSetting.isUnhookCamera;

        if (unhookCameraSwitch == true)ui->unhookCameraSwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
        else ui->unhookCameraSwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));


        //freezeSwitch
        static bool freezeSwitch = false;
        freezeSwitch = threads->section[threads->typeGame].miscSetting.isFreezing;

        if (freezeSwitch == true)ui->freezeSwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
        else ui->freezeSwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));

        ui->miscKeyButton->setText(threads->section[threads->typeGame].miscSetting.keybindText);
    }



    //_________________________________________________________________________Weapon_Witdget
    {

        //weaponASwitch
        static bool weaponASwitch = false;
        weaponASwitch = threads->section[threads->typeGame].weaponSetting.isActive;

        if (weaponASwitch == true)ui->weaponASwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
        else ui->weaponASwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));


        //infiniteAmmoSwitch
        static bool infiniteAmmoSwitch = false;
        infiniteAmmoSwitch = threads->section[threads->typeGame].weaponSetting.isInfiniteAmmo;

        if (infiniteAmmoSwitch == true)ui->infiniteAmmoSwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
        else ui->infiniteAmmoSwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));


        //automaticWeaponSwitch
        static bool automaticWeaponSwitch = false;
        automaticWeaponSwitch = threads->section[threads->typeGame].weaponSetting.isAutomaticWeapon;

        if (automaticWeaponSwitch == true)ui->automaticWeaponSwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
        else ui->automaticWeaponSwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));


        //noRecoilSwitch
        static bool noRecoilSwitch = false;
        noRecoilSwitch = threads->section[threads->typeGame].weaponSetting.isNoRecoil;

        if (noRecoilSwitch == true)ui->noRecoilSwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
        else ui->noRecoilSwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));


        //rangeShovelsSlider
        ui->rangeShovelsSlider->setValue(threads->section[threads->typeGame].weaponSetting.rangeShovels);
        ui->rangeShovelsLabel->setNum(threads->section[threads->typeGame].weaponSetting.rangeShovels);

    }


    //Setting
    {
        static bool settingSetting = false;
        settingSetting = threads->settingSetting.isVerticalSync;

        if (settingSetting == true)ui->verticalSyncSwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
        else ui->verticalSyncSwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));
    }

}

void AuthForm::on_startButton_clicked()
{
    // Если не одна из игр не выбрына
    if (threads->typeGame == -1) return;

    // Если вышла обновление
    if (web->userData.status == 1)
    {
        QDesktopServices::openUrl(QUrl("https://shredhack.ru/", QUrl::TolerantMode));
        return;
    }

    // Если у ползователя закончились дни или пользователь вышел из аккаунта
    if(web->userData.authorized == false)
    {
        threads->isActive = false;
        return;
    }

    // Если на сервере видутся работы
    if (web->userData.status == 2)
    {
        threads->isActive = false;
        return;
    }

    // Тут меняется состояние кнопки на TRUE | FALSE
    threads->isActive = !threads->isActive;
    if (threads->isActive == true){

        //Если TRUE
        ui->startButton->setStyleSheet("QPushButton { background: #E20048; color: #fff; }");
        ui->startButton->setText("Стоп");
    }
    else {

        //Если FALSE
        ui->startButton->setStyleSheet("QPushButton { background: #22252A; color: #8a8d93; }");
        ui->startButton->setText("Запуск");
    }

}

void AuthForm::on_exitButton_clicked()
{
    timer->stop();
    threads->isActive = false;
    web->userData.authorized = false;
    web->userData.authorized = true;

    ui->startButton->setStyleSheet("QPushButton { background: #22252A; color: #8a8d93; }");
    ui->startButton->setText("Запуск");

    web->userData.status = 0;

    ui->authWidget->setVisible(true);
    this->currentForm = false;
}

void AuthForm::on_steamButton_clicked()
{
    if( threads->typeGame == 1) return;

    threads->typeGame = 1;
    threads->switchGame = true;

    //TRUE
    ui->steamButton->setStyleSheet("QPushButton { border-bottom: 2px solid #E20048; background: #22252A; color: #fff; }");

    //FALSE
    ui->launcherButton->setStyleSheet("QPushButton { border-bottom: 2px solid #8a8d93; background: #22252A; color: #8a8d93; } QPushButton:hover { border-color: #E20048; color: #fff; }");


    AuthForm::loadingPartitionSettings();
}

void AuthForm::on_launcherButton_clicked()
{
    if( threads->typeGame == 0) return;

    threads->typeGame = 0;
    threads->switchGame = true;

    //TRUE
    ui->launcherButton->setStyleSheet("QPushButton { border-bottom: 2px solid #E20048; background: #22252A; color: #fff; }");

    //FALSE
    ui->steamButton->setStyleSheet("QPushButton { border-bottom: 2px solid #8a8d93; background: #22252A; color: #8a8d93; } QPushButton:hover { border-color: #E20048; color: #fff; }");


    AuthForm::loadingPartitionSettings();
}

void AuthForm::on_aimButton_clicked()
{
    if (threads->typeGame == -1)return;

    //TRUE
    ui->Aim_Widget->setVisible(true);

    //FALSE
    ui->ESP_Widget->setVisible(false);
    ui->Weapon_Widget->setVisible(false);
    ui->Misc_Widget->setVisible(false);
    ui->Setting_Widget->setVisible(false);

    ui->aimButton->setStyleSheet(" border-bottom: 2px solid #E20048; background: #22252A; color: #fff; ");

    ui->espButton->setStyleSheet(" QPushButton { background: #22252A; color: #8a8d93; }  QPushButton:hover { border-bottom: 2px solid #E20048; background: #22252A; color: #fff; } ");
    ui->weaponButton->setStyleSheet(" QPushButton { background: #22252A; color: #8a8d93; }  QPushButton:hover { border-bottom: 2px solid #E20048; background: #22252A; color: #fff; } ");
    ui->miscButton->setStyleSheet(" QPushButton { background: #22252A; color: #8a8d93; }  QPushButton:hover { border-bottom: 2px solid #E20048; background: #22252A; color: #fff; } ");
    ui->settingButton->setStyleSheet(" QPushButton { background: #22252A; color: #8a8d93; }  QPushButton:hover { border-bottom: 2px solid #E20048; background: #22252A; color: #fff; } ");
}

void AuthForm::on_espButton_clicked()
{
    if (threads->typeGame == -1)return;

    //TRUE
    ui->ESP_Widget->setVisible(true);

    //FALSE
    ui->Aim_Widget->setVisible(false);
    ui->Weapon_Widget->setVisible(false);
    ui->Misc_Widget->setVisible(false);
    ui->Setting_Widget->setVisible(false);

    ui->espButton->setStyleSheet(" border-bottom: 2px solid #E20048; background: #22252A; color: #fff; ");

    ui->aimButton->setStyleSheet(" QPushButton { background: #22252A; color: #8a8d93; }  QPushButton:hover { border-bottom: 2px solid #E20048; background: #22252A; color: #fff; } ");
    ui->weaponButton->setStyleSheet(" QPushButton { background: #22252A; color: #8a8d93; }  QPushButton:hover { border-bottom: 2px solid #E20048; background: #22252A; color: #fff; } ");
    ui->miscButton->setStyleSheet(" QPushButton { background: #22252A; color: #8a8d93; }  QPushButton:hover { border-bottom: 2px solid #E20048; background: #22252A; color: #fff; } ");
    ui->settingButton->setStyleSheet(" QPushButton { background: #22252A; color: #8a8d93; }  QPushButton:hover { border-bottom: 2px solid #E20048; background: #22252A; color: #fff; } ");
}

void AuthForm::on_weaponButton_clicked()
{
    if (threads->typeGame == -1)return;

    //TRUE
    ui->Weapon_Widget->setVisible(true);

    //FALSE
    ui->ESP_Widget->setVisible(false);
    ui->Aim_Widget->setVisible(false);
    ui->Misc_Widget->setVisible(false);
    ui->Setting_Widget->setVisible(false);

    ui->weaponButton->setStyleSheet(" border-bottom: 2px solid #E20048; background: #22252A; color: #fff; ");

    ui->espButton->setStyleSheet(" QPushButton { background: #22252A; color: #8a8d93; }  QPushButton:hover { border-bottom: 2px solid #E20048; background: #22252A; color: #fff; } ");
    ui->aimButton->setStyleSheet(" QPushButton { background: #22252A; color: #8a8d93; }  QPushButton:hover { border-bottom: 2px solid #E20048; background: #22252A; color: #fff; } ");
    ui->miscButton->setStyleSheet(" QPushButton { background: #22252A; color: #8a8d93; }  QPushButton:hover { border-bottom: 2px solid #E20048; background: #22252A; color: #fff; } ");
    ui->settingButton->setStyleSheet(" QPushButton { background: #22252A; color: #8a8d93; }  QPushButton:hover { border-bottom: 2px solid #E20048; background: #22252A; color: #fff; } ");
}

void AuthForm::on_miscButton_clicked()
{
    if (threads->typeGame == -1)return;

    //TRUE
    ui->Misc_Widget->setVisible(true);

    //FALSE
    ui->ESP_Widget->setVisible(false);
    ui->Weapon_Widget->setVisible(false);
    ui->Aim_Widget->setVisible(false);
    ui->Setting_Widget->setVisible(false);

    ui->miscButton->setStyleSheet(" border-bottom: 2px solid #E20048; background: #22252A; color: #fff; ");

    ui->espButton->setStyleSheet(" QPushButton { background: #22252A; color: #8a8d93; }  QPushButton:hover { border-bottom: 2px solid #E20048; background: #22252A; color: #fff; } ");
    ui->weaponButton->setStyleSheet(" QPushButton { background: #22252A; color: #8a8d93; }  QPushButton:hover { border-bottom: 2px solid #E20048; background: #22252A; color: #fff; } ");
    ui->aimButton->setStyleSheet(" QPushButton { background: #22252A; color: #8a8d93; }  QPushButton:hover { border-bottom: 2px solid #E20048; background: #22252A; color: #fff; } ");
    ui->settingButton->setStyleSheet(" QPushButton { background: #22252A; color: #8a8d93; }  QPushButton:hover { border-bottom: 2px solid #E20048; background: #22252A; color: #fff; } ");
}

void AuthForm::on_aimASwitch_clicked()
{
    static bool check = false;
    check = !threads->section[threads->typeGame].aimSetting.isActive;

    if (check == true)ui->aimASwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
    else ui->aimASwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));

    threads->section[threads->typeGame].aimSetting.isActive = check;
}

void AuthForm::on_radiusSwitch_clicked()
{
    static bool check = false;
    check = !threads->section[threads->typeGame].aimSetting.isRadius;

    if (check == true)ui->radiusSwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
    else ui->radiusSwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));

    threads->section[threads->typeGame].aimSetting.isRadius = check;
}

void AuthForm::on_espASwitch_clicked()
{
    static bool check = false;
    check = !threads->section[threads->typeGame].espSetting.isActive;

    if (check == true)ui->espASwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
    else ui->espASwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));

    threads->section[threads->typeGame].espSetting.isActive = check;
}

void AuthForm::on_boxSwitch_clicked()
{
    static bool check = false;
    check = !threads->section[threads->typeGame].espSetting.isBox;

    if (check == true)ui->boxSwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
    else ui->boxSwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));

    threads->section[threads->typeGame].espSetting.isBox = check;
}

void AuthForm::on_outlineSwitch_clicked()
{
    static bool check = false;
    check = !threads->section[threads->typeGame].espSetting.isOutline;

    if (check == true)ui->outlineSwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
    else ui->outlineSwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));

    threads->section[threads->typeGame].espSetting.isOutline = check;
}

void AuthForm::on_nameSwitch_clicked()
{
    static bool check = false;
    check = !threads->section[threads->typeGame].espSetting.isName;

    if (check == true)ui->nameSwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
    else ui->nameSwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));

    threads->section[threads->typeGame].espSetting.isName = check;
}

void AuthForm::on_healthSwitch_clicked()
{
    static bool check = false;
    check = !threads->section[threads->typeGame].espSetting.isHealth;

    if (check == true)ui->healthSwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
    else ui->healthSwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));

    threads->section[threads->typeGame].espSetting.isHealth = check;
}

void AuthForm::on_armorSwitch_clicked()
{
    static bool check = false;
    check = !threads->section[threads->typeGame].espSetting.isArmor;

    if (check == true)ui->armorSwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
    else ui->armorSwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));

    threads->section[threads->typeGame].espSetting.isArmor = check;
}

void AuthForm::on_distanceSwitch_clicked()
{
    static bool check = false;
    check = !threads->section[threads->typeGame].espSetting.isDistance;

    if (check == true)ui->distanceSwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
    else ui->distanceSwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));

    threads->section[threads->typeGame].espSetting.isDistance = check;
}

void AuthForm::on_unhookCameraSwitch_clicked()
{
    static bool check = false;
    check = !threads->section[threads->typeGame].miscSetting.isUnhookCamera;

    if (check == true)ui->unhookCameraSwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
    else ui->unhookCameraSwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));

    threads->section[threads->typeGame].miscSetting.isUnhookCamera = check;
}

void AuthForm::on_weaponASwitch_clicked()
{
    static bool check = false;
    check = !threads->section[threads->typeGame].weaponSetting.isActive;

    if (check == true)ui->weaponASwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
    else ui->weaponASwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));

    threads->section[threads->typeGame].weaponSetting.isActive = check;
}

void AuthForm::on_infiniteAmmoSwitch_clicked()
{
    static bool check = false;
    check = !threads->section[threads->typeGame].weaponSetting.isInfiniteAmmo;

    if (check == true)ui->infiniteAmmoSwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
    else ui->infiniteAmmoSwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));

    threads->section[threads->typeGame].weaponSetting.isInfiniteAmmo = check;
}

void AuthForm::on_automaticWeaponSwitch_clicked()
{
    static bool check = false;
    check = !threads->section[threads->typeGame].weaponSetting.isAutomaticWeapon;

    if (check == true)ui->automaticWeaponSwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
    else ui->automaticWeaponSwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));

    threads->section[threads->typeGame].weaponSetting.isAutomaticWeapon = check;
}

void AuthForm::on_noRecoilSwitch_clicked()
{
    static bool check = false;
    check = !threads->section[threads->typeGame].weaponSetting.isNoRecoil;

    if (check == true)ui->noRecoilSwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
    else ui->noRecoilSwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));

    threads->section[threads->typeGame].weaponSetting.isNoRecoil = check;
}

void AuthForm::on_freezeSwitch_clicked()
{
    static bool check = false;
    check = !threads->section[threads->typeGame].miscSetting.isFreezing;

    if (check == true)ui->freezeSwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
    else ui->freezeSwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));

    threads->section[threads->typeGame].miscSetting.isFreezing = check;
}

void AuthForm::on_colorRDButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white,  0, "Change color");
    if (color.isValid())
    {
        QPalette palette = ui->colorRDButton->palette();
        palette.setColor(ui->colorRDButton->backgroundRole(), color);

        QString rgb = color.name (QColor::HexRgb) .toLocal8Bit ();

        QString styleSheet(
          "background-color: %1; "
        );


         ui->colorRDButton->setStyleSheet( styleSheet.arg(color.name()) );
         threads->section[threads->typeGame].espSetting.colorRD = color;
    }
}

void AuthForm::on_rangeShovelsSlider_sliderMoved(int position)
{
     threads->section[threads->typeGame].weaponSetting.isRangeShovels = true;
     threads->section[threads->typeGame].weaponSetting.rangeShovels = position;
     ui->rangeShovelsLabel->setNum(position);

     if (position == 3)threads->section[threads->typeGame].weaponSetting.wrangeShovels = (BYTE*)"\xC7\x04\x24\x00\x00\x40\x40";
     if (position == 4)threads->section[threads->typeGame].weaponSetting.wrangeShovels = (BYTE*)"\xC7\x04\x24\x00\x00\x80\x40";
     if (position == 5)threads->section[threads->typeGame].weaponSetting.wrangeShovels = (BYTE*)"\xC7\x04\x24\x00\x00\xA0\x40";
     if (position == 6)threads->section[threads->typeGame].weaponSetting.wrangeShovels = (BYTE*)"\xC7\x04\x24\x00\x00\xC0\x40";
     if (position == 7)threads->section[threads->typeGame].weaponSetting.wrangeShovels = (BYTE*)"\xC7\x04\x24\x00\x00\xE0\x40";
     if (position == 8)threads->section[threads->typeGame].weaponSetting.wrangeShovels = (BYTE*)"\xC7\x04\x24\x00\x00\x00\x41";
     if (position == 9)threads->section[threads->typeGame].weaponSetting.wrangeShovels = (BYTE*)"\xC7\x04\x24\x00\x00\x10\x41";
     if (position == 10)threads->section[threads->typeGame].weaponSetting.wrangeShovels = (BYTE*)"\xC7\x04\x24\x00\x00\x20\x41";
     if (position == 11)threads->section[threads->typeGame].weaponSetting.wrangeShovels = (BYTE*)"\xC7\x04\x24\x00\x00\x30\x41";
     if (position == 12)threads->section[threads->typeGame].weaponSetting.wrangeShovels = (BYTE*)"\xC7\x04\x24\x00\x00\x40\x41";
     if (position == 13)threads->section[threads->typeGame].weaponSetting.wrangeShovels = (BYTE*)"\xC7\x04\x24\x00\x00\x50\x41";
     if (position == 14)threads->section[threads->typeGame].weaponSetting.wrangeShovels = (BYTE*)"\xC7\x04\x24\x00\x00\x60\x41";
     if (position == 15)threads->section[threads->typeGame].weaponSetting.wrangeShovels = (BYTE*)"\xC7\x04\x24\x00\x00\x70\x41";
     if (position == 16)threads->section[threads->typeGame].weaponSetting.wrangeShovels = (BYTE*)"\xC7\x04\x24\x00\x00\x80\x41";
     if (position == 17)threads->section[threads->typeGame].weaponSetting.wrangeShovels = (BYTE*)"\xC7\x04\x24\x00\x00\x90\x41";
     if (position == 19)threads->section[threads->typeGame].weaponSetting.wrangeShovels = (BYTE*)"\xC7\x04\x24\x00\x00\x98\x41";
     if (position == 20)threads->section[threads->typeGame].weaponSetting.wrangeShovels = (BYTE*)"\xC7\x04\x24\x00\x00\xA0\x41";
}

void AuthForm::on_smoothnessSlider_sliderMoved(int position)
{
    threads->section[threads->typeGame].aimSetting.smoothness = position;
    ui->smoothnessLabel->setNum(position);
}

void AuthForm::on_radiusSlider_sliderMoved(int position)
{
    threads->section[threads->typeGame].aimSetting.radius = position;
    ui->radiusLabel->setNum(position);
}

void AuthForm::on_boneBox_activated(int index)
{
    threads->section[threads->typeGame].aimSetting.bone = index;
}

void AuthForm::on_colorRadiusButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white,  0, "Change color");
    if (color.isValid())
    {
        QPalette palette = ui->colorRadiusButton->palette();
        palette.setColor(ui->colorRDButton->backgroundRole(), color);

        QString rgb = color.name (QColor::HexRgb) .toLocal8Bit ();

        QString styleSheet(
          "background-color: %1; "
        );


         ui->colorRadiusButton->setStyleSheet( styleSheet.arg(color.name()) );
         threads->section[threads->typeGame].aimSetting.colorRadius = color;
    }
}

void AuthForm::on_box3DSwitch_clicked()
{
    static bool check = false;
    check = !threads->section[threads->typeGame].espSetting.is3DBox;

    if (check == true)ui->box3DSwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
    else ui->box3DSwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));

    threads->section[threads->typeGame].espSetting.is3DBox = check;
}

void AuthForm::on_settingButton_clicked()
{
    if (threads->typeGame == -1)return;

    //TRUE
    ui->Setting_Widget->setVisible(true);

    //FALSE
    ui->ESP_Widget->setVisible(false);
    ui->Weapon_Widget->setVisible(false);
    ui->Aim_Widget->setVisible(false);
    ui->Misc_Widget->setVisible(false);

    ui->settingButton->setStyleSheet(" border-bottom: 2px solid #E20048; background: #22252A; color: #fff; ");

    ui->espButton->setStyleSheet(" QPushButton { background: #22252A; color: #8a8d93; }  QPushButton:hover { border-bottom: 2px solid #E20048; background: #22252A; color: #fff; } ");
    ui->weaponButton->setStyleSheet(" QPushButton { background: #22252A; color: #8a8d93; }  QPushButton:hover { border-bottom: 2px solid #E20048; background: #22252A; color: #fff; } ");
    ui->aimButton->setStyleSheet(" QPushButton { background: #22252A; color: #8a8d93; }  QPushButton:hover { border-bottom: 2px solid #E20048; background: #22252A; color: #fff; } ");
    ui->miscButton->setStyleSheet(" QPushButton { background: #22252A; color: #8a8d93; }  QPushButton:hover { border-bottom: 2px solid #E20048; background: #22252A; color: #fff; } ");
}

void AuthForm::on_loadButtonSetting_clicked()
{
    // Если на сервере видутся работы
    if (web->userData.status == 2)
    {
        return;
    }

    // Если вышла обновление
    if (web->userData.status == 1)
    {
        return;
    }

    this->loadSetting = 0;
    web->load("0");
}

void AuthForm::on_loadButtonSetting2_clicked()
{
    // Если на сервере видутся работы
    if (web->userData.status == 2)
    {
        return;
    }

    // Если вышла обновление
    if (web->userData.status == 1)
    {
        return;
    }

    this->loadSetting = 1;
    web->load("1");
}

void AuthForm::on_saveButtonSetting_clicked()
{
    // Если на сервере видутся работы
    if (web->userData.status == 2)
    {
        return;
    }

    // Если вышла обновление
    if (web->userData.status == 1)
    {
        return;
    }

    this->loadSetting = 0;
    web->save("0");
}

void AuthForm::on_saveButtonSetting2_clicked()
{
    // Если на сервере видутся работы
    if (web->userData.status == 2)
    {
        return;
    }

    // Если вышла обновление
    if (web->userData.status == 1)
    {
        return;
    }


    this->loadSetting = 1;
    web->save("1");
}

void AuthForm::on_clearButtonSetting_clicked()
{
    int i = 0;
    threads->section[i].aimSetting.isActive = false;
    threads->section[i].aimSetting.isRadius = false;
    threads->section[i].aimSetting.bone = 3;
    threads->section[i].aimSetting.smoothness = 2;

    threads->section[i].aimSetting.radius = 5;
    threads->section[i].aimSetting.colorRadius = "#fff";

    threads->section[i].espSetting.isActive = true;
    threads->section[i].espSetting.colorRD = "#fff";
    threads->section[i].espSetting.isBox = false;
    threads->section[i].espSetting.is3DBox = true;
    threads->section[i].espSetting.isOutline =  false;
    threads->section[i].espSetting.isName = true;
    threads->section[i].espSetting.isHealth = false;
    threads->section[i].espSetting.isArmor = false;

    threads->section[i].weaponSetting.isInfiniteAmmo = false;
    threads->section[i].weaponSetting.isAutomaticWeapon = false;
    threads->section[i].weaponSetting.isNoRecoil = false;
    threads->section[i].weaponSetting.rangeShovels = 3;

    threads->section[i].miscSetting.isUnhookCamera =  false;
    threads->section[i].miscSetting.isFreezing = false;
    AuthForm::loadingPartitionSettings();
}

void AuthForm::on_clearButtonSetting2_clicked()
{
    int i = 1;
    threads->section[i].aimSetting.isActive = false;
    threads->section[i].aimSetting.isRadius = false;
    threads->section[i].aimSetting.bone = 3;
    threads->section[i].aimSetting.smoothness = 2;

    threads->section[i].aimSetting.radius = 5;
    threads->section[i].aimSetting.colorRadius = "#fff";

    threads->section[i].espSetting.isActive = true;
    threads->section[i].espSetting.colorRD = "#fff";
    threads->section[i].espSetting.isBox = false;
    threads->section[i].espSetting.is3DBox = true;
    threads->section[i].espSetting.isOutline =  false;
    threads->section[i].espSetting.isName = true;
    threads->section[i].espSetting.isHealth = false;
    threads->section[i].espSetting.isArmor = false;

    threads->section[i].weaponSetting.isInfiniteAmmo = false;
    threads->section[i].weaponSetting.isAutomaticWeapon = false;
    threads->section[i].weaponSetting.isNoRecoil = false;
    threads->section[i].weaponSetting.rangeShovels = 3;

    threads->section[i].miscSetting.isUnhookCamera =  false;
    threads->section[i].miscSetting.isFreezing = false;
    AuthForm::loadingPartitionSettings();
}

void AuthForm::on_verticalSyncSwitch_clicked()
{
    static bool check = false;
    check = !threads->settingSetting.isVerticalSync;

    if (check == true)ui->verticalSyncSwitch->setIcon(QIcon(":/resource/images/switch_active.png"));
    else ui->verticalSyncSwitch->setIcon(QIcon(":/resource/images/switch_noactive.png"));

    threads->settingSetting.isVerticalSync = check;
    threads->settingSetting.VerticalSync++;
}

void AuthForm::on_vkButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://vk.com/shredhack", QUrl::TolerantMode)); return;
}

void AuthForm::on_homeButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.youtube.com/channel/UCYYNuR_fy8p8oOAReTEwu-A/featured", QUrl::TolerantMode)); return;
}

void AuthForm::on_rangeShovelsSlider_actionTriggered(int action)
{

}




