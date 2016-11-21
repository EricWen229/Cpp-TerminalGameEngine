#ifndef Thread_H
#define Thread_H

#include <thread>
#include <functional>

#define null nullptr

/* 避免缩进 */
struct AvoidIntend {};

std::thread createPthread(std::function<void *(void *)> func);
void waitPthread(std::thread &thread);

#endif
