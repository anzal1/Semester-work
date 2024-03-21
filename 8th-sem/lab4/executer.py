from bs4 import BeautifulSoup
import requests
from bs4 import BeautifulSoup
import requests
from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize
from nltk.stem import PorterStemmer
from sklearn.feature_extraction.text import CountVectorizer, TfidfVectorizer
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, classification_report
from sklearn.feature_extraction.text import CountVectorizer
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.model_selection import train_test_split

from classifier import NaiveBayesClassifier


def scrape_wikipedia(url):
    # Use requests to fetch the HTML content
    response = requests.get(url)

    # Use BeautifulSoup to parse the HTML content
    soup = BeautifulSoup(response.content, 'html.parser')
    # Extract text content from paragraphs
    text = [p.get_text() for p in soup.find_all('p')]
    # Join the text into a single string
    return ' '.join(text)


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
    stemmer = PorterStemmer()
    tokens = [stemmer.stem(token) for token in tokens]
    # lemmatizer = WordNetLemmatizer()
    # tokens = [lemmatizer.lemmatize(token) for token in tokens]
    # Join the tokens into a single string
    return ' '.join(tokens)

# URLs of Wikipedia pages related to sports and education
sports_url = [
     "https://en.wikipedia.org/wiki/Soccer",
    "https://en.wikipedia.org/wiki/Basketball",
    "https://en.wikipedia.org/wiki/American_football",
    "https://en.wikipedia.org/wiki/Tennis",
    "https://en.wikipedia.org/wiki/Cricket",
    "https://en.wikipedia.org/wiki/Rugby_football",
    "https://en.wikipedia.org/wiki/Golf",
    "https://en.wikipedia.org/wiki/Boxing",
    "https://en.wikipedia.org/wiki/Swimming_(sport)",
    "https://en.wikipedia.org/wiki/Track_and_field",
    "https://en.wikipedia.org/wiki/Volleyball",
    "https://en.wikipedia.org/wiki/Baseball",
    "https://en.wikipedia.org/wiki/Formula_One",
    "https://en.wikipedia.org/wiki/Cycling",
    "https://en.wikipedia.org/wiki/Ice_hockey",
    "https://en.wikipedia.org/wiki/Skiing",
    "https://en.wikipedia.org/wiki/Surfing",
    "https://en.wikipedia.org/wiki/Figure_skating",
    "https://en.wikipedia.org/wiki/Martial_arts",
    "https://en.wikipedia.org/wiki/Sailing"
    ]
education_url = [
    "https://en.wikipedia.org/wiki/Education",
    "https://en.wikipedia.org/wiki/School",
    "https://en.wikipedia.org/wiki/University",
    "https://en.wikipedia.org/wiki/College",
    "https://en.wikipedia.org/wiki/Higher_education",
    "https://en.wikipedia.org/wiki/Educational_technology",
    "https://en.wikipedia.org/wiki/Adult_education",
    "https://en.wikipedia.org/wiki/Learning",
    "https://en.wikipedia.org/wiki/Educational_psychology",
    "https://en.wikipedia.org/wiki/Educational_research",
    "https://en.wikipedia.org/wiki/Curriculum",
    "https://en.wikipedia.org/wiki/Educational_assessment",
    "https://en.wikipedia.org/wiki/Education_policy",
    "https://en.wikipedia.org/wiki/Teaching",
    "https://en.wikipedia.org/wiki/Learning_management_system"
]

# scrape the Wikipedia pages
sports_content = [scrape_wikipedia(url) for url in sports_url]
education_content = [scrape_wikipedia(url) for url in education_url]

# preprocess the text
sports_content = [preprocess_text(text) for text in sports_content]
education_content = [preprocess_text(text) for text in education_content]

# create a unigram matric for the sports and education content

unigram_vectorizer = CountVectorizer(ngram_range=(1, 1), token_pattern=r'\b\w+\b', min_df=1)
X_unigram_counts = unigram_vectorizer.fit_transform(sports_content + education_content)


print("Unigram Counts Matrix:")
print(X_unigram_counts.toarray())


X_train, X_test, y_train, y_test = train_test_split(X_unigram_counts, ["Sports"] * len(sports_content) + ["Education"] * len(education_content), test_size=0.2, random_state=42)
classifier = NaiveBayesClassifier()
classifier.fit(X_train, y_train)

predictions = classifier.predict(X_test)

# print accuracy score in percentage 
print("Accuracy Score:", accuracy_score(y_test, predictions))



print("Classification Report:")
# fix zero division error in classification report
print(classification_report(y_test, predictions, zero_division=1))




print('\n\n')

# create a bigram matric for the sports and education content

bigram_vectorizer = CountVectorizer(ngram_range=(2, 2), token_pattern=r'\b\w+\b', min_df=1)

X_bigram_counts = bigram_vectorizer.fit_transform(sports_content + education_content)


print("Bigram Counts Matrix:")
print(X_bigram_counts.toarray())

X_train, X_test, y_train, y_test = train_test_split(X_bigram_counts, ["Sports"] * len(sports_content) + ["Education"] * len(education_content), test_size=0.2, random_state=42)

classifier = NaiveBayesClassifier()

classifier.fit(X_train, y_train)

predictions = classifier.predict(X_test)

# print accuracy score in percentage
print("Accuracy Score:", accuracy_score(y_test, predictions))

print("Classification Report:")
# fix zero division error in classification report
print(classification_report(y_test, predictions, zero_division=1))
print('\n\n')


# create a tf-idf matric for the sports and education content

tfidf_vectorizer = TfidfVectorizer()
X_tfidf = tfidf_vectorizer.fit_transform(sports_content + education_content)

print("TF-IDF Matrix:")
print(X_tfidf.toarray())

X_train, X_test, y_train, y_test = train_test_split(X_tfidf, ["Sports"] * len(sports_content) + ["Education"] * len(education_content), test_size=0.2, random_state=42)

classifier = NaiveBayesClassifier()

classifier.fit(X_train, y_train)

predictions = classifier.predict(X_test)

# print accuracy score in percentage

print("Accuracy Score:", accuracy_score(y_test, predictions))

print("Classification Report:")
# fix zero division error in classification report
print(classification_report(y_test, predictions, zero_division=1))

print('\n\n')






