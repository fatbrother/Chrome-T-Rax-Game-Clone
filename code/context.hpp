#include <bits/stdc++.h>

class Context
{
public:
    Context();
    template <typename T>
    T getRandom(T, T);

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

static Context context;