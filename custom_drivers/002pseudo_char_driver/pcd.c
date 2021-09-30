#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/kdev_t.h>

#undef pr_fmt
#define pr_fmt(fmt) "%s :" fmt,__func__

#define DEV_MEM_SIZE	512

/* pseudo device's memory */
char device_buffer[DEV_MEM_SIZE];

/* This holds the device number */
dev_t device_number;

/* cdev variable */
struct cdev pcd_cdev;


loff_t pcd_lseek(struct file *filp, loff_t off, int whence)
{
	pr_info("lseek requested \n");
	return 0;
}
ssize_t pcd_read(struct file *filp, char __user *buff, size_t count, loff_t *f_pos)
{
	pr_info("read requested for %zu bytes \n", count);
	return 0;
}
ssize_t pcd_write(struct file *filp, const char __user *buff, size_t count, loff_t *f_pos)
{
	pr_info("write requested for %zu bytes \n", count);
	return 0;
}
int pcd_open(struct inode *inode, struct file *filp)
{
	pr_info("open was successful\n");
	return 0;
}
int pcd_release(struct inode *inode, struct file *filp)
{
	pr_info("close was successful\n");
	return 0;
}

/* file operations of the driver */
struct file_operations pcd_fops =
{
	.open = pcd_open,
	.write = pcd_write,
	.read = pcd_read,
	.llseek = pcd_lseek,
	.release = pcd_release,
	.owner = THIS_MODULE
};

struct class *class_pcd;
struct device *device_pcd;

static int __init pcd_driver_init(void) 
{
	/*1. Dynamically allocate a device number */
	alloc_chrdev_region(&device_number, 0, 1, "pcd_devices");	  

	pr_info("Device number <major>:<minor> = %d:%d\n", MAJOR(device_number), MINOR(device_number));

	/*2. Initialize the cdev structure with fops */
	cdev_init(&pcd_cdev, &pcd_fops);

	/*3. Register the device (cdev structure) with VFS */
	pcd_cdev.owner = THIS_MODULE; 
	cdev_add(&pcd_cdev, device_number, 1);

	/*4. Create device class under /sys/class/ */
	class_pcd = class_create(THIS_MODULE, "pcd_class");

	/*5. Populate the sysfs with device information */
	device_pcd = device_create(class_pcd, NULL, device_number, NULL, "pcd");

	pr_info("Module init was successful\n");

	return 0;
}

static void __exit pcd_driver_cleanup(void)
{
	device_destroy(class_pcd, device_number);	
	class_destroy(class_pcd);
	cdev_del(&pcd_cdev);
	unregister_chrdev_region(device_number, 1);
	pr_info("module unloaded\n");
}

module_init(pcd_driver_init);
module_exit(pcd_driver_cleanup);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("NEERAJ");
MODULE_DESCRIPTION("A pseudo character driver");
