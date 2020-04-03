#ifndef THREADMEM_H
#define THREADMEM_H

#include "blockpost.h"
#include "toolshack.h"
#include "mem.h"
#include "threads.h"

#include <QThread>

class ThreadMem : public QThread
{
public:
    explicit ThreadMem(Blockpost* _blockpost, Threads *_threads);

    void Update();

    void run();
};

#endif // THREADMEM_H
