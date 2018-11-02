


Name:Jonathan Tso
UIN: 662758603

-----------------------------------------------

Please confirm that you compiled your solution with test cases exercising ALL
functions using g++ -std=c++11.  Confirm this statement by typing YES below.
(If you did not do this, compilation errors may result in an overall grade of
zero!)

YES




Describe what augmentations to the bst data structures you made to complete the 
project -- i.e., what types / data members did you change and why?


I added a book keeping of the size of the number of nodes below a root. 
I also kept the size of the number of nodes that are smaller than the root.
Using this, I was able to determine if it would violate any size balancing issues recursively.

I included this check inside my insert and remove functions. I also included a special remove function so that it could remove without causing this check only for when I'm using it to fix the size balancing issue. 

I added several static functions to interact with other static functions if necessary, of current existing functions. An example is also creating two forms of the to_vector function. 




-----------------------------------------------
Which functions did you need to modify as a result of the augmentations from the previous
question?  

I modified the insert and remove functions, creating and modifying helper functions. Modifications were also made to checking functions, such as sizeBalanced, which helps check if there is a violation. Other functions were added in to accommodate with these data members in mind.


-----------------------------------------------
For each function from the previous question, how did you ensure that the (assymptotic) runtime 
remained the same?

For the insert and remove, all additional functions to correct for size balancing were done only if the size balance check would return false. This means that more often than not, it would not occur and so it would amortize to the same runtime. Additionally, the checks themselves were small. All size modifications per the new data types were updated upon the success of the function action.

-----------------------------------------------
For each of the assigned functions, tell us how far you got using the choices 0-5 and
answer the given questions.  


0:  didn't get started
1:  started, but far from working
2:  have implementation but only works for simple cases
3:  finished and I think it works most of the time but not sure the runtime req is met. 
4:  finished and I think it works most of the time and I'm sure my design leads to 
       the correct runtime (even if I still have a few bugs).
5:  finished and confident on correctness and runtime requirements


to_vector level of completion:  ______5____  


-----------------------------------------------
get_ith level of completion:  _____4_____  

    How did you ensure O(h) runtime?

    ANSWER: I was not able to ensure O(h) runtime per the runtime check test. However, I do believe that the way my function is set up is how it should be set up, where you would only need to check one directionally per each height level until you find the correct node.

-----------------------------------------------
num_geq level of completion:  _____4_____  

    How did you ensure O(h) runtime?

    ANSWER: My function runs unidirectionally based off of a comparison on the value you put in and at each node level. Because of this, it will only run a proportional number of checks to the height.

-----------------------------------------------
num_leq level of completion:  ______5_____

    How did you ensure O(h) runtime?

    ANSWER: The ideology of this function is very similar to the num_geq function, where you just need to run down the height of the tree based off of 1 comparison at each level.

-----------------------------------------------
num_range level of completion:  ______5_____

    How did you ensure O(h) runtime?

    ANSWER: I utilized the num_leq function here to get my runtime, which I have seen to be O(h) runtime.

-----------------------------------------------
Implementation of size-balanced criteria according to 
the given guidelines (including bst_sb_work):

    Level of completion: ___5______


Write a few sentences describing how you tested your solutions.  Are there
any tests that in retrospect you wish you'd done?

I created several functions that would help give me the left and right sizes of subtrees for a node. I used this over all my nodes to confirm that there would not be an imbalance. Then, I added this into my insert and remove functions and used a set of numbers I knew would cause imbalances (specifically, my first instance of an imbalance would be at the inputs 1,2,3). 

I then chose to send this into a vector and remove the corresponding nodes, reading them in shortly after. This was done recursively in case there were any issues for ancestors above. I believe these checks were sufficient in creating the size-balancing functionality, with minor modifications afterwards for small bug fixes.










