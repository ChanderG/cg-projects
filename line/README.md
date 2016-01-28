# 3d line segment

### What?
3d DSS enhanced with unit 1 cubes drawn around selected points.

### Running
First compile as:
```
make
```

Then run as 
```
./a.out <args>
```

Running without any args gives you a help message.

The output is a OBJ file, specifically `output.obj`. Open it in any graphics software like `meshlab`.

### Testing
Using a makeshift test framework. Run:
```
./testrunner.sh
```
to run tests. Look in the `testsuite` directory for tests and correct outputs.
