import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""

        temp_positives = []
        
        f = open(positives)
        
        for line in f:
            
            if line[0] != ";":
                
                temp_positives.append(line.rstrip())
        
        f.close()
        
        temp_negatives = []
        
        f = open(negatives)
        
        for line in f:
            
            if line[0] != ";":
                
                temp_negatives.append(line.rstrip())
                
        f.close()
        
        self.positives = temp_positives
        self.negatives = temp_negatives

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""

        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text)
    
        score = 0
        
        for token in tokens:
            
            if token in self.positives:
                
                score += 1
                
            elif token in self.negatives:
                
                score -= 1
        
        return score
