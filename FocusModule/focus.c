   #include <linux/module.h>       /* Needed by all modules */
   #include <linux/kernel.h>       /* Needed for KERN_INFO */
   #include <linux/init.h>         /* Needed for the macros */
   #include<linux/kmod.h>
   
   MODULE_LICENSE( "GPL" );

   static int __init hello_start(void)
   {
       printk(KERN_INFO "Loading rooted module...\n");
       char* argv[] = {"/bin/bash", "-c", "/home/grim-reaper/focusmyman.sh", NULL};

       static char* envp[] = { "HOME=/",  "TERM=linux",   "PATH=/sbin:/bin:/usr/sbin:/usr/bin", NULL };
       int ret = call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);
       if (ret < 0) {
       	printk(KERN_ERR "Failed to execute script\n");
        return ret;
       }
       return 0;
   }

   static void __exit hello_end(void)
   {
       printk(KERN_INFO "exit.\n");
       char* argv[] = {"/bin/bash", "home/grim-reaper/script-remove.sh", NULL};

       static char* envp[] = { "HOME=/",  "TERM=linux",   "PATH=/sbin:/bin:/usr/sbin:/usr/bin", NULL };
       call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);

   }

   module_init(hello_start);
   module_exit(hello_end);
