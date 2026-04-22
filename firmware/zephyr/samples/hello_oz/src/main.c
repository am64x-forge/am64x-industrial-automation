#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

int main(void)
{
    printk("hello_oz: sample Zephyr application is running.\n");
    return 0;
}
