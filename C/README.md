# Autonomous Forklift Logic in C

## Project Structure
```
C
├── build
|   ├── depends
|   ├── objs
|   └── results
├── src
└── test
```
### Structure Rules and Recommendations
Suggested we follow the following C coding Standard: https://users.ece.cmu.edu/~eno/coding/CCodingStandard.html <br>

### Naming
Since there is no namespace in C, let's use prefixes in the following format : component_task/action<br>
example: leftMotor_driveForward
## Unit Testing

### Framework
Chosen framework for unit testing is [Unity](http://www.throwtheswitch.org/unity) <br>
See [README](../unity/README.md) for details.

### Build Method
We are building using Make. The [Makefile](./makefile) will make building customizable and easy. See [link](http://www.throwtheswitch.org/build/make) for details on the Makefile 

### Test Runner
We have two options for the test runner: <br>
- Native Tests : http://www.throwtheswitch.org/build/native
- Simulator : http://www.throwtheswitch.org/build/cross
## Resources
Reason for testing choices : http://www.throwtheswitch.org/decide-o-tron

Literally EVERYTHING about C :
https://github.com/kozross/awesome-c

Using C in an Object-Oriented way:
https://www.cs.rit.edu/~ats/books/ooc.pdf



