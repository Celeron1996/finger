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


/**
 * finger device
 */
struct rt_finger_device {
	struct rt_device								parent;
	enum rt_finger_status						status;
	const struct rt_finger_info *		info;
	const struct rt_finger_ops *		ops;
};


/**
 * finger operators
 */
struct rt_finger_ops
{
    rt_err_t (*control)(struct rt_finger_device *finger, int cmd, void *arg);
};


/**
 * finger info
 */
struct rt_finger_info {
	const uint8_t *			vendor;
	const uint16_t			user_total;
	const uint8_t				enroll_cnt;
};


/**
 * finger command
 */
enum rt_finger_cmd {
	FINGER_CMD_VERIFY = 0x01,
	FINGER_CMD_DELETE = 0x02,
	FINGER_CMD_ENROLL = 0x04,
	FINGER_CMD_WORK		= 0x10,
	FINGER_CMD_SLEEP	= 0x20
};


/**
 * finger arg
 */
struct rt_finger_arg {
	rt_err_t result;
	uint16_t id;
	uint16_t timeout;
};


/**
 * finger status
 */
enum rt_finger_status {
	FINGER_STATUS_STANDBY,
	FINGER_STATUS_SLEEP,
	FINGER_STATUS_BUSY,
	FINGER_STATUS_DEINIT
};


#endif

