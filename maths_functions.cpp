#include "maths_functions.h"
#define M_PI 3.141f

D3DXVECTOR3 MathsFunctions::Subtract(D3DXVECTOR3 src, D3DXVECTOR3 dst)
{
    D3DXVECTOR3 diff;
    diff.x = src.x - dst.x;
    diff.y = src.y - dst.y;
    diff.z = src.z - dst.z;
    return diff;
}

float MathsFunctions::Magnitude(D3DXVECTOR3 vec)
{
    return sqrtf(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
}

float MathsFunctions::Distance(D3DXVECTOR3 src, D3DXVECTOR3 dst)
{
    D3DXVECTOR3 diff = MathsFunctions::Subtract(src, dst);
    diff = MathsFunctions::Clamp(MathsFunctions::Norm(diff));
    return MathsFunctions::Magnitude(diff);
}

D3DXVECTOR3 MathsFunctions::CalcAngle(D3DXVECTOR3 src, D3DXVECTOR3 dst)
{
    D3DXVECTOR3 delta = MathsFunctions::Subtract(src, dst);
    D3DXVECTOR3 angle;

    angle.x = atan2f(delta.x, delta.z) * (180.0f / M_PI);//Pith
    angle.y = -asin(delta.y / MathsFunctions::Magnitude(delta)) * (180.0f / M_PI);//Yaw
    angle.z = 0.0f;

    return angle;
}

D3DXVECTOR3 MathsFunctions::Clamp(D3DXVECTOR3 angle)
{
    if (angle.x > 90.0f && angle.x <= 180.0f)
    angle.x = 90.0f;

    if (angle.x > 180.0f)
    angle.x = angle.x - 360.0f;

    if (angle.x < -90.0f)
    angle.x = -90.0f;

    if (angle.y > 180.0f)
    angle.y = angle.y - 360.0f;

    if (angle.y < -180.0f)
    angle.y = angle.y + 360.0f;

    return angle;
}

D3DXVECTOR3 MathsFunctions::Norm(D3DXVECTOR3 angle)
{
    if (angle.x > 180)
    angle.x -= 360.0f;

    if (angle.x < 180)
    angle.x += 360.0f;

    if (angle.y > 180)
    angle.y -= 360.0f;

    if (angle.y < 180)
    angle.y += 360.0f;

    return angle;
}

float MathsFunctions::DotProduct(D3DXVECTOR3 src, D3DXVECTOR3 dst)
{
    return src.x * dst.x + src.y * dst.y + src.z * dst.z;
}

D3DXVECTOR3 MathsFunctions::NormalizeVec(D3DXVECTOR3 vec)
{
    float Length = Magnitude(vec);

    vec.x /= Length;
    vec.y /= Length;
    vec.z /= Length;

    return vec;
}

D3DXVECTOR3 MathsFunctions::MultiplyVec(D3DXVECTOR3 src, D3DXVECTOR3 dest)
{
    src.x *= dest.x;
    src.y *= dest.y;
    src.z *= dest.z;

    return src;
}

D3DXVECTOR3 MathsFunctions::Divide(D3DXVECTOR3 src, float num)
{
    D3DXVECTOR3 vec;
    vec.x = src.x / num;
    vec.y = src.y / num;
    vec.z = src.z / num;

    return vec;
}

D3DXVECTOR3 MathsFunctions::Normalize(D3DXVECTOR3 src)
{
    D3DXVECTOR3 vec = MathsFunctions::Divide(src, MathsFunctions::Magnitude(src));
    return vec;
}



D3DXVECTOR3 MathsFunctions::AimbotSmooth(D3DXVECTOR3 src, D3DXVECTOR3 dst)
{
    D3DXVECTOR3 diff;
    diff[0] = src[0] - dst[0];
    diff[1] = src[1] - dst[1];
    diff[2] = 0;

    return diff;
}
