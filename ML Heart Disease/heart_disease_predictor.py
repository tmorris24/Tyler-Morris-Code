# Import needed libraries
from sklearn.utils import shuffle
from io import BytesIO
import streamlit as st
from PIL import Image
import pandas as pd
import numpy as np
import pickle
import base64

def streamlit_interface():
   """
      Function for Streamlit Interface
   """
   st.markdown('<h2 style="background-color:MediumSeaGreen; text-align:center; font-family:arial;color:white">HEART DISEASE PREDICTOR</h2>', unsafe_allow_html=True)
   
   
   # Main Page (Right)
   img = Image.open('./static/heart_disease.JPG')
   st.image(img, width=150)
   age    = st.slider('Age', 30, 80 , step=5)
   sex    = st.selectbox('Gender', ('Female', 'Male'))
   chest_pain    = st.slider('Chest Pain', 0, 3 , step=1)
   tres_bps    = st.slider('Tres BPS', 90, 200 , step=10)

   if st.button('Submit'):
          st.success('Hello World')
      

   #    input_arr = np.array([sepal_length, sepal_width, petal_length, petal_width]).reshape(1, -1)
   #    iris_prediction, confidence = pred_iris_flower(input_arr)
      
   #    st.success(usr_model + ' || Prediction : ' + iris_prediction + ' || Model Confidence : ' + confidence + '%')

   #    st.image(image_map[iris_prediction], width=200, caption = iris_prediction)

if __name__ == '__main__':
    streamlit_interface()
