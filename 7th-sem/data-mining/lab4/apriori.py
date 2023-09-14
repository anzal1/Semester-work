
# import pandas
import pandas as pd;
# import numpy
import numpy as np;
# import combinations from itertools
from itertools import combinations;


# read the data from data.txt
df = pd.read_csv("data-mining/lab4/data.txt")

# print the data
print(df)
print("\n")

# create a list of candidates
candidates = []
# create a list of frequent itemsets
frequent = []


# create a list of unique items from the data
items=pd.unique(df.values.ravel('K'))
# remove the NaN values from the list
items=items[~pd.isna(items)]

# ask the user for the minimum support
min_support=int(input("Enter minimum support: "))
print("\n")

# for each itemset
for iterno in range(1,len(items)):
    # create a dictionary of counts
    count={}
    # create a list of intermediate itemsets
    intermediate=[]

    # if it is the first itemset
    if iterno == 1:
        # add all items to the candidates list
        candidates.append(items)
        # for each item in the candidates list
        for transaction in candidates[iterno-1]:
            # count the number of times the item appears in the data
            ctr=0
            # for each row in the data
            for value in df.values:
                # if the item is in the row
                if transaction in value:
                    # increment the counter
                    ctr+=1
            # add the item and the count to the dictionary
            count[transaction]=ctr
    # if it is not the first itemset
    else:
        # create a list of combinations of items from the frequent itemsets
        candidates.append(list(combinations(np.unique(np.array(frequent[iterno-2]).ravel('K')),iterno)))
        # for each itemset in the candidates list
        for transaction in candidates[iterno-1]:
            # count the number of times the itemset appears in the data
            ctr=0
            # for each row in the data
            for value in df.values:
                # if all of the items in the itemset are in the row
                if all(i in value for i in transaction):
                    # increment the counter
                    ctr+=1
            # add the itemset and the count to the dictionary
            count[transaction]=ctr

    # for each itemset in the dictionary
    for k in count.keys():
        # if the count is greater than or equal to the minimum support
        print(intermediate)
        print("Itemset: ",k," Count: ",count[k])
        if count[k]>=min_support:
            # add the itemset to the intermediate list
            intermediate.append(k)
            
    # if the intermediate list is empty
    if intermediate == []:
        # pretty print the frequent itemsets
        print("Frequent itemsets are: ")
        for item in frequent:
            print(item)
        # break out of the for loop
        break

    # add the intermediate list to the frequent itemsets
    frequent.append(intermediate)

