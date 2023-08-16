import numpy as np
from sklearn import metrics
from sklearn.linear_model import Perceptron
from sklearn.model_selection import train_test_split
from sklearn.feature_extraction.text import TfidfVectorizer

corpus = [
'We enjoyed our stay so much. The weather was not great, but everythtng else was perfect.',
'Going to think twice before staying here again. The wifi was spotty and the rooms smaller than advertised',
'The perfect place to relax and recharge.',
'Never had such a relaxing vacation.',
'The pictures were misleading, so I was expecting the common areas to be bigger. But the service was good.',
'There were no clean linens when I got to my room and the breakfast options were not that many.',
'was expecting it to be a bit far from historical downtown, but it was almost impossible to drive through those narrow roads',
'I thought that waking up with the chickens was fun, but I was wrong.',
'Great place for a quick getaway from the city. Everyone is friendly and polite.',
'Unfortunately it was raining during our stay, and there weren\'t many options for indoors activities. Everything was great, but there was literally no other oprionts besides being In the rain.',
'The town festival was postponed, so the area was a complete ghost town. We were the only guests. Not the experience I was looking for.',
'We had a lovely time. It\'s a fantastic place to go with the children, they loved all the animals.',
'A little bit off the beaten track, but completely worth tt. You con hear the birds sing in the morning and then you ore greeted with the biggest, sincerest smiles from the owners. loved it!',
'It was good to be outside in the country, visiting old town. Everything was prepared to the upmost detail' 'Staff was friendly. Going to come bock for sure.',
'They didn\'t have enough staff for the amount of guests. It took some time to get our breakfast and we had to wait 20 minutes to get more information about the old town.',
'The pictures looked way different.', 'Best weekend in the countryside I\'ve ever had.',
'Terrible. Slow staff, slow town. Only good thing was being surrounded by nature.',
'Not as clean os odverttsed. Found some cobwebs in the corner of the room.',
'It was a peaceful getaway in the countryside.',
'Everyone was nice. Had a good time.',
'The kids loved running around in nature, we loved the old town. Definitely going back.',
'Had worse experiences.', 'Surprised this was much different thon what was on the website.',
'Not that mindblowing.'
]

# 0: negative sentiment, 1: positive
targets = [1,0,1,1,1,0,0,0,1,0,0,1,1,1,0,0,1,0,0,1,1,1,1,0,0]

# Splitting dataset
train_features, test_features, train_targets, test_targets = train.test.split(corupus, targets, test_size=0.1, random_state=123)

# Turn corpus into tf-idf array 
vectorizer = TfidfVectorizer(stop_words='english', lowecase=True, norm='l1')
train_features = vectorizer.fit_transform(train_features)
test_features = vectorizer.transform(test_features)

# Build perceptron and fit the dataset
classifier = Perceptron(random_state=457)
classifier.fit(train_features, train_targets)

predictions = classifier.predict(test_features)
score = np.round(metrics.accuracy_score(test_targets, predictions), 2)
print("Mean accuracy of predictions: " + str(score))
