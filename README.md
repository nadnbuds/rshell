# rshell
Cs100 Assignment by Lorenzo Alamillo and Jerry Zhu

**rshell** is a command shell that is written in C++
### Usage
**rshell** performs the following steps:

1. Print a command prompt: rshell$
2. Read in a command on one line. Commands will have the form:
  * cmd = executable [ argumentList ] [ connector cmd ]
  * connectors || or && or ;
    * || = If a command is followed by ||, then the next command is executed only if the first
      one fails
    * && = If a command is followed by &&, then the next command is executed only if the first one
      succeeds
      
### Bugs
**rshell** will return an error when only a comment is passed in, it will also return an error with incorrect syntax such as:
* When there is no command before/after a connector
* 
