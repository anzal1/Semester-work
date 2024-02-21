from bs4 import BeautifulSoup
from preprocess import preprocess_text,word_tokenize
import requests
url = "https://en.wikipedia.org/wiki/Permutation"  
doc = requests.get(url).text
# print(doc)
cleantext = BeautifulSoup(doc, "lxml").text
cleantext = preprocess_text(cleantext)
#write this into a text file 
with open('plainText.txt', 'w') as f:
    f.write(cleantext)


#map all the links with their text 
soup = BeautifulSoup(doc, 'html.parser')
links = soup.find_all('a')
linkMap = {}
for link in links:
    linkMap[link.get('href')] = link.text


# prettify the linkmap and write it to a file
with open('linkMap.txt', 'w') as f:
    for key, value in linkMap.items():
        f.write('%s:%s\n' % (key, value))


# write all paragraphs to a file
paragraphs = soup.find_all('p')
with open('paragraphs.txt', 'w') as f:
    for paragraph in paragraphs:
        f.write(paragraph.text)

# write all the sentences to a file
sentences = []
for paragraph in paragraphs:
    sentences.extend(paragraph.text.split('.'))
with open('sentences.txt', 'w') as f:
    for sentence in sentences:
        f.write(sentence)

# write all the words to a file
words = []
for sentence in sentences:
    #extract words from the sentences , they can be comma seperated 
    words.extend(word_tokenize(sentence))

with open('words.txt', 'w') as f:
    for word in words:
        f.write(word)

# write all the unique words to a file
uniqueWords = set(words)
with open('uniqueWords.txt', 'w') as f:
    for word in uniqueWords:
        f.write(word)

# write all the links to a file
with open('links.txt', 'w') as f:
    for link in links:
        f.write(link.get('href'))
        



















# Preprocess the text
# cleantext = preprocess_text(cleantext)
# print(cleantext)

# Given a URL by the user.
# fetch the textual content of the page and preprocess it.
# Return the preprocessed text.
# prepare a list of paragraphs , sentences , words, unique words and links
# the links should be mapped to the paragraph they are in. like if an anchor tag has a link the text inside the anchor tag should be mapped to the link.



# import requests
# from bs4 import BeautifulSoup
# import re

# def fetch_and_preprocess(url):
#     # Fetch webpage content
#     response = requests.get(url)
#     if response.status_code != 200:
#         return "Failed to fetch content"

#     # Parse HTML content
#     soup = BeautifulSoup(response.content, 'html.parser')

#     # Extract paragraphs, sentences, words, and links
#     paragraphs = [p.get_text() for p in soup.find_all('p')]
#     sentences = []
#     words = []
#     unique_words = set()
#     links_mapping = {}

#     for paragraph in paragraphs:
#         paragraph_links = {}
#         paragraph_sentences = re.split(r'(?<!\w\.\w.)(?<![A-Z][a-z]\.)(?<=\.|\?)\s', paragraph)
#         for sentence in paragraph_sentences:
#             sentences.append(sentence)
#             sentence_words = re.findall(r'\b\w+\b', sentence)
#             words.extend(sentence_words)
#             unique_words.update(sentence_words)
#             for link in soup.find_all('a', href=True, text=re.compile(re.escape(sentence))):
#                 paragraph_links[link['href']] = sentence
#         links_mapping.update(paragraph_links)

#     return paragraphs, sentences, words, unique_words, links_mapping

# # Example usage
# url = "https://en.wikipedia.org/wiki/Permutation"
# paragraphs, sentences, words, unique_words, links_mapping = fetch_and_preprocess(url)

# print("Paragraphs:")
# for idx, paragraph in enumerate(paragraphs, 1):
#     print(f"Paragraph {idx}: {paragraph}")

# print("\nSentences:", sentences)
# print("\nWords:", words)
# print("\nUnique Words:", unique_words)
# print("\nLinks Mapping:")
# for link, sentence in links_mapping.items():
#     print(f"Link: {link}, Sentence: {sentence}")
