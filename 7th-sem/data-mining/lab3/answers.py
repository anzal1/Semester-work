# #consider domain questions and answers of a use case ,given a new question find the closest answer ,generate bow vectors for the new question and find the closest answer using cosine similarity
# #given five documents remove stock words and add freq of words in each document

import pandas as pd
import re
# Read the text file

def read_file(file):
    with open(file) as f:
        return f.read()

def remove_stopwords(text):
    stopwords = read_file('data-mining/lab3/stopWords.txt').split('\n')
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



# Print the DataFrame



# Split the content into question-answer pairs
qa_pairs = read_file("data-mining/lab3/documents.txt").split("\n\n")

# Initialize lists to store questions and answers
questions_inp = []
questions = []
answers = []

# Iterate through question-answer pairs and extract questions and answers
for qa_pair in qa_pairs:
    lines = qa_pair.split("\n")
    if len(lines) == 2:
        question = lines[0].replace("Question: ", "")
        answer = lines[1].replace("Answer: ", "")
        questions.append(clean_text(question))
        questions_inp.append(question)
        answers.append(answer)

df = pd.DataFrame({"Question": questions_inp, "Answer": answers})
# print(df)
# print("\n")


# Create a list of unique words in the corpus
unique_words = set()
for question in questions:
    for word in question.split():
        unique_words.add(word)

for answer in answers:
    for ans in clean_text(answer).split():
        unique_words.add(ans)        

# Create a dictionary of word frequencies for each question
def get_freq(text):
    freq = {}
    for word in unique_words:
        freq[word] = text.split().count(word)
    return freq

df = pd.DataFrame()
for i,ques in enumerate(questions):
    df['Q'+str(i+1)] = pd.Series(get_freq(ques))
df = df.fillna(0)



# take a new question and find the closest answer
new_question = input("Enter a question: ")
new_question = clean_text(new_question)
new_question_freq = get_freq(new_question)


def square_rooted(x):
    return round(sum([a*a for a in x])**0.5,3)
  
def cosine_similarity(x,y):
    #convert nan to 0
    x = [0 if i!=i else i for i in x]
    y = [0 if i!=i else i for i in y]
    numerator = sum(a*b for a,b in zip(x,y))
    denominator = square_rooted(x)*square_rooted(y)
    return round(numerator/float(denominator),3)
# Find the cosine similarity between the new question and each question in the corpus

similarity = []
for i in range(len(df.columns)):    
    cs_score = cosine_similarity(df.iloc[:,i].values, (pd.Series(new_question_freq)).values)
    if cs_score != cs_score:
      cs_score = 0       
    similarity.append([df.columns[i], cs_score])

# Sort the list of similarities in descending order
similarity.sort(key=lambda x: x[1], reverse=True)

print(pd.DataFrame(similarity, columns=['Q.NO', 'CS_SIM']))
print("\n")
# Print the most similar question and its answer
threshold = 0.5
if(similarity[0][1] < threshold):
    print("No Match Found,insufficient similarity")
else:
    print("Matched Question: ", questions_inp[int(similarity[0][0][1:])-1])
    print("Nearest Answer: ", answers[int(similarity[0][0][1:])-1])


# Create a Pandas DataFrame