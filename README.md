## Ice Cream Factory Simulation - Operating Systems Course Project

This project simulates the manufacturing process of an ice cream factory, where multiple orders are processed concurrently using semaphores and threads in a Linux environment. The simulation represents the various stages of ice cream production, including boiling milk, adding sugar, flavoring, freezing, and wrapping.

### Key Features:
- **System Call Implementation**: A custom system call `sys_icecream` is developed to simulate the workflow in an ice cream factory.
- **Thread Synchronization**: Multiple orders (represented by threads) are handled concurrently with synchronization mechanisms such as semaphores to ensure proper order processing without conflicts.
- **Deadlock Prevention**: Semaphores are also used to manage machine resources, preventing deadlock situations during the execution of multiple orders.
- **Order Processing**: Each order goes through a series of stages (boiling, sugar, flavoring, etc.), and each stage uses a machine resource. The system ensures that only available resources are used, and machines are assigned tasks based on the longest waiting time.
- **Order Queue**: Machines are assigned tasks from a task queue in a "longest waiting time first" basis to ensure fair processing.

### Project Overview:
- The project models an ice cream factory with various machines that process orders in parallel.
- It simulates real-world factory operations by mimicking tasks that machines perform, such as boiling, freezing, and wrapping.
- The ice cream production process is depicted with various machines (boiler, sugar, flavor, cone, freezing, and wrapping), each performing specific tasks concurrently.
  
### How the Project Works:
1. **Order Placement**: Customers place orders for ice cream, each having a predefined sequence of tasks.
2. **Order Processing**: Each order goes through several stages (boiling, mixing, freezing, etc.), and multiple threads simulate these tasks.
3. **Semaphore Management**: Semaphores are used to synchronize the threads representing various machines, ensuring tasks are performed in order and preventing resource conflicts.
4. **Deadlock Prevention**: Semaphores also help prevent deadlocks by controlling the flow of orders and machine usage, making sure no machine is stuck waiting for a resource indefinitely.

### How to Run:
1. **Clone the Repository**:
   ```
   git clone https://github.com/your-username/ice-cream-factory-simulation.git
   ```
2. **Kernel Setup**:
   Follow the steps to set up the kernel and integrate the `icecream` system call into the kernel as described in the project report.

3. **Compilation**:
   Compile the kernel with the new system call added:
   ```
   sudo make
   sudo make modules_install && sudo make install
   ```
4. **Run the Test Program**:
   After installation, compile and run the test program (`testprog.c`), which triggers the `sys_icecream` system call to start the simulation.
   ```
   gcc testprog.c -o testprog
   ./testprog
   ```

5. **Viewing Output**:
   You can view the kernel logs to see the simulation progress using:
   ```
   dmesg
   ```

### Project Challenges and Solutions:
- **Deadlock Handling**: Initially, deadlocks were encountered when more threads were created than the project limit allowed. This was resolved by utilizing semaphores to control the flow of tasks and prevent multiple threads from blocking each other.
- **Synchronization**: Using semaphores ensured that each machine resource was properly synchronized, allowing tasks to be performed in a sequence while preventing race conditions.

### Screenshot 
![image alt](https://github.com/abubakkar-kaleem/ice-cream-factory-simulation/blob/6d3e351ba31b4691d1755eaaa4ee1ba9ffe4a79e/Project%20Screenshots/screenshot_1.png)

 
### Conclusion:
This project demonstrates an effective implementation of concurrent task processing in an operating system using Linux kernel programming. It simulates the production of ice cream in a factory setting, focusing on task synchronization, deadlock prevention, and resource management.
