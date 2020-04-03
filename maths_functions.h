#ifndef MATHS_FUNCTIONS_H
#define MATHS_FUNCTIONS_H

#include "threads.h"

namespace MathsFunctions
{
    D3DXVECTOR3 Normalize(D3DXVECTOR3 src);
    D3DXVECTOR3 Divide(D3DXVECTOR3 src, float num);
    D3DXVECTOR3 MultiplyVec(D3DXVECTOR3 src, D3DXVECTOR3 dest);
    D3DXVECTOR3 NormalizeVec(D3DXVECTOR3 vec);
    D3DXVECTOR3 Clamp(D3DXVECTOR3 angle);
    D3DXVECTOR3 Norm(D3DXVECTOR3 angle);
    D3DXVECTOR3 Subtract(D3DXVECTOR3 src, D3DXVECTOR3 dst);
    D3DXVECTOR3 CalcAngle(D3DXVECTOR3 src, D3DXVECTOR3 dst);
    D3DXVECTOR3 AimbotSmooth(D3DXVECTOR3 src, D3DXVECTOR3 dst);
    float DotProduct(D3DXVECTOR3 src, D3DXVECTOR3 dst);
    float Magnitude(D3DXVECTOR3 vec);
    float Distance(D3DXVECTOR3 src, D3DXVECTOR3 dst);
};

#endif // MATHS_FUNCTIONS_H
