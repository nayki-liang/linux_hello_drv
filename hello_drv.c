#include <linux/uaccess.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/mutex.h>
#include <linux/atomic.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/gpio.h>
#include <linux/miscdevice.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/time.h>
#include <linux/of_gpio.h>
#include <linux/kobject.h>
#include <linux/kthread.h>
#include <linux/types.h>
#include <linux/err.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/of_device.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include <linux/stat.h>




#define DEV_NAME    "hello_device"

struct plat_hello_drv  
{
    dev_t dev;
    int major;
    int minor;
    struct class *class;
    struct device *device;  
    struct device_node *nd;
    struct cdev     drv_cdev;

};

struct plat_hello_drv  hello_drv;


  uint8_t receive_buff[1024];

int hello_drv_open (struct inode *node, struct file *file)
{
    printk("hello driver open success \n");  

    return 0;
}

ssize_t hello_drv_write (struct file *file, const char __user *buff, size_t size, loff_t *offset)
{
    uint8_t len;
    len = copy_from_user(receive_buff,buff,size);
   
    return 0;
}

ssize_t hello_drv_read (struct file *file, char __user *buff, size_t size , loff_t *offset)
{
    uint8_t len ;
    len = copy_to_user(buff,receive_buff,strlen(receive_buff));
    return 0;
}


static struct file_operations hello_opera = 
{
    .open = hello_drv_open,
    .write =hello_drv_write ,
    .read = hello_drv_read,
    .owner = THIS_MODULE,

};



static int __init hello_drv_init(void)
{
   //创建设备号
   if(alloc_chrdev_region(&hello_drv.dev,0,1,DEV_NAME))
   {
        printk("alloc chrdev fail \n");
   } 
   //获取主设备号
   hello_drv.major = MAJOR(hello_drv.dev);
    //初始化 cdev ;
    cdev_init(&hello_drv.drv_cdev,&hello_opera);
    if(cdev_add(&hello_drv.drv_cdev,hello_drv.major,1))
    {
        printk("cdev add fail \n");
    }
    //创建设备类
    hello_drv.class = class_create(THIS_MODULE,DEV_NAME);
    if(hello_drv.class == NULL)
    {
        printk("class create fail \n");

    }
    //创建设备节点
    //获取次设备号
    hello_drv.minor = MINOR(hello_drv.dev);
    hello_drv.device = device_create(hello_drv.class,NULL,MKDEV(hello_drv.major,hello_drv.minor),NULL,DEV_NAME);
    if(hello_drv.device == NULL)
    {
        printk("device create fail \n");
    }

    

    return 0;
}

static void __exit hello_drv_exit(void)
{
    cdev_del(&hello_drv.drv_cdev);
    class_destroy(hello_drv.class);
    device_destroy(hello_drv.class,hello_drv.dev);
}


module_init(hello_drv_init);
module_exit(hello_drv_exit);

MODULE_LICENSE("GPL");


