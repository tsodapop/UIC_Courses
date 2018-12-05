

This folder contains numerous tester programs and problem instances
for testing the program-5 correctness.

Conventions:

    - files with a .g extension are graph files.
    - files with a .o extension are vertex ordering files.
    - files with a .ref extension are 'reference output files'

The naming of the .ref files are indicative of the features tested.

-----------------------------------------------------------------------------

To get started running individual tests:

    - copy your Graph.h file into a folder with all of these files.
    - run make
    - examine one or more of the .ref files.  You will see that it includes
        exactly how the test case should be run.  Try it!  Does the output
        match what the .ref file says?


-----------------------------------------------------------------------------

To run ALL tests in a batch:


1.  Copy Graph.h into this directory.

2.  run script 'run_tests'

        ./run_tests

3.  Files produced:

        FULL-REPORT.txt      :  hopefully you will not have to look at this

        PARTIAL-SCORES.txt   :  this is extracted from the full report.  It
                                gives the auto-graded results.  Maximum of 130
                                points.

        TIMED-RESULTS.txt     : this contains extracted timed results.  There 
                                are 4 tests requiring manual inspection.  For
                                each test make sure it says "FUNCTIONAL TEST: PASSED" 
                                If it functionally passed, check the reported
                                time (which should be above).  If
                                implementation is correct, this will probably
                                read 0.00 sec.  Since we are just distinguishing
                                between poly-time and exponential time, this
                                should be pretty obvious.

                                We have put a 0.1 sec threshold as a max
                                allowable time which should be plenty.

                                Each of these tests is worth 5 points.  Tally
                                them up and add to the partial scores.


4. Now you should have a score out of 150 points.  If the submission at least
   shows some effort (i.e., they actually attempted the assignment even
   if they didn't get it to work completely), they receive 50 points for 
   "honest effort".

   Thus, the entire assignment is scored out of 200 points.

--------------------------------------------

General structure of the tests:

   The run_tests script launches the batch script which actually runs
   the tests and generates output files; it generates the log file 
   FULL-REPORT.txt.  After the log file is generated, the two summary
   files PARTIAL-SCORES.txt and TIMED-RESULTS.txt

   A program is run to exercise one of the features they implemented.  The
   output is filtered so we get just the interesting stuff -- this goes to
   a file named xxx.out.  The .out file is diffed with a reference file
   for the test (.ref extension).  

   We have tried to make sure that there is ALWAYS a unique correct solution.
   For example, graphs which we run critical-paths on have a unique 
   critical path.  The reports also only dispay the relevant vertex labels
   for that test (e.g., the state field is usually not displayed).

   For the enum-paths operation, the paths are sorted before comparison (since
   different ordering of the same set of paths should still be considered 
   correct).


