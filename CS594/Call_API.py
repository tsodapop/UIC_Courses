#you need to import google-cloud-automl to run the following code

#in terminal, before running the .py file, run the following:
#export GOOGLE_APPLICATION_CREDENTIALS="CREDENTIALS.json FILE"

#once you are done running the above, the format for running the file is as follows:
#python call_api.py content

import os
import sys
from google.cloud import automl_v1beta1 as automl
from google.cloud.automl_v1beta1.proto import service_pb2

os.system('clear') #clears the console before running the below


# 'content' is the image of the watch you are trying to analyze and get labels out of 
def get_prediction(content):

  project_id = '946558125160'
  model_id = 'ICN6835430693418303488'

  prediction_client = automl.PredictionServiceClient()

  name = 'projects/{}/locations/us-central1/models/{}'.format(project_id, model_id)
  payload = {'image': {'image_bytes': content }}
  params = {}
  request = prediction_client.predict(name, payload, params) #the actual label info that will be returned
  return request  # waits till request is returned

if __name__ == '__main__':
  file_path = sys.argv[1]

  with open(file_path, 'rb') as ff: #grab the image
    content = ff.read()

print("______________________Classification of image: ", file_path, "______________________")
print(get_prediction(content)) #get the info from the image