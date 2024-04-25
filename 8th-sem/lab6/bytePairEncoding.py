import re, collections

rules  =[]

def get_stats(vocab):
    pairs = collections.defaultdict(int)
    for word, freq in vocab.items():
        symbols = word.split()
        for i in range(len(symbols)-1):
            pairs[symbols[i],symbols[i+1]] += freq
    return pairs

def merge_vocab(pair, v_in):
    v_out = {}
    bigram = re.escape(' '.join(pair))
    p = re.compile(r'(?<!\S)' + bigram + r'(?!\S)')
    for word in v_in:
        w_out = p.sub(''.join(pair), word)
        v_out[w_out] = v_in[word]
    return v_out

def get_tokens(vocab):
    tokens = collections.defaultdict(int)
    for word, freq in vocab.items():
        word_tokens = word.split()
        for token in word_tokens:
            tokens[token] += freq
    return tokens

# vocab = {'l o w </w>': 5, 'l o w e r </w>': 2, 'n e w e s t </w>': 6, 'w i d e s t </w>': 3}
def prepare_vocab(sentence):
    vocab = collections.defaultdict(int)
    words = sentence.strip().split()
    for word in words:
        vocab[' '.join(list(word)) + ' </w>'] += 1
    print(vocab)
    return vocab

sentence = 'LOW LOWEST NEWER WIDER NEW'
vocab = prepare_vocab(sentence)

print('==========')
print('Tokens Before BPE')
tokens = get_tokens(vocab)
print('Tokens: {}'.format(tokens))
print('Number of tokens: {}'.format(len(tokens)))
print('==========')

num_merges = 5
for i in range(num_merges):
    pairs = get_stats(vocab)
    if not pairs:
        break
    best = max(pairs, key=pairs.get)
    vocab = merge_vocab(best, vocab)
    rules.append(best)
    print(vocab)
    print('Iter: {}'.format(i))
    print('Best pair: {}'.format(best))
    tokens = get_tokens(vocab)
    print('Tokens: {}'.format(tokens))
    print('Number of tokens: {}'.format(len(tokens)))
    print('==========')



test_sentence = 'LOWER'

    # use rules to tokenize test_sentence

print('Rules: {}'.format(rules))
print('Test Sentence: {}'.format(test_sentence))

test_vocab = prepare_vocab(test_sentence)

for rule in rules:
    test_vocab = merge_vocab(rule, test_vocab)
    print(test_vocab)
    tokens = get_tokens(test_vocab)
    print('Tokens: {}'.format(tokens))
    print('Number of tokens: {}'.format(len(tokens)))
    print('==========')
    



