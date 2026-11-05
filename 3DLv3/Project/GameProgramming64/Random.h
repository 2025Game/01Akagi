#ifndef RANDOM_H
#define RANDOM_H
#include <random>
namespace Random 
{
    //整数型のランダムな値を返す
    inline int get(int min, int max)
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
    inline float get(float min, float max)
    {
        static std::random_device seed_gen;
        static std::mt19937 engine(seed_gen());

        std::uniform_real_distribution<float> dist(min, max);

         float value = dist(engine);

        return value;
    }
}

#endif // !RANDOM_H

