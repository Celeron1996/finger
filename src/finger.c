/*
 * finger.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-16     zhusl        first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <finger.h>

#define DBG_TAG    "UART"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>


/*
 * finger poll routines
 */
rt_inline int _finger_poll_rx(struct rt_finger_device *finger, rt_uint8_t *data, int length)
{
    return 0;
}

rt_inline int _finger_poll_tx(struct rt_finger_device *finger, const rt_uint8_t *data, int length)
{
    return 0;
}

/*
 * finger interrupt routines
 */
rt_inline int _finger_int_rx(struct rt_finger_device *finger, rt_uint8_t *data, int length)
{
    return 0;
}

rt_inline int _finger_int_tx(struct rt_finger_device *finger, const rt_uint8_t *data, int length)
{
    return 0;
}

static void _finger_check_buffer_size(void)
{

}	


/* RT-Thread Device Interface */
/*
 * This function initializes finger device.
 */
static rt_err_t rt_finger_init(struct rt_device *dev)
{
    return 0;
}

static rt_err_t rt_finger_open(struct rt_device *dev, rt_uint16_t oflag)
{
    return 0;
}

static rt_err_t rt_finger_close(struct rt_device *dev)
{
    return 0;
}

static rt_size_t rt_finger_read(struct rt_device *dev,
                                rt_off_t          pos,
                                void             *buffer,
                                rt_size_t         size)
{
    struct rt_finger_device *finger;

    RT_ASSERT(dev != RT_NULL);
    if (size == 0) return 0;

    finger = (struct rt_finger_device *)dev;

    if (dev->open_flag & RT_DEVICE_FLAG_INT_RX)
    {
        return _finger_int_rx(finger, (rt_uint8_t *)buffer, size);
    }

    return _finger_poll_rx(finger, (rt_uint8_t *)buffer, size);
}

static rt_size_t rt_finger_write(struct rt_device *dev,
                                 rt_off_t          pos,
                                 const void       *buffer,
                                 rt_size_t         size)
{
    struct rt_finger_device *finger;

    RT_ASSERT(dev != RT_NULL);
    if (size == 0) return 0;

    finger = (struct rt_finger_device *)dev;

    if (dev->open_flag & RT_DEVICE_FLAG_INT_TX)
    {
        return _finger_int_tx(finger, (const rt_uint8_t *)buffer, size);
    }

    else
    {
        return _finger_poll_tx(finger, (const rt_uint8_t *)buffer, size);
    }
}


static rt_err_t rt_finger_control(struct rt_device *dev,
                                  int              cmd,
                                  void             *args)
{
    return 0;
}


/*
 * finger register
 */
rt_err_t rt_hw_finger_register(struct rt_finger_device *finger,
                               const char              *name,
                               rt_uint32_t              flag,
                               void                    *data)
{
    rt_err_t ret;
    struct rt_device *device;
    RT_ASSERT(finger != RT_NULL);

    device = &(finger->parent);

    device->type        = RT_Device_Class_Char;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;

    device->init        = rt_finger_init;
    device->open        = rt_finger_open;
    device->close       = rt_finger_close;
    device->read        = rt_finger_read;
    device->write       = rt_finger_write;
    device->control     = rt_finger_control;

    device->user_data   = data;

    /* register a character device */
    ret = rt_device_register(device, name, flag);

    return ret;
}

/* ISR for finger interrupt */
void rt_hw_finger_isr(struct rt_finger_device *finger, int event)
{

}

