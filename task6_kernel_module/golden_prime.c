#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/gcd.h>
#include <linux/hash.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Golden Ratio Prime Module");
MODULE_AUTHOR("Student");

static int __init golden_prime_init(void) {
    printk(KERN_INFO "Loading Kernel Module\n");
    printk(KERN_INFO "GOLDEN_RATIO_PRIME = %lu\n", GOLDEN_RATIO_PRIME);
    return 0;
}

static void __exit golden_prime_exit(void) {
    unsigned long result = gcd(3700, 24);
    printk(KERN_INFO "Removing Kernel Module\n");
    printk(KERN_INFO "GCD(3700, 24) = %lu\n", result);
}

module_init(golden_prime_init);
module_exit(golden_prime_exit);
