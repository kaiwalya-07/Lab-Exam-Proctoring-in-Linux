#include <linux/module.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");

static char *my_strings[10] = {"default1", "default2", "default3"};
module_param_array(my_strings, charp, NULL, 0);
MODULE_PARM_DESC(my_strings, "An array of strings");

static int __init my_module_init(void)
{
    int i;

    printk(KERN_INFO "my_strings:\n");
    for (i = 0; i < ARRAY_SIZE(my_strings); i++) {
        printk(KERN_INFO "[%d]: %s\n", i, my_strings[i]);
    }

    return 0;
}

static void __exit my_module_exit(void)
{
    printk(KERN_INFO "Exiting my module\n");
}

module_init(my_module_init);
module_exit(my_module_exit);
