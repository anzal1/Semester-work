# given n objects find and rank similar between them
import pandas as pd 

df=pd.read_csv('data-mining/lab2/animal.txt')
print(df)

# find similarity between objects  and print 10 most similar objects without using any library
# 1. find similarity between objects
# 2. rank them
# 3. print 10 most similar objects


def square_rooted(x):
    return round(sum([a*a for a in x])**0.5,3)
  
def cosine_similarity(x,y):
    #convert nan to 0
    x = [0 if i!=i else i for i in x]
    y = [0 if i!=i else i for i in y]
    numerator = sum(a*b for a,b in zip(x,y))
    denominator = square_rooted(x)*square_rooted(y)
    return round(numerator/float(denominator),3)

def euclidean_distance(x,y):
    #convert nan to 0
    x = [0 if i!=i else i for i in x]
    y = [0 if i!=i else i for i in y]
    return round(sum([abs(a-b)**2 for a,b in zip(x,y)])**0.5,3)

similarity = []
for i in range(len(df)):
    for j in range(len(df)):
        if i != j:
            cs_score = cosine_similarity(df.iloc[i,1:].values, df.iloc[j,1:].values)  
            eu_score=euclidean_distance(df.iloc[i,1:].values, df.iloc[j,1:].values)
            similarity.append([df['animal'][i], df['animal'][j],eu_score,cs_score])

#sort and print 10 most similar objects
similarity.sort(key=lambda x: x[3], reverse=True)
print('\n')
#print in tabular form
print(pd.DataFrame(similarity[:10], columns=['D1', 'D2', 'EU_DIS','CS_DIS']))




