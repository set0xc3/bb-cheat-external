#ifndef AUTHFORM_H
#define AUTHFORM_H

#include "blockpost.h"
#include "threads.h"
#include <QFont>
#include <QTimer>
#include <QMainWindow>
#include <QUrl>
#include <QPushButton>


QT_BEGIN_NAMESPACE
namespace Ui { class AuthForm; }
QT_END_NAMESPACE

class AuthForm : public QMainWindow
{
    Q_OBJECT

private:
    bool currentForm = false;
    bool waitingCheck = false;
    QPushButton * uiText;

public:
   int loadSetting = -1;

signals:
    void authFormSignal();

public:
    explicit AuthForm(QWidget *parent = nullptr);
    ~AuthForm();

    enum class vKey : UINT
    {
        KEY_MOUSE_BUTTON_LEFT   = 1,
        KEY_MOUSE_BUTTON_RIGHT,
        KEY_CANCEL,
        KEY_MOUSE_BUTTON_MIDDLE,

        KEY_0 = 48,
        KEY_1,
        KEY_2,
        KEY_3,
        KEY_4,
        KEY_5,
        KEY_6,
        KEY_7,
        KEY_8,
        KEY_9,

        KEY_A = 65,
        KEY_B,
        KEY_C,
        KEY_D,
        KEY_E,
        KEY_F,
        KEY_G,
        KEY_H,
        KEY_I,
        KEY_J,
        KEY_K,
        KEY_L,
        KEY_M,
        KEY_N,
        KEY_O,
        KEY_P,
        KEY_Q,
        KEY_R,
        KEY_S,
        KEY_T,
        KEY_U,
        KEY_V,
        KEY_W,
        KEY_X,
        KEY_Y,
        KEY_Z,

        KEY_NUMPAD_0 = 320,
        KEY_NUMPAD_1,
        KEY_NUMPAD_2,
        KEY_NUMPAD_3,
        KEY_NUMPAD_4,
        KEY_NUMPAD_5,
        KEY_NUMPAD_6,
        KEY_NUMPAD_7,
        KEY_NUMPAD_8,
        KEY_NUMPAD_9,

        KEY_F1 = 290,
        KEY_F2,
        KEY_F3,
        KEY_F4,
        KEY_F5,
        KEY_F6,
        KEY_F7,
        KEY_F8,
        KEY_F9,
        KEY_F10,
        KEY_F11,
        KEY_F12,

        KEY_SHIFT_LEFT = 340,
        KEY_CTRL_LEFT,
        KEY_ALT_LEFT,
        KEY_SHIFT_RIGHT = 344,
        KEY_CTRL_RIGHT,
        KEY_ALT_RIGHT,
        KEY_SPACE = 32,

        KEY_ESC = 256,
        KEY_ENTER,
        KEY_TAB,
        KEY_BACKSPACE,

        KEY_INSERT  = 260,
        KEY_DELETE,
        KEY_ARROW_RIGHT,
        KEY_ARROW_LEFT,
        KEY_ARROW_DOWN,
        KEY_ARROW_UP,
        KEY_PAGE_UP,
        KEY_PAGE_DOWN,
        KEY_HOME,
        KEY_END,

        KEY_CAPS_LOCK = 280,
        KEY_SCROLL_LOCK,
        KEY_NUM_LOCK,
        KEY_PRINT_SCREEN,
        KEY_PAUSE,
    };

private slots:

    void loaderFormSlot();
    void loadSettingSlot();
    void authFormSlot();
    void threadUpdate();
    void KeyBindAim();
    void KeyBindMisc();

    void loadingPartitionSettings();

    void on_loginButton_clicked();
    void on_startButton_clicked();
    void on_exitButton_clicked();

    void on_steamButton_clicked();

    void on_launcherButton_clicked();

    void on_aimButton_clicked();

    void on_espButton_clicked();

    void on_weaponButton_clicked();

    void on_miscButton_clicked();

    void on_aimASwitch_clicked();

    void on_radiusSwitch_clicked();

    void on_espASwitch_clicked();

    void on_boxSwitch_clicked();

    void on_outlineSwitch_clicked();

    void on_nameSwitch_clicked();

    void on_healthSwitch_clicked();

    void on_armorSwitch_clicked();

    void on_distanceSwitch_clicked();

    void on_unhookCameraSwitch_clicked();

    void on_weaponASwitch_clicked();

    void on_infiniteAmmoSwitch_clicked();

    void on_automaticWeaponSwitch_clicked();

    void on_noRecoilSwitch_clicked();

    void on_freezeSwitch_clicked();

    void on_colorRDButton_clicked();

    void on_rangeShovelsSlider_sliderMoved(int position);

    void on_smoothnessSlider_sliderMoved(int position);

    void on_radiusSlider_sliderMoved(int position);

    void on_boneBox_activated(int index);

    void on_colorRadiusButton_clicked();



    void on_box3DSwitch_clicked();

    void on_settingButton_clicked();

    void on_loadButtonSetting_clicked();

    void on_loadButtonSetting2_clicked();



    void on_saveButtonSetting_clicked();

    void on_saveButtonSetting2_clicked();

    void on_clearButtonSetting_clicked();

    void on_clearButtonSetting2_clicked();

    void on_verticalSyncSwitch_clicked();

    void on_vkButton_clicked();

    void on_homeButton_clicked();

    void on_rangeShovelsSlider_actionTriggered(int action);

    void on_aimBotKeyButton_clicked();

    void on_miscKeyButton_clicked();

private:
    Ui::AuthForm *ui;

    QTimer *timer;
    QTimer *waitingAim;
    QTimer *waitingMisc;
};
#endif // AUTHFORM_H
