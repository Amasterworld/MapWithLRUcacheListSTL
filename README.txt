This project was made for a company, 
Project: Efficient Key-Value-Store

Short Description:

Create an efficient, performance optimized key-value-store by making use of modern C++. With this application, 
users should be able to add/update values by key, retrieve values by key and delete values by key


	● Keys are strings, values are strings as well. Both have variable length
	● A “PUT” call which adds a pair to the store
	● A “DELETE” call which deletes a pair from the store by key
	● A “GET” call which retrieves a pair from the store by key
	
Installation :
	● open sln if you are using MSVS
	
	
Data structure:
	
	 build in Linked list + hashtable 
 

Contributing:
	
	● The method GET and PUT, each run in O(1) average complexity

Roadmap:
	
	● For my self: implement LRUcache + TTL (Time To live)  (done)
	● tested with the third party unordered_map (e.g., ska:: unordered_map)
	● Change it to be a template
	
	
