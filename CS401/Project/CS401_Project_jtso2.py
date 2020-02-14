projdata1 = open("Projdata1.txt","r")
contents = projdata1.readlines()

votes = []
region = []

for row in contents:
    rowline = row.split(" ")
    votes.append(rowline[0])
    region.append(rowline[1])

for row in new_content:
    rowline = row.split(" ")
    votes.append(rowline[0])
    region.append(rowline[1])
    
votes_int = []
    
for row in votes:
    votes_int.append(int(row))

memoization = {} #the dictionary that we will use to store already saved values
smallest_subset_size = 0
min_subsets = 0


def num_of_subsets(data, desired_total):
    
    num_subsets = recursive_call(data, desired_total, len(data)-1, memoization, smallest_subset_size)
    if (num_subsets == 0):
        print("Not Feasible")
    else:
        print("Found subsets.")
        print("Number of subsets that sum to total", desired_total, " is ", num_subsets)
        print("Smallest subset size is", smallest_subset_size)
        print("Num of distinct smallest subsets is", min_subsets)


def recursive_call(data, desired_total, i, memoization, smallest_subset):
    
    #we store to reduce runtime by not needing recursion 
    key = str(desired_total) + "-" + str(i)
    
    if (key in memoization):
        return memoization[key]
    
    #the actual recursion
    if (desired_total == 0): #the empty set is technically a total of 0  
        global min_subsets
        min_subsets= min_subsets + 1
        calculate_smallest_subset(smallest_subset_size, smallest_subset)  
        return 1 
    
    elif (desired_total < 0): #can't possibly have negatives in votes 
        return 0 
    
    elif (i < 0): #we've reached the end of the data list
        return 0 
    
    elif (desired_total < data[i]): #we move on to the next one since data[i] is larger than our desired_total
        to_memoize = recursive_call(data, desired_total, i-1, memoization, smallest_subset)
        
    else: #it is possibly in either tree branch, so we look at both of them                                                      
        to_memoize = (recursive_call(data, desired_total, i-1, memoization,smallest_subset)
                     + 
                      recursive_call(data, desired_total - data[i], i-1, memoization,smallest_subset+1))
        
    memoization[key] = to_memoize
    return to_memoize

def calculate_smallest_subset(curr_size, smallest_subset):
    global smallest_subset_size     
    
    if (smallest_subset <= 0):
        return
    
    elif ((curr_size != 0) & (curr_size < smallest_subset)):   
        return
    
    else:      
        smallest_subset_size = smallest_subset
    


num_of_subsets(votes_int, 9)