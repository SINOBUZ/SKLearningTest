import pandas as pd
from sklearn import svm, metrics
from sklearn.model_selection import train_test_split
 
csv = pd.read_csv("irisData.csv")
dataset = csv[["sepal_length","sepal_width","petal_length","petal_width"]]
irislabel = csv["species"]
 
train_data, test_data, train_label, test_label=\
    train_test_split(dataset, irislabel, test_size=0.3)
 
clf = svm.SVC()
clf.fit(train_data,  train_label)
results = clf.predict(test_data)
 
score = metrics.accuracy_score(results, test_label)
print(results)
print("정답률 : ", score)