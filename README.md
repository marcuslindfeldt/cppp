A News System 
=========
Run
----

Run "make" to compile and link, the executables client & server are stored in the "bin" folder

Client: 
    
    ./client <host> <port> 

Server:
    
    ./server <port> [memdb|filedb]
    

Usage
---------

```
news> help
Available commands:
  list                                  List all newsgroups
  list <ngid>                           List articles in newsgroup
  read <ngid> <id>                      Display article
  create <newsgroup>                    Create newsgroup
  create <ngid> <title> <author> <body> Create article
  delete <ngid>                         Delete newsgroup
  delete <ngid> <id>                    Delete article
  clear                                 Clear the screen
  quit                                  Exit the application
```

