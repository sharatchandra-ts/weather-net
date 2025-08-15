from fastapi import FastAPI
from models.weather_model import Weather

app = FastAPI()

@app.post('/weatherdata')
def post_data(data: Weather):
    print(data)
    return {'status': 'saved'}

@app.get('/weatherdata')
def get_data():
    return {'data': 'no-data'}