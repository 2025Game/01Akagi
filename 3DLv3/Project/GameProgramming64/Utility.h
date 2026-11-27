#ifndef UTILITY_H  
#define UTILITY_H
#include <random>
#include "CVector.h"
namespace Utility
{
    //整数型のランダムな値を返す
    inline int random(int min, int max)
    {
        // staticを付けることで、プログラム全体で一度だけ初期化される
        static std::random_device seed_gen;     //シードの生成器
        static std::mt19937 engine(seed_gen()); //乱数生成エンジン

        //エンジンの出力を範囲(min, max)に収める
        std::uniform_int_distribution<int> dist(min, max);

        //フィルター(dist)にエンジン(engine)を連動させて乱数を発生させる
        int value = dist(engine);

        return value;
    }

    //float型のランダムな値を返す
    inline float random(float min, float max)
    {
        static std::random_device seed_gen;
        static std::mt19937 engine(seed_gen());

        std::uniform_real_distribution<float> dist(min, max);

         float value = dist(engine);

        return value;
    }

    //線形補間
    inline float lerp(const float& start, const float& end, const float t)
    {
        return start + t * (end - start);
    }

    //線形補間(ベクトル)
    inline CVector lerp(const CVector& start, const CVector& end, const float t)
    {
        return CVector(
            lerp(start.X(), end.X(), t),
            lerp(start.Y(), end.Y(), t),
            lerp(start.Z(), end.Z(), t)
        );
    }
}

#endif // !RANDOM_H

