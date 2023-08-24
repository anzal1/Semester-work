#given five documents remove stock words and add freq of words in each document

import pandas as pd
import numpy as np
import re

def read_file(file):
    with open(file) as f:
        return f.read()
    
def remove_stopwords(text):
    stopwords = read_file('data-mining/similarobject/stopWords.txt').split('\n')
    return ' '.join([word for word in text.split() if word not in stopwords])

def remove_punctuation(text):
    return re.sub(r'[^\w\s]','',text)

def remove_numbers(text):
    return re.sub(r'\d+','',text)


def clean_text(text):
    text = text.lower()
    text = remove_stopwords(text)
    text = remove_punctuation(text)
    text = remove_numbers(text)
    return text

def unique_words(documents):
    unique = set()
    for doc in documents:
        for word in doc.split():
            unique.add(word)
    return list(unique)


text=read_file('data-mining/similarobject/documents.txt')
documents =text.split('\n')
documents = [clean_text(doc) for doc in documents]


dict_words = unique_words(documents)
#find frequency of unqiue words in each document and build an attribute table using pandas


def get_freq(text):
    freq = {}
    for word in dict_words:
        freq[word] = text.split().count(word)
    return freq

df = pd.DataFrame()
for i,doc in enumerate(documents):
    df['D'+str(i+1)] = pd.Series(get_freq(doc))
df = df.fillna(0)

    

print(df)


#find similarity between documents using cosine similarity and euclidean distance
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
for i in range(len(df.columns)):
    for j in range(len(df.columns)):
        if i != j:
            cs_score = cosine_similarity(df.iloc[:,i].values, df.iloc[:,j].values)  
            eu_score=euclidean_distance(df.iloc[:,i].values, df.iloc[:,j].values)
            similarity.append([df.columns[i], df.columns[j],eu_score,cs_score])

#sort and print 10 most similar objects
similarity.sort(key=lambda x: x[3], reverse=True)
print('\n')
#print in tabular form
print(pd.DataFrame(similarity[:10], columns=['Da', 'Db', 'EU_DIS','CS_DIS']))

