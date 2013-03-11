#include "application.h"

int main(int argc, char *argv[])
{
    RocketBar::AppLock lock;
    return RocketBar::Application(argc, argv).run();
}
