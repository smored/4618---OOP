#include "CAsteroidGame.h"

using namespace std;

int main(int argc, char* argv[])
{
    CAsteroidGame astro(cv::Size(1000,500));
    astro.run();
}
