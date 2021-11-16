#include <linux/module.h> 
#include <linux/init.h>   
#include <linux/err.h>   
#include <linux/fs.h>   
#include <linux/device.h>   
#include <asm/uaccess.h>	//copy to user / copy from user

#define	DEMO_MAJOR	60
#define DEV_NAME	"char_dev"
#define BUF_SIZE	1024
static struct class *demo_class ;

static ssize_t demo_read(struct file *file, char __user *user_buf, size_t count, loff_t *ppos)
{	
	ssize_t status ;
	unsigned char data[BUF_SIZE] = {"ABCDEFGHIJKLMN"};
	printk("Now entering %s() \n", __FUNCTION__ );
	status = raw_copy_to_user(user_buf,data,count);
	printk("user read data is %s\n",user_buf );
	return status ;
}

static ssize_t demo_write(struct file *file, const char __user *user_buf, size_t count, loff_t *ppos)
{
	ssize_t	status ;
	unsigned char data[BUF_SIZE];
	printk("Now entering %s() \n", __FUNCTION__ );
	status = raw_copy_from_user( data,user_buf,count);
	printk("user write data is %s\n",data);
	return  status ;
}

static int demo_open(struct inode *inode, struct file *file)
{
	printk("Now entering %s() \n", __FUNCTION__ );
	return 0 ;
}

static int demo_close(struct inode *inode, struct file *file)
{
	printk("Now entering %s() \n", __FUNCTION__ );
	return 0 ;
}

struct file_operations demo_ops = {
	.owner = THIS_MODULE ,
	.open = demo_open ,
	.release = demo_close ,
	.write = demo_write ,
	.read = demo_read ,
};

static int __init hello_init(void){
	int status ;
	printk("Hello driver world\n");
	status = register_chrdev( DEMO_MAJOR , DEV_NAME , &demo_ops);
	if ( status < 0 ){
		printk("Failed to register char device - %d\n" , DEMO_MAJOR );
		return status ;
	}

	demo_class = class_create(THIS_MODULE , "demo-class");
	if (IS_ERR(demo_class)){
		unregister_chrdev( DEMO_MAJOR , DEV_NAME );
	}

	device_create(demo_class ,NULL , MKDEV(DEMO_MAJOR , 0), NULL ,  "hubuyu" );
	return 0;
}
	 
static void __exit hello_exit(void){
	printk("Goodbye driver world\n");
	device_destroy(demo_class , MKDEV(DEMO_MAJOR ,0));
    class_destroy(demo_class);
    unregister_chrdev(DEMO_MAJOR , DEV_NAME);

}

module_init(hello_init);
module_exit(hello_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("howard");
MODULE_DESCRIPTION("Simple char with write/read");
