from fastapi import FastAPI
from backend.schemas.weather_schema import WeatherSchema

app = FastAPI()

@app.post('/weatherdata')
def post_data(data: WeatherSchema):
    print(data)
    return {'status': 'saved'}

@app.get('/weatherdata')
def get_data():
    return {'data': 'no-data'}