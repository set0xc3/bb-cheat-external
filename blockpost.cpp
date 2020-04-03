#include "blockpost.h"

Blockpost::Blockpost()
{

}



bool Blockpost::WorldToScreen(D3DXVECTOR3 vector, D3DXVECTOR3 &screen, float viewMatrix[16], const RECT m_Rect)
{
    //Matrix-vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
        D3DXVECTOR4 clipCoords;
        clipCoords.x = vector.x * viewMatrix[0] + vector.y * viewMatrix[4] + vector.z * viewMatrix[8] + viewMatrix[12];
        clipCoords.y = vector.x * viewMatrix[1] + vector.y * viewMatrix[5] + vector.z * viewMatrix[9] + viewMatrix[13];
        clipCoords.z = vector.x * viewMatrix[2] + vector.y * viewMatrix[6] + vector.z * viewMatrix[10] + viewMatrix[14];
        clipCoords.w = vector.x * viewMatrix[3] + vector.y * viewMatrix[7] + vector.z * viewMatrix[11] + viewMatrix[15];



        //perspective division, dividing by clip.W = Normalized Device Coordinates
        D3DXVECTOR3 NDC;
        NDC.x = clipCoords.x / clipCoords.w;
        NDC.y = clipCoords.y / clipCoords.w;
        NDC.z = clipCoords.z / clipCoords.w;

        int width = static_cast<int>(m_Rect.right - m_Rect.left);
        int height = static_cast<int>(m_Rect.bottom - m_Rect.top);

        screen.x = (width / 2 * NDC.x) + (NDC.x + width / 2);
        screen.y = -(height / 2 * NDC.y) + (NDC.y + height / 2);

        if (clipCoords.w < 0.1f)
            return false;

        return true;
}

D3DXVECTOR3 Blockpost::WorldToScreen(D3DXVECTOR3 vector, float viewMatrix[16], const RECT m_Rect)
{
    D3DXVECTOR4 clipCoords;
    clipCoords.x = vector.x * viewMatrix[0] + vector.y * viewMatrix[4] + vector.z * viewMatrix[8] + viewMatrix[12];
    clipCoords.y = vector.x * viewMatrix[1] + vector.y * viewMatrix[5] + vector.z * viewMatrix[9] + viewMatrix[13];
    clipCoords.z = vector.x * viewMatrix[2] + vector.y * viewMatrix[6] + vector.z * viewMatrix[10] + viewMatrix[14];
    clipCoords.w = vector.x * viewMatrix[3] + vector.y * viewMatrix[7] + vector.z * viewMatrix[11] + viewMatrix[15];

//    if (clipCoords.w < 0.1f)
//        return D3DXVECTOR3(0,0,0);

    //perspective division, dividing by clip.W = Normalized Device Coordinates
    D3DXVECTOR3 NDC;
    NDC.x = clipCoords.x / clipCoords.w;
    NDC.y = clipCoords.y / clipCoords.w;
    NDC.z = clipCoords.z / clipCoords.w;

    int width = static_cast<int>(m_Rect.right - m_Rect.left);
    int height = static_cast<int>(m_Rect.bottom - m_Rect.top);

    D3DXVECTOR3 screen;
    screen.x = (width / 2 * NDC.x) + (NDC.x + width / 2);
    screen.y = -(height / 2 * NDC.y) + (NDC.y + height / 2);

    return screen;
}


