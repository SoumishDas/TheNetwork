
# importing the required libraries
import pandas as pd
from sklearn.preprocessing import MinMaxScaler
  
# creating a dataframe
pd_data = pd.read_csv("Data/fake_bills.csv")
print(pd_data)

# Creating an instance of the sklearn.preprocessing.MinMaxScaler()
scaler = MinMaxScaler()
  
# Scaling the Price column of the created dataFrame and storing
# the result in ScaledPrice Column
pd_data[["diagonal","height_left","height_right","margin_low","margin_up","length"]] = scaler.fit_transform(pd_data[["diagonal","height_left","height_right","margin_low","margin_up","length"]])
  
pd_data.to_csv("Data/fake_bills_normalized.csv",index=False)