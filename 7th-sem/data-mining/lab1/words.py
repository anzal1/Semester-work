# write a program to count the freq of words after reading the text file
import re
def print_word_freq():
    data=input().strip()
    datafreq={}
    for word in re.split(r' |,|!|;', data):
        if(word!=''):
            if word not in datafreq:
                datafreq[word.lower()]=1
            else:
                datafreq[word.lower()]+=1
    datafreq = sorted(datafreq.items(),key=lambda item:item[1],reverse=True)
    print_table(datafreq)

def print_table(datafreq):
    print ("{:<15} {:<2}".format('Word','Frequency'))
    for words in datafreq:
        print("{:<15} {:<2}".format(words[0],words[1]))


def input():
    filePath = 'input.txt'
    with open(filePath, 'r') as file:
        data = file.read().replace('\n', '');
    return data

if __name__ == "__main__":
    print_word_freq()
