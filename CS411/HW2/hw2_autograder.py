#################### DO NOT CHANGE THIS FILE ####################
import homework2 as hw2
import numpy as np
import optparse,sys


##### P1

def gradeP1():
    score = 4
    result = hw2.sudokuCSPToGrid(hw2.sudokuCSP([(0,0,4),(0,1,3),(1,0,1),(1,2,3),(2,2,2),(3,0,2),(3,1,1)],2),2)
    result = np.reshape(result,16)
    answer = [4, 3, 1, 2, 1, 2, 3, 4, 3, 4, 2, 1, 2, 1, 4, 3]
    for i in range(16):
        if result[i] != answer[i]:
            score = 0            

    if score == 0:
        print "Your Answer:\n" + str(np.reshape(result,(4,4)))
        print "Correct Answer:\n" + str(np.reshape(answer,(4,4)))

    print "#######################################"
    print "P1 SCORE: " + str(score) + " / 4 "
    print "#######################################"

    return score
    
##### P2

def gradeP2():
    score = 3
    result = hw2.annealTSP(['New York City', 'Los Angeles', 'Chicago', 'Houston'])
    print "\n"
    if result[1] > 93.0:
        score = 0            

    if score == 0:
        print "Your Distance: " + str(result[1])
        print "Correct Distance: 92.5725570752" 

    print "#######################################"
    print "P2 SCORE: " + str(score) + " / 3 "
    print "#######################################"

    return score

##### P3

def gradeP3():
    correct_runs = 10
    for i in range(10):
        bad_run = False
        result = np.reshape(hw2.annealSudoku([(0,0,4),(0,1,3),(1,0,1),(1,2,3),(2,2,2),(3,0,2),(3,1,1)],2)[0],16)
        print "\n"
        answer = [4, 3, 1, 2, 1, 2, 3, 4, 3, 4, 2, 1, 2, 1, 4, 3]
        for i in range(16):
            if result[i] != answer[i]:
                correct_runs = correct_runs - 1
                bad_run = True
        if bad_run:    
            print "Your Answer:\n" + str(np.reshape(result,(4,4)))
            print "Correct Answer:\n" + str(np.reshape(answer,(4,4)))

    if correct_runs > 8:
        score = 4
    elif correct_runs > 6:
        score = 3
    elif correct_runs > 3:
        score = 2
    elif correct_runs > 0:
        score = 1        
    else:
        score = 0

    print "#######################################"
    print "P3 SCORE: " + str(score) + " / 4 "
    print "Based on: " + str(correct_runs) + " / 10 correct runs"
    print "#######################################"

    return score

##### P4

def gradeP4():
    score = 4

    result = hw2.fractionalKnapsack(5)
    if abs(result - 4.4) > 0.01:
        score = score - 1
        print "Your Answer:    " + str(result)
        print "Correct Answer: 4.4"

    result = hw2.fractionalKnapsack(7)
    if abs(result - 5.2) > 0.01:
        score = score - 1
        print "Your Answer:    " + str(result)
        print "Correct Answer: 5.2"

    result = hw2.fractionalKnapsack(10)
    if abs(result - 6.0) > 0.01:
        score = score - 1
        print "Your Answer:    " + str(result)
        print "Correct Answer: 6.0"

    result = hw2.fractionalKnapsack(2)
    if abs(result - 2.0) > 0.01:
        score = score - 1
        print "Your Answer:    " + str(result)
        print "Correct Answer: 2.0"

    print "#######################################"
    print "P4 SCORE: " + str(score) + " / 4 "
    print "#######################################"

    return score

##### P5

def gradeP5():
    score = 4
    result = hw2.sudokuIPToGrid(hw2.sudokuIP([(0,0,4),(0,1,3),(1,0,1),(1,2,3),(2,2,2),(3,0,2),(3,1,1)],2),2)
    result = np.reshape(result,16)
    answer = [4, 3, 1, 2, 1, 2, 3, 4, 3, 4, 2, 1, 2, 1, 4, 3]
    for i in range(16):
        if result[i] != answer[i]:
            score = 0            

    if score == 0:
        print "Your Answer:\n" + str(np.reshape(result,(4,4)))
        print "Correct Answer:\n" + str(np.reshape(answer,(4,4)))

    print "#######################################"
    print "P5 SCORE: " + str(score) + " / 4 "
    print "#######################################"

    return score

##### P6
def gradeP6():
    score = 6

    result = hw2.calculateMMSValue(2,5,((1,2,3,4,5),(10,9,8,7,6)),0)
    if result and abs(result - 7.0) > 0.01:
        score = score - 1
        print "MMSValue Test Case 1:"
        print "Your Answer:    " + str(result)
        print "Correct Answer: 7.0"

    result = hw2.calculateMMSValue(2,5,((1,2,3,4,5),(10,9,8,7,6)),1)
    if result and abs(result - 19.0) > 0.01:
        score = score - 1
        print "MMSValue Test Case 1:"
        print "Your Answer:    " + str(result)
        print "Correct Answer: 19.0"

    result = hw2.calculateMMSValue(2,5,((10,9,8,7,6),(1,2,3,4,5)),0)
    if result and abs(result - 19.0) > 0.01:
        score = score - 1
        print "MMSValue Test Case 1:"
        print "Your Answer:    " + str(result)
        print "Correct Answer: 19.0"

    if not result:
        print "MMS Value: Result was None"
        score = score - 3

    result = hw2.calculateMMSAllocation(2,5,((1,2,3,4,5),(10,9,8,7,6)),(7,19))
    if result is not None:
        val1 = 1*result[0][0] +  2*result[0][1] +  3*result[0][2] +  4*result[0][3] +  5*result[0][4]
        val2 = 10*result[1][0] +  9*result[1][1] +  8*result[1][2] +  7*result[1][3] +  6*result[1][4]
        if val1 < 6.99 or val2 < 18.99:
            score = score - 3
            print "MMS Allocation:"
            print "Note that small deviations from 1 or 0 due to numerics are note the issue"
            print "Your Answer:\n" + str(np.reshape(result,(2,5)))
            print "Player 1 should get at least 7 and got: " + str(val1)
            print "Player 2 should get at least 19 and got: " + str(val2) 
    else:
        print "MMS Allocation: Result was None (no feasible solution?)"
        score = score - 3

    print "#######################################"
    print "P6 SCORE: " + str(score) + " / 6 "
    print "#######################################"

    return score

def gradeAll():
    total_points = 0
    total_points = total_points + gradeP1()
    total_points = total_points + gradeP2()
    total_points = total_points + gradeP3()
    total_points = total_points + gradeP4()
    total_points = total_points + gradeP5()
    total_points = total_points + gradeP6()
    print "#######################################"
    print "TOTAL SCORE: " + str(total_points) + " / 25 "
    print "#######################################"

# register arguments and set default values
def readCommand(argv):
    parser = optparse.OptionParser(description = 'Run public tests on student code')
    parser.add_option('--question', '-q',
                    dest = 'gradeQuestion',
                    default = None,
                    type = 'int',
                    help = 'Grade one particular question.')
    (options, args) = parser.parse_args(argv)
    return options

if __name__ == '__main__':
    options = readCommand(sys.argv)
    if options.gradeQuestion == 1:
        gradeP1()
    elif options.gradeQuestion == 2:
        gradeP2()
    elif options.gradeQuestion == 3:
        gradeP3()
    elif options.gradeQuestion == 4:
        gradeP4()
    elif options.gradeQuestion == 5:
        gradeP5()
    elif options.gradeQuestion == 6:
        gradeP6()
    else:
        gradeAll()