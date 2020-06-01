#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>		
#include<linux/cdev.h>		
#include<linux/semaphore.h>	
#include<linux/uaccess.h>	
#define DEVICE_NAME	"encdev"

MODULE_LICENSE("GPL");

char data[100];
struct cdev *devstruct;
int major ,ret;			
dev_t dev_num;		


int device_open(struct inode *inode, struct file *filp){
	return 0;
}	

ssize_t device_read(struct file *filp, char *bufStoreData, size_t bufCount, loff_t *curOffset){
	ret = copy_to_user(bufStoreData, data, bufCount );
	return ret;
}

ssize_t device_write(struct file *filp, const char *bufSourceData, size_t bufCount, loff_t *curOffset){
	ret = copy_from_user(data, bufSourceData, bufCount);
	int i=0;
	while(data[i]!=NULL){
		data[i] = data[i]+1 ;
		i++;
	}
	return ret;
}

int device_close(struct inode *inode, struct file *filp){
	return 0;
}

struct file_operations fops = { 
	.open = device_open,
	.read = device_read,
	.write = device_write,
	.release = device_close        
 };

static int driver_entry(void){
	ret = alloc_chrdev_region(&dev_num,1,1,DEVICE_NAME);
	major = MAJOR(dev_num);
	printk(KERN_INFO "%s : mknod /dev/%s c %d 1\n", DEVICE_NAME, DEVICE_NAME, major);
	devstruct= cdev_alloc();
	devstruct->ops = &fops;	
	ret = cdev_add(devstruct, dev_num, 1);
	printk(KERN_ALERT "%s: Done adding cdev",DEVICE_NAME);
	return 0;
}

static void driver_exit(void){
	cdev_del(devstruct);
	unregister_chrdev_region(dev_num, 1);
	printk(KERN_ALERT "Unloading\n");
}

module_init(driver_entry);
module_exit(driver_exit);