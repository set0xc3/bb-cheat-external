#include "threadmem.h"
#include "functions.h"
#include "maths_functions.h"


static Blockpost* blockpost = nullptr;
static Threads* threads = nullptr;



ThreadMem::ThreadMem(Blockpost *_blockpost, Threads* _threads)
{
    blockpost = _blockpost;
    threads = _threads;
}

void ThreadMem::Update()
{
    ThreadMem::msleep(500);
    while(true)
    {
        if (IsDebuggerPresent())
        {
            exit(0);
        }

//        qDebug() << "threads->isActive:" << threads->isActive;
//        qDebug() << "threads->typeGame:" << threads->typeGame;
//        qDebug() << "blockpost->module.SteamСlient:" << blockpost->module.SteamСlient;

        Target.Window = FindWindow(nullptr, "BLOCKPOST");
        if (GetForegroundWindow() == Target.Window  && ToolsHack::GetAppstat(nullptr, "BLOCKPOST") == 1)
        {
            GetWindowThreadProcessId(Target.Window, &pid);
            pHandle = ProcessFunctions::GetHandle();
            Target.Checked = true;
            GetWindowRect(Target.Window, &Target.Size);
            Overlay.Width = Target.Size.right - Target.Size.left;
            Overlay.Height = Target.Size.bottom - Target.Size.top;
            Target.Style = GetWindowLong(Target.Window, GWL_STYLE);

            if (Target.Style & WS_BORDER)
            {
                Target.Size.top += 23;
                Overlay.Height -= 23;
            }

            MoveWindow(Overlay.Window, Target.Size.left, Target.Size.top, Overlay.Width, Overlay.Height, true);
            Overlay.Margin = { 0, 0, Overlay.Width, Overlay.Height };
        }

        if (threads->isActive == true && threads->typeGame == 0 && blockpost->module.SteamСlient == 0 ||
                threads->isActive == true && threads->typeGame == 1 && blockpost->module.SteamСlient != 0)
        {
//            if (threads->typeGame == 0 && blockpost->module.SteamСlient != 0)return;
//            if (threads->typeGame == 1 && blockpost->module.SteamСlient == 0)return;

//            qDebug() << "Target.Name:" << Target.Name;
//            qDebug() << "Target.Size.top:" << Target.Size.top;
//            qDebug() << "Target.Style:" << Target.Style;
//            qDebug() << "Target.Window:" << Target.Window;
//            qDebug() << "Target.Checked:" << Target.Checked << endl;

//            qDebug() << "Overlay.Name:" << Overlay.Name;
//            qDebug() << "Overlay.Window:" << Overlay.Window;
//            qDebug() << "Overlay.Message:" << Overlay.Message;
//            qDebug() << "Overlay.Margin.cyTopHeight:" << Overlay.Margin.cyTopHeight << endl;


            if (Target.Window != nullptr && ToolsHack::GetAppstat(nullptr, "BLOCKPOST") == 1)
            {

            if (blockpost->aimBot.target != -1 && blockpost->entity[blockpost->aimBot.target].team != 2 && blockpost->entity[blockpost->aimBot.target].death != 5 && GetAsyncKeyState(VK_RBUTTON) && 1)blockpost->aimBot.isActive = false;
            else blockpost->aimBot.isActive = true;


            if (blockpost->aimBot.isActive == true)
            {
                blockpost->aimBot.minDiffAng = 1000000;
                for (int i = 0; i < 40; i++)
                {
                    blockpost->aimBot.target = -1;
                    blockpost->entity[i].isReady = false;
                }
            }

            DWORD ptrPlayerVectorHead = ToolsHack::FindDMAAddy(blockpost->pHandle, blockpost->baseAddress.MatrixBegin, { 0x0, 0x8, 0x3B4 });
            ReadProcessMemory(blockpost->pHandle, (LPCVOID)(ptrPlayerVectorHead), &blockpost->player.vectorHead, 12, nullptr);

            //AimBot
            DWORD ptrPlayerAngle = ToolsHack::FindDMAAddy(blockpost->pHandle, blockpost->baseAddress.Controll, { 0x5C, 0x6C });
            ReadProcessMemory(blockpost->pHandle, (LPCVOID)(ptrPlayerAngle), &blockpost->player.angle, 8, nullptr);


            DWORD entityDist = 0x10;
            for (int i = 0; i < 40; i++)
            {
                if (blockpost->server.gamemode != 2 && blockpost->server.gamemode != 5 && blockpost->server.gamemode != 8)
                {
                    if(blockpost->player.team == blockpost->entity[i].team)
                    {
                        entityDist += 0x4;
                        continue;
                    }
                }
                else if (blockpost->server.gamemode == 5)
                {
                    if(blockpost->player.teamZombie == blockpost->entity[i].teamZombie)
                    {
                        entityDist += 0x4;
                        continue;
                    }
                }


                if (blockpost->entity[i].team == 2)
                {
                    entityDist += 0x4;
                    continue;
                }

                if (blockpost->entity[i].death == 5)
                {
                    entityDist += 0x4;
                    continue;
                }

                if (blockpost->entity[i].isLocalPlayer != NULL)
                {
                    entityDist += 0x4;
                    continue;
                }

                DWORD ptrEntityVectorHeadT = ToolsHack::FindDMAAddy(blockpost->pHandle, blockpost->baseAddress.PLH, { 0x5C, 0xC, entityDist, 0x104, 0x8, 0x34, 0x60 });
                ReadProcessMemory(blockpost->pHandle, (LPCVOID)(ptrEntityVectorHeadT), &blockpost->entity[i].vectorHeadT, 12, nullptr);

                DWORD ptrEntityVectorBodyT = ToolsHack::FindDMAAddy(blockpost->pHandle, blockpost->baseAddress.PLH, { 0x5C, 0xC, entityDist, 0x100, 0x8, 0x34, 0x60 });
                ReadProcessMemory(blockpost->pHandle, (LPCVOID)(ptrEntityVectorBodyT), &blockpost->entity[i].vectorBodyT, 12, nullptr);

                DWORD ptrEntityVectorLArm = ToolsHack::FindDMAAddy(blockpost->pHandle, blockpost->baseAddress.PLH, { 0x5C, 0xC, entityDist, 0x108, 0x10, 0x8, 0x34, 0x60 });
                ReadProcessMemory(blockpost->pHandle, (LPCVOID)(ptrEntityVectorLArm), &blockpost->entity[i].vectorLArm[0], 12, nullptr);


                DWORD ptrEntityVectorLArm2 = ToolsHack::FindDMAAddy(blockpost->pHandle, blockpost->baseAddress.PLH, { 0x5C, 0xC, entityDist, 0x108, 0x14, 0x8, 0x34, 0x60 });
                ReadProcessMemory(blockpost->pHandle, (LPCVOID)(ptrEntityVectorLArm2), &blockpost->entity[i].vectorLArm[1], 12, nullptr);


                DWORD ptrEntityVectorRArm = ToolsHack::FindDMAAddy(blockpost->pHandle, blockpost->baseAddress.PLH, { 0x5C, 0xC, entityDist, 0x10C, 0x10, 0x8, 0x34, 0x60 });
                ReadProcessMemory(blockpost->pHandle, (LPCVOID)(ptrEntityVectorRArm), &blockpost->entity[i].vectorRArm[0], 12, nullptr);


                DWORD ptrEntityVectorRArm2 = ToolsHack::FindDMAAddy(blockpost->pHandle, blockpost->baseAddress.PLH, { 0x5C, 0xC, entityDist, 0x10C, 0x14, 0x8, 0x34, 0x60 });
                ReadProcessMemory(blockpost->pHandle, (LPCVOID)(ptrEntityVectorRArm2), &blockpost->entity[i].vectorRArm[1], 12, nullptr);


                DWORD ptrEntityVectorLLeg= ToolsHack::FindDMAAddy(blockpost->pHandle, blockpost->baseAddress.PLH, { 0x5C, 0xC, entityDist, 0x110, 0x10, 0x8, 0x34, 0x60 });
                ReadProcessMemory(blockpost->pHandle, (LPCVOID)(ptrEntityVectorLLeg), &blockpost->entity[i].vectorLLeg[0], 12, nullptr);


                DWORD ptrEntityVectorLLeg2 = ToolsHack::FindDMAAddy(blockpost->pHandle, blockpost->baseAddress.PLH, { 0x5C, 0xC, entityDist, 0x110, 0x14, 0x8, 0x34, 0x60 });
                ReadProcessMemory(blockpost->pHandle, (LPCVOID)(ptrEntityVectorLLeg2), &blockpost->entity[i].vectorLLeg[1], 12, nullptr);


                DWORD ptrEntityVectorLLeg3 = ToolsHack::FindDMAAddy(blockpost->pHandle, blockpost->baseAddress.PLH, { 0x5C, 0xC, entityDist, 0x110, 0x18, 0x8, 0x34, 0x60 });
                ReadProcessMemory(blockpost->pHandle, (LPCVOID)(ptrEntityVectorLLeg3), &blockpost->entity[i].vectorLLeg[2], 12, nullptr);


                DWORD ptrEntityVectorRLeg = ToolsHack::FindDMAAddy(blockpost->pHandle, blockpost->baseAddress.PLH, { 0x5C, 0xC, entityDist, 0x114, 0x10, 0x8, 0x34, 0x60 });
                ReadProcessMemory(blockpost->pHandle, (LPCVOID)(ptrEntityVectorRLeg), &blockpost->entity[i].vectorRLeg[0], 12, nullptr);


                DWORD ptrEntityVectorRLeg2 = ToolsHack::FindDMAAddy(blockpost->pHandle, blockpost->baseAddress.PLH, { 0x5C, 0xC, entityDist, 0x114, 0x14, 0x8, 0x34, 0x60 });
                ReadProcessMemory(blockpost->pHandle, (LPCVOID)(ptrEntityVectorRLeg2), &blockpost->entity[i].vectorRLeg[1], 12, nullptr);


                DWORD ptrEntityVectorRLeg3 = ToolsHack::FindDMAAddy(blockpost->pHandle, blockpost->baseAddress.PLH, { 0x5C, 0xC, entityDist, 0x114, 0x18, 0x8, 0x34, 0x60 });
                ReadProcessMemory(blockpost->pHandle, (LPCVOID)(ptrEntityVectorRLeg3), &blockpost->entity[i].vectorRLeg[2], 12, nullptr);

                //Bone
                {
                    //Head
                    blockpost->entity[i].angle[0] = MathsFunctions::CalcAngle(blockpost->entity[i].vectorHeadT, blockpost->player.vectorHead);
                    blockpost->entity[i].diffAng[0] = MathsFunctions::Distance(MathsFunctions::CalcAngle(blockpost->entity[i].vectorHeadT, blockpost->player.vectorHead), blockpost->player.angle);

                    //Body
                    blockpost->entity[i].angle[1] = MathsFunctions::CalcAngle(blockpost->entity[i].vectorBodyT, blockpost->player.vectorHead);
                    blockpost->entity[i].diffAng[1] = MathsFunctions::Distance(MathsFunctions::CalcAngle(blockpost->entity[i].vectorBodyT, blockpost->player.vectorHead), blockpost->player.angle);

                    //vectorLArm[0]
                    blockpost->entity[i].angle[2] = MathsFunctions::CalcAngle(blockpost->entity[i].vectorLArm[0], blockpost->player.vectorHead);
                    blockpost->entity[i].diffAng[2] = MathsFunctions::Distance(MathsFunctions::CalcAngle(blockpost->entity[i].vectorLArm[0], blockpost->player.vectorHead), blockpost->player.angle);

                    //vectorLArm[1]
                    blockpost->entity[i].angle[3] = MathsFunctions::CalcAngle(blockpost->entity[i].vectorLArm[1], blockpost->player.vectorHead);
                    blockpost->entity[i].diffAng[3] = MathsFunctions::Distance(MathsFunctions::CalcAngle(blockpost->entity[i].vectorLArm[1], blockpost->player.vectorHead), blockpost->player.angle);

                    //vectorRArm[0]
                    blockpost->entity[i].angle[4] = MathsFunctions::CalcAngle(blockpost->entity[i].vectorRArm[0], blockpost->player.vectorHead);
                    blockpost->entity[i].diffAng[4] = MathsFunctions::Distance(MathsFunctions::CalcAngle(blockpost->entity[i].vectorRArm[0], blockpost->player.vectorHead), blockpost->player.angle);

                    //vectorRArm[1]
                    blockpost->entity[i].angle[5] = MathsFunctions::CalcAngle(blockpost->entity[i].vectorRArm[1], blockpost->player.vectorHead);
                    blockpost->entity[i].diffAng[5] = MathsFunctions::Distance(MathsFunctions::CalcAngle(blockpost->entity[i].vectorRArm[0], blockpost->player.vectorHead), blockpost->player.angle);

                    //vectorLLeg[0]
                    blockpost->entity[i].angle[6] = MathsFunctions::CalcAngle(blockpost->entity[i].vectorLLeg[0], blockpost->player.vectorHead);
                    blockpost->entity[i].diffAng[6] = MathsFunctions::Distance(MathsFunctions::CalcAngle(blockpost->entity[i].vectorLLeg[0], blockpost->player.vectorHead), blockpost->player.angle);

                    //vectorLLeg[1]
                    blockpost->entity[i].angle[7] = MathsFunctions::CalcAngle(blockpost->entity[i].vectorLLeg[1], blockpost->player.vectorHead);
                    blockpost->entity[i].diffAng[7] = MathsFunctions::Distance(MathsFunctions::CalcAngle(blockpost->entity[i].vectorLLeg[1], blockpost->player.vectorHead), blockpost->player.angle);

                    //vectorLLeg[2]
                    blockpost->entity[i].angle[8] = MathsFunctions::CalcAngle(blockpost->entity[i].vectorLLeg[2], blockpost->player.vectorHead);
                    blockpost->entity[i].diffAng[8] = MathsFunctions::Distance(MathsFunctions::CalcAngle(blockpost->entity[i].vectorLLeg[2], blockpost->player.vectorHead), blockpost->player.angle);

                    //vectorRLeg[0]
                    blockpost->entity[i].angle[9] = MathsFunctions::CalcAngle(blockpost->entity[i].vectorRLeg[0], blockpost->player.vectorHead);
                    blockpost->entity[i].diffAng[9] = MathsFunctions::Distance(MathsFunctions::CalcAngle(blockpost->entity[i].vectorRLeg[0], blockpost->player.vectorHead), blockpost->player.angle);

                    //vectorRLeg[1]
                    blockpost->entity[i].angle[10] = MathsFunctions::CalcAngle(blockpost->entity[i].vectorRLeg[1], blockpost->player.vectorHead);
                    blockpost->entity[i].diffAng[10] = MathsFunctions::Distance(MathsFunctions::CalcAngle(blockpost->entity[i].vectorRLeg[1], blockpost->player.vectorHead), blockpost->player.angle);

                    //vectorRLeg[2]
                    blockpost->entity[i].angle[11] = MathsFunctions::CalcAngle(blockpost->entity[i].vectorRLeg[2], blockpost->player.vectorHead);
                    blockpost->entity[i].diffAng[11] = MathsFunctions::Distance(MathsFunctions::CalcAngle(blockpost->entity[i].vectorRLeg[2], blockpost->player.vectorHead), blockpost->player.angle);
                }


                if (threads->section[threads->typeGame].aimSetting.bone == 0)
                {
                    for (int n = 0; n < 12; n++)
                    {
                        if (blockpost->entity[i].diffAng[n] < blockpost->aimBot.minDiffAng)
                        {
                            blockpost->aimBot.fov[n] = blockpost->entity[i].diffAng[n];
                            blockpost->aimBot.target = i;
                            blockpost->aimBot.minDiffAng = blockpost->entity[i].diffAng[n];
                            blockpost->aimBot.boneId = n;
                            blockpost->entity[i].isReady = true;
                        }
                    }
                }

                if (threads->section[threads->typeGame].aimSetting.bone == 1)
                {
                    if (blockpost->entity[i].diffAng[0] < blockpost->aimBot.minDiffAng)
                    {
                        blockpost->aimBot.fov[0] = blockpost->entity[i].diffAng[0];
                        blockpost->aimBot.target = i;
                        blockpost->aimBot.minDiffAng = blockpost->entity[i].diffAng[0];
                        blockpost->aimBot.boneId = 0;
                        blockpost->entity[i].isReady = true;
                    }
                }

                if (threads->section[threads->typeGame].aimSetting.bone == 2)
                {
                    if (blockpost->entity[i].diffAng[1] < blockpost->aimBot.minDiffAng)
                    {
                        blockpost->aimBot.fov[1] = blockpost->entity[i].diffAng[1];
                        blockpost->aimBot.target = i;
                        blockpost->aimBot.minDiffAng = blockpost->entity[i].diffAng[1];
                        blockpost->aimBot.boneId = 1;
                        blockpost->entity[i].isReady = true;
                    }
                }

                if (threads->section[threads->typeGame].aimSetting.bone == 3)
                {
                    for (int n = 0; n < 2; n++)
                    {
                        if (blockpost->entity[i].diffAng[n] < blockpost->aimBot.minDiffAng)
                        {
                            blockpost->aimBot.fov[n] = blockpost->entity[i].diffAng[n];
                            blockpost->aimBot.target = i;
                            blockpost->aimBot.minDiffAng = blockpost->entity[i].diffAng[n];
                            blockpost->aimBot.boneId = n;
                            blockpost->entity[i].isReady = true;
                        }
                    }
                }

//                DWORD ptrburst = ToolsHack::FindDMAAddy(blockpost->pHandle, blockpost->baseAddress.Controll, { 0x5C, 0xC0 });

//                blockpost->rageShovel.distance = MathsFunctions::Distance(blockpost->player.vectorHead, blockpost->entity[i].vector);
//                if (blockpost->rageShovel.distance <= 100)
//                {
//                    blockpost->player.angle += MathsFunctions::Clamp(MathsFunctions::Norm(MathsFunctions::AimbotSmooth(blockpost->entity[i].angle[0], blockpost->player.angle)))
//                            / ((threads->section[threads->typeGame].aimSetting.smoothness / 3) + 1.0f);

////                    Drawing::Line(Overlay.Width / 2, Overlay.Height, blockpost->entity[i].screenHead.x, blockpost->entity[i].screenHead.y, Color::Blue);

//                    WriteProcessMemory(blockpost->pHandle, (LPCVOID*)(ptrPlayerAngle), &blockpost->player.angle, 8, nullptr);

//                    blockpost->player.burst = 1;
//                    WriteProcessMemory(blockpost->pHandle, (LPCVOID*)(ptrburst), &blockpost->player.burst, 4, nullptr);
//                }
//                else
//                {
//                    blockpost->player.burst = 0;
//                    WriteProcessMemory(blockpost->pHandle, (LPCVOID*)(ptrburst), &blockpost->player.burst, 4, nullptr);
//                }

        //            blockpost->entity[i].vector.y -= 2;
        //            vectorHead.y += 0.5f;


                entityDist += 0x4;
            }

            //AimBot
//            DWORD ptrPlayerAngle = ToolsHack::FindDMAAddy(blockpost->pHandle, blockpost->baseAddress.Controll, { 0x5C, 0x6C });
//            ReadProcessMemory(blockpost->pHandle, (LPCVOID)(ptrPlayerAngle), &blockpost->player.angle, 8, nullptr);
            if (threads->section[threads->typeGame].aimSetting.isActive == true)
            {
                if (blockpost->aimBot.isActive == false)
                {
                    if (blockpost->aimBot.fov[blockpost->aimBot.boneId] < threads->section[threads->typeGame].aimSetting.radius || blockpost->aimBot.fov[blockpost->aimBot.boneId] < -threads->section[threads->typeGame].aimSetting.radius)
                    {
                        if (blockpost->server.gamemode != 2 && blockpost->server.gamemode != 5 && blockpost->server.gamemode != 8)
                        {
                            if(blockpost->player.team == blockpost->entity[blockpost->aimBot.target].team)
                            {
                                entityDist += 0x4;
                                continue;
                            }
                        }
                        else if (blockpost->server.gamemode == 5)
                        {
                            if(blockpost->player.teamZombie == blockpost->entity[blockpost->aimBot.target].teamZombie)
                            {
                                entityDist += 0x4;
                                continue;
                            }
                        }

                        blockpost->player.angle += MathsFunctions::Clamp(MathsFunctions::Norm(MathsFunctions::AimbotSmooth(blockpost->entity[blockpost->aimBot.target].angle[blockpost->aimBot.boneId], blockpost->player.angle)))
                                / ((threads->section[threads->typeGame].aimSetting.smoothness / 3) + 1.0f);

                        WriteProcessMemory(blockpost->pHandle, (LPCVOID*)(ptrPlayerAngle), &blockpost->player.angle, 8, nullptr);
                    }
                }
            }

            }
        }


        ThreadMem::msleep(1);
    }

}

void ThreadMem::run()
{
    ThreadMem::Update();
}
