# C Hash Tables
## _My implementation of two hashtable algorithms in C._

It includes timers to verify the increased efficiency of searching the table trough the key's hash instead of just searching linearly.

```hashtable_linked_list.c```:
- A hashtable where collisions are solved by adding a node to the linked list present in the respective index

```hashtable_linear.c```:
- A hashtable where collisions are solved by adding the key/value pair in the following available index starting from the hashed one

Both implementations allow the searching of desired keys trough a linear or hashing optimised way.


## Running it

Open the folder and run 
``gcc hashtable_linked_list.c -o hashtable_linked_list`` -> ``./hashtable_linked_list``<br>
<br>or<br>
``gcc hashtable_linear.c -o hashtable_linear`` -> ``./hashtable_linear``



## Images


![alt text](https://github.com/gugajazz/Hash_Table/blob/main/imgs/menu.png?raw=true)
<br><br>
![alt text](https://github.com/gugajazz/Hash_Table/blob/main/imgs/table.png?raw=true)
<br><br>
![alt text](https://github.com/gugajazz/Hash_Table/blob/main/imgs/search.png?raw=true)
<br><br>
![alt text](https://github.com/gugajazz/Hash_Table/blob/main/imgs/time.png?raw=true)
<br><br>
