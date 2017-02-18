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
**rshell** will return an error when:
* There is no command before/after a connector
* Only a comment is passed in
* Only && or || is passed in

**rshell** currently do not have the ability to handle incorrect inputs and prompt the user to enter a correct input. 

When running **rshell** with the bash scripts that tests the program, the script input does **NOT** show up when u run the script
