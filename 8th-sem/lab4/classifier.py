import numpy as np
class NaiveBayesClassifier:
    def __init__(self):
        self.class_prior = None
        self.word_likelihoods = None
        self.vocab_size = None
    
    def fit(self, X_train, y_train):
        # Calculate class priors
        self.classes, class_counts = np.unique(y_train, return_counts=True)
        self.class_prior = class_counts / len(y_train)
        
        # Calculate word likelihoods
        self.vocab_size = X_train.shape[1]
        self.word_likelihoods = np.zeros((len(self.classes), self.vocab_size))
        for i, c in enumerate(self.classes):
            class_docs = X_train[y_train == c]
            total_words_in_class = np.sum(class_docs)
            self.word_likelihoods[i] = (np.sum(class_docs, axis=0) + 1) / (total_words_in_class + self.vocab_size)
    
    def predict(self, X_test):
        predictions = []
        for doc in X_test:
            posteriors = []
            for i, c in enumerate(self.classes):
                prior = self.class_prior[i]
                likelihood = np.prod(self.word_likelihoods[i, doc.nonzero()[0]]) # ignoring zero counts
                posterior = prior * likelihood
                posteriors.append(posterior)
            predicted_class = self.classes[np.argmax(posteriors)]
            predictions.append(predicted_class)
        return predictions
    
    def score(self, X_test, y_test):
        y_pred = self.predict(X_test)
        return np.mean(y_pred == y_test)
    
    
    
