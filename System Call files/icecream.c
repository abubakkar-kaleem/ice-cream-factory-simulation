#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/time.h>
#include <linux/timer.h>
#include <linux/semaphore.h>
#include <linux/delay.h>

#define MAX_ORDERS 15
#define numOfOrders 4

static struct semaphore waitingLine;
static struct semaphore orderCounter;
static struct semaphore boiler, sugar, flavor, cone, freezing, wrapping;
static struct semaphore custWait;

int allDone = 0; // Indicates if all orders are processed.
int currentOrderRunning;
int Numbers[MAX_ORDERS];
int const orderDetails[numOfOrders] = {3, 1, 2, 4};

static struct task_struct *childThreads[MAX_ORDERS];
static struct task_struct *tid[MAX_ORDERS];

int customer(void *id);
int startManufacture(void *);
int manufacture(void *id);

asmlinkage long sys_icecream(void) {
    int i;

    if (numOfOrders > MAX_ORDERS) {
        printk(KERN_INFO "The number of orders exceeds the MAX capacity. Exiting...\n");
        return 0;
    }

    printk(KERN_INFO "\t---DATA\n");
    printk(KERN_INFO "numOfOrders: %d\n", numOfOrders);
    for (i = 0; i < numOfOrders; i++) printk(KERN_INFO "%d \n", orderDetails[i]);
    printk(KERN_INFO "-----------\n");

    printk(KERN_INFO "\t\t---Solution for Ice cream factory---\n");

    // Numbering each order
    for (i = 0; i < MAX_ORDERS; ++i) {
        Numbers[i] = i + 1;
    }

    // Initialize semaphores
    sema_init(&waitingLine, numOfOrders); // Waiting line initialized with numOfOrders
    sema_init(&orderCounter, 1); // One ordering machine
    sema_init(&boiler, 3); // 3 boilers
    sema_init(&sugar, 2); // 2 sugar machines
    sema_init(&flavor, 2); // 2 flavor machines
    sema_init(&cone, 2); // 2 cone machines
    sema_init(&freezing, 3); // 3 freezing machines
    sema_init(&wrapping, 2); // 2 wrapping machines
    sema_init(&custWait, 0); // Customer wait semaphore initialized

    // Create threads for orders
    for (i = 0; i < numOfOrders; ++i) {
        tid[i] = kthread_create(customer, (void*)&Numbers[i], "thread1");
        if (tid[i]) {
            wake_up_process(tid[i]);
        }
    }

    msleep(3000);
    allDone = 1;
    printk(KERN_INFO "Program ended\n");
    return 0;
}

int customer(void *id) {
    int num = *(int *)id;
    printk(KERN_INFO "Order number %d received.\n", num);
    msleep(10);

    down(&waitingLine);
    printk(KERN_INFO "Order number %d is in the waiting area.\n", num);

    down(&orderCounter);
    up(&waitingLine);
    printk(KERN_INFO "Order number %d has entered the counter.\n", num);
    currentOrderRunning = num;

    startManufacture(NULL);

    printk(KERN_INFO "Order #%d processed. Leaving.\n", num);
    up(&orderCounter);
    do_exit(0);
    return 0;
}

int startManufacture(void *nothing) {
    int tempNumbers[orderDetails[currentOrderRunning - 1]];
    int i;

    for (i = 0; i < orderDetails[currentOrderRunning - 1]; ++i) {
        tempNumbers[i] = i + 1;
    }

    for (i = 0; i < orderDetails[currentOrderRunning - 1]; ++i) {
        childThreads[i] = kthread_create(manufacture, (void*)&tempNumbers[i], "thread");
        if (childThreads[i]) {
            wake_up_process(childThreads[i]);
        }
    }
    msleep(500);
    return 0;
}

int manufacture(void *id) {
    int num = *(int *)id;

    down(&boiler);
    printk(KERN_INFO "Order #%d, Ice cream #%d is in boiling stage.\n", currentOrderRunning, num);
    msleep(15);
    up(&boiler);

    down(&sugar);
    printk(KERN_INFO "Order #%d, Ice cream #%d is in sugar stage.\n", currentOrderRunning, num);
    msleep(10);
    up(&sugar);

    down(&flavor);
    printk(KERN_INFO "Order #%d, Ice cream #%d is in flavor stage.\n", currentOrderRunning, num);
    msleep(10);
    up(&flavor);

    down(&cone);
    printk(KERN_INFO "Order #%d, Ice cream #%d is in coning stage.\n", currentOrderRunning, num);
    msleep(10);
    up(&cone);

    down(&freezing);
    printk(KERN_INFO "Order #%d, Ice cream #%d is in freezing stage.\n", currentOrderRunning, num);
    msleep(15);
    up(&freezing);

    down(&wrapping);
    printk(KERN_INFO "Order #%d, Ice cream #%d is in wrapping stage.\n", currentOrderRunning, num);
    msleep(10);
    up(&wrapping);

    printk(KERN_INFO "Order #%d, Ice cream #%d finished/made.\n", currentOrderRunning, num);
    do_exit(0);
    return 0;
}
