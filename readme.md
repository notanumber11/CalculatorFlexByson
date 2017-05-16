# Calculator with flex and byson

Console calculator using C , flex and byson. 

### How to compile
``` bash
cmake ..
make
./exec
```
### How to obtain byson and flex files:
``` bash
bison -d byson.y  
flex lexer.flex
```
### How to use
After execute the program you can use the following commands:
``` console
help: Show some examples and syntax 
show: Show the symbol table
load nameOfFile: Load a file
exit: Exit of the program
``` 

Allowed functions: sin, cos, tan , log exp
Constants: pi; E;

Examples <br>
3+2; <br> 5-2;<br> 3e-2+3;<br> 53*3; <br> cos(37);  <br> 3+pi;


