# Autonomous Forklift Logic in C

## Project Structure
```
C
├── build
├── src
|   ├── begin-with-the-crazy-ideas.textile
|   └── on-simplicity-in-technology.markdown
├── _includes
|   ├── footer.html
|   └── header.html
├── _layouts
|   ├── default.html
|   └── post.html
├── _posts
|   ├── 2007-10-29-why-every-programmer-should-play-nethack.textile
|   └── 2009-04-26-barcamp-boston-4-roundup.textile
├── _data
|   └── members.yml
├── _site
└── index.html
```
## Unit Testing

### Framework
Chosen framework for unit testing is [Unity](http://www.throwtheswitch.org/unity)

### Build Method
We are building using Make. The [Makefile](./Makefile) will make building customizable and easy. See [link](http://www.throwtheswitch.org/build/make) for details on the Makefile 

### Test Runner
We have two options for the test runner: 
	- Native Tests : http://www.throwtheswitch.org/build/native
	- Simulator : http://www.throwtheswitch.org/build/cross
## Resources
Reason for testing choices : http://www.throwtheswitch.org/decide-o-tron

