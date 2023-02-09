# dbms_hw3

## Instructions:
To run and clone the repo:

```bash
#If you're setup for ssh then do the this:
git clone https://github.com/goodwjak/dbms_hw3.git

#Otherwise this will work.
git clone git@github.com:goodwjak/dbms_hw3.git

cd ./dbms_hw3

make run
```

That should be all that's required to build and run the program.
The only other issues that are super likely is if you don't have the std
C and C++ libraries availible on your machine.

The program does require access to the "rm" console command as well. So fair
warning to make sure you don't have anything else in the repo with the name in
the format "run_\*" as it will YEET that right off your filesystem! :)



## Description:
A bunch of small peices of software to handle storage for DBMS(CS440).

The directory layout:
- Docs: holds pdfs, instructions and documents relating to development.
- src: holds source code 
- build: holds the debugging and binary output from linking/compiling.
- data: Holds example data.
- scripts: Holds any bash/csh/sh scripts used to automate stuff.



## TODO:

1. Test and debug 2-pass merge sort.    DONE
2. Test it using OSU servers.           DONE
3. Clean the code so it's not so nasty. DONE
4. Work on the other code issues.       DONE
