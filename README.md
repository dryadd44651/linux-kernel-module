# linux-kernel-module
```
# check kernel log
tail -f /var/log/kern.log
```

## File Device Driver Module
*Demo HelloWorld chardev*

```
cd chardev
make
sudo insmod chardev.ko

# list kernel
lsmod
# remove kernel
sudo rmmod chardev
```
```
# create the device file with major number 60
sudo mknod /dev/example c 60 0
chmod 777 example
echo  "132"  >  example
cat example
# 132

```
## Net Link Module
*NetLink*
```
cd NetLink
make
sudo insmod greetNetlinkLKM.ko
gcc -g userspace.c -o  userspace -lpthread
./userspace
```

