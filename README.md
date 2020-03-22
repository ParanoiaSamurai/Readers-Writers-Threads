# Readers-Writers-Threads
Readers-writer threads using POSIX Thread or pthread
What is reader-writer problems?
Consider a scenario where one person is editing a file and other one is reading at the same time, it causes problem to both of the user. OS calls this problem as reader writer problem.
Solutions are two- Either Reader has the high priority over Writer or Vice Versa
This program will Explain the Reader Writer Problem where reader has the high priority than writer and they will read a common shared variable 
What is the value that the reader read before writing and what is the written value after reading.


Same can be done using monitors and semaphore.

To run this, install gcc using command
apt-get install gcc (For Ubuntu) 

to run the file 
gcc Reader_Writer_thread.c -pthread -o <Object_file_name>

Execute it using
./<Object_file_name>

Done!

