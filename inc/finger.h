#ifndef FINGER_H
#define FINGER_H

#include <rtthread.h>

#include "ipc/ringbuffer.h"
#include "ipc/completion.h"
#include "ipc/dataqueue.h"
#include "ipc/workqueue.h"
#include "ipc/waitqueue.h"
#include "ipc/pipe.h"
#include "ipc/poll.h"
#include "ipc/ringblk_buf.h"


struct rt_finger_device {
	struct rt_device          parent;
	const uint8_t *						message;
	const struct rt_uart_ops *ops;
	
};



#endif

