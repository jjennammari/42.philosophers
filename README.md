_This project has been created as part of the 42 curriculum by jemustaj_

# Philosophers

## Description

Philosophers is using a metaphor of dining philosophers that has tasks to eat, sleep and think. The goal goal is to learn about concurrent programming with using threads in a safe way implementing with mutex locks.

## Instructions

To be able to compile the project in your computer, make sure you have installed `cc` and GNU Makefile<br>
<br>
 * compile from terminal commandline with:
```
make
```
* after the program is created, you can execute and test it with different inputs
```
./philo 1 800 200 200   // with one philosopher
./philo 4 300 250 200   // with no max meal nb defined
./philo 9 500 100 200 3 // with max meal nb defined
```
* after you are done using the program, you can clean the .o files with
```
clean
```
* to delete the execution file, type
```
fclean
```

## Resources

To learn more about the project and tools to use to create it, I was using several resources:
<br>
* Data races abd how to avoid
    * [https://www.geeksforgeeks.org/cpp/data-races-in-cpp/](https://www.geeksforgeeks.org/cpp/data-races-in-cpp/)
    * [https://docs.oracle.com/cd/E19205-01/820-0619/geojs/index.html](https://docs.oracle.com/cd/E19205-01/820-0619/geojs/index.html)
    * [https://www.mathworks.com/products/polyspace/static-analysis-notes/what-data-races-how-avoid-during-software-development.html](https://www.mathworks.com/products/polyspace/static-analysis-notes/what-data-races-how-avoid-during-software-development.html)
    * [https://medium.com/@efebalikofc/understanding-data-races-in-programming-a-quick-overview-1058047c0c6f](https://medium.com/@efebalikofc/understanding-data-races-in-programming-a-quick-overview-1058047c0c6f)
* Processes and fork in C
    * [https://www.geeksforgeeks.org/operating-systems/process-in-operating-system/](https://www.geeksforgeeks.org/operating-systems/process-in-operating-system/)
    * [https://www.geeksforgeeks.org/c/fork-system-call/](https://www.geeksforgeeks.org/c/fork-system-call/)
    * [https://www.youtube.com/watch?v=cex9XrZCU14&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY](https://www.youtube.com/watch?v=cex9XrZCU14&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY)
* Threads in Unix system with C
    * [https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2](https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)
    * [https://medium.com/@jalal92/the-dining-philosophers-7157cc05315](https://medium.com/@jalal92/the-dining-philosophers-7157cc05315)
    * [https://medium.com/@jalal92/lets-discuss-threads-grab-a-coffee-ad4d4ebf7181](https://medium.com/@jalal92/lets-discuss-threads-grab-a-coffee-ad4d4ebf7181)
* AI usage
    * Resources. Especially when looking for very specific details that seems slow to find information from internet.
    * Help to understand how different tools work together
    * Advice when I have no idea what is going on
