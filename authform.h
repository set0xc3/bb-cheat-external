#ifndef AUTHFORM_H
#define AUTHFORM_H

#include "blockpost.h"
#include "threads.h"
#include <QFont>
#include <QTimer>
#include <QMainWindow>
#include <QUrl>


QT_BEGIN_NAMESPACE
namespace Ui { class AuthForm; }
QT_END_NAMESPACE

class AuthForm : public QMainWindow
{
    Q_OBJECT

private:
    bool currentForm = false;

public:
   int loadSetting = -1;

signals:
    void authFormSignal();

public:
    explicit AuthForm(QWidget *parent = nullptr);
    ~AuthForm();

private slots:

    void loaderFormSlot();
    void loadSettingSlot();
    void authFormSlot();
    void threadUpdate();

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

private:
    Ui::AuthForm *ui;

    QTimer *timer;
};
#endif // AUTHFORM_H
