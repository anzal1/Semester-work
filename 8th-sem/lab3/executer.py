from bs4 import BeautifulSoup
import requests
from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize
from nltk.stem import PorterStemmer, WordNetLemmatizer
from sklearn.feature_extraction.text import CountVectorizer, TfidfVectorizer
from sklearn.naive_bayes import MultinomialNB
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, classification_report
from sklearn.feature_extraction.text import CountVectorizer
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.model_selection import train_test_split

# Function to scrape Wikipedia pages
def scrape_wikipedia(url):
    # Use requests to fetch the HTML content
    response = requests.get(url)

    # Use BeautifulSoup to parse the HTML content
    soup = BeautifulSoup(response.content, 'html.parser')
    # Extract text content from paragraphs
    text = [p.get_text() for p in soup.find_all('p')]
    # Join the text into a single string
    return ' '.join(text)



# Function to preprocess and clean text
def preprocess_text(text):
    # Tokenization
    tokens = word_tokenize(text)
    # Lowercasing
    tokens = [token.lower() for token in tokens]
    # Removing punctuation
    tokens = [token for token in tokens if token.isalnum()]
    # Removing stopwords
    stop_words = set(stopwords.words('english'))
    tokens = [token for token in tokens if token not in stop_words]
    # Stemming or Lemmatization (choose one)
    # stemmer = PorterStemmer()
    # tokens = [stemmer.stem(token) for token in tokens]
    lemmatizer = WordNetLemmatizer()
    tokens = [lemmatizer.lemmatize(token) for token in tokens]
    # Join the tokens into a single string
    return ' '.join(tokens)

# URLs of Wikipedia pages related to sports and education
sports_url = [
    "https://en.wikipedia.org/wiki/Sport",
    "https://en.wikipedia.org/wiki/Physical_fitness",
    "https://en.wikipedia.org/wiki/Exercise",
    ]
education_url = [
    "https://en.wikipedia.org/wiki/Education",
    "https://en.wikipedia.org/wiki/History_of_education",
    "https://en.wikipedia.org/wiki/Philosophy_of_education",
]

# scrape the Wikipedia pages

sports_text = [preprocess_text(scrape_wikipedia(url)) for url in sports_url]
education_text = [preprocess_text(scrape_wikipedia(url)) for url in education_url]



unigram_vectorizer = CountVectorizer(ngram_range=(1, 1), token_pattern=r'\b\w+\b', min_df=1)
X_unigram_counts = unigram_vectorizer.fit_transform(sports_text+education_text)

# Print unigram counts matrix
print("Unigram Counts Matrix:")
print(X_unigram_counts.toarray())
print("Vocabulary:", unigram_vectorizer.get_feature_names_out())

# Convert text data into feature matrices for bigrams
bigram_vectorizer = CountVectorizer(ngram_range=(2, 2), token_pattern=r'\b\w+\b', min_df=1)
X_bigram_counts = bigram_vectorizer.fit_transform(sports_text + education_text)

# Get vocabulary for bigrams
vocab_bigram = bigram_vectorizer.get_feature_names_out()

# Convert bigram counts matrix to bigram probability matrix
X_bigram_probs = np.zeros_like(X_bigram_counts.toarray(), dtype=float)
for i in range(X_bigram_counts.shape[0]):
    for j in range(X_bigram_counts.shape[1]):
        bigram = vocab_bigram[j]
        unigram1, unigram2 = bigram.split()
        idx_unigram1 = unigram_vectorizer.vocabulary_[unigram1]
        idx_unigram2 = unigram_vectorizer.vocabulary_[unigram2]
        unigram_count1 = X_unigram_counts[i, idx_unigram1]
        unigram_count2 = X_unigram_counts[i, idx_unigram2]
        if unigram_count1 == 0 or unigram_count2 == 0:
            X_bigram_probs[i, j] = 0
        else:
            X_bigram_probs[i, j] = X_bigram_counts[i, j] / min(unigram_count1, unigram_count2)

print("\nBigram Probability Matrix:")
print(X_bigram_probs)

tfidf_vectorizer = TfidfVectorizer()
X_tfidf = tfidf_vectorizer.fit_transform(sports_text + education_text)

# Print TF-IDF matrix
print("TF-IDF Matrix:")
print(X_tfidf.toarray())

# apply naive bayes classifier on each matrix
X_test_counts = unigram_vectorizer.transform(sports_text + education_text)
X_test_bigram_counts = bigram_vectorizer.transform(sports_text + education_text)
X_test_bigram_probs = np.zeros_like(X_test_bigram_counts.toarray(), dtype=float)
for i in range(X_test_bigram_counts.shape[0]):
    for j in range(X_test_bigram_counts.shape[1]):
        bigram = vocab_bigram[j]
        unigram1, unigram2 = bigram.split()
        idx_unigram1 = unigram_vectorizer.vocabulary_[unigram1]
        idx_unigram2 = unigram_vectorizer.vocabulary_[unigram2]
        unigram_count1 = X_unigram_counts[i, idx_unigram1]
        unigram_count2 = X_unigram_counts[i, idx_unigram2]
        if unigram_count1 == 0 or unigram_count2 == 0:
            X_test_bigram_probs[i, j] = 0
        else:
            X_test_bigram_probs[i, j] = X_test_bigram_counts[i, j] / min(unigram_count1, unigram_count2)

X_test_tfidf = tfidf_vectorizer.transform(sports_text + education_text)



# use naive bayes classifier for each matrix

X_train, X_test, y_train, y_test = train_test_split(X_unigram_counts, [0, 1], test_size=0.5, random_state=0)

clf = MultinomialNB().fit(X_train, y_train)
predicted = clf.predict(X_test)
print("Unigram Counts Accuracy:", accuracy_score(y_test, predicted))
print("Unigram Counts Classification Report:")
print(classification_report(y_test, predicted))

X_train, X_test, y_train, y_test = train_test_split(X_bigram_counts, [0, 1], test_size=0.5, random_state=0)

clf = MultinomialNB().fit(X_train, y_train)
predicted = clf.predict(X_test)
print("Bigram Counts Accuracy:", accuracy_score(y_test, predicted))
print("Bigram Counts Classification Report:")
print(classification_report(y_test, predicted))

X_train, X_test, y_train, y_test = train_test_split(X_bigram_probs, [0, 1], test_size=0.5, random_state=0)

clf = MultinomialNB().fit(X_train, y_train)
predicted = clf.predict(X_test)
print("Bigram Probability Accuracy:", accuracy_score(y_test, predicted))
print("Bigram Probability Classification Report:")
print(classification_report(y_test, predicted))



