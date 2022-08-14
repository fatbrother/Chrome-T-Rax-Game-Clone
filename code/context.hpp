#include <bits/stdc++.h>

class Context
{
public:
    Context();
    template <typename T>
    T getRandom(T, T);
    void FPStest(float);

private:
    std::default_random_engine generator;
};

Context::Context()
{
    std::random_device rd;
    generator = std::default_random_engine(rd());
}

template <typename T>
T Context::getRandom(T from, T to)
{
    std::uniform_real_distribution<float> unif(from, to);
    float res = unif(generator);

    return (T)res;
}

void Context::FPStest(float time)
{
    static float pastTime = 0;
    static int cnt = 0;
    static std::mutex mutex;

    pastTime += time, cnt++;
    if (pastTime >= 1.f)
    {
        mutex.lock();
        int tmp = cnt;
        std::cout << tmp << std::endl;
        pastTime -= 1.f;
        cnt -= tmp;
        mutex.unlock();
    }
}

static Context context;