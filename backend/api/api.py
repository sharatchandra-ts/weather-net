from fastapi import APIRouter, Depends
from sqlalchemy.orm import Session
import backend.database.operations as op
from backend.schemas.weather_schema import WeatherSchema

router = APIRouter()

# Endpoint to add new weather data to the database
@router.post('/data')
def post_data(data: WeatherSchema, db: Session = Depends(op.get_db)):
    print(data)
    op.add_weather(weather=data.map_to_db(), db=db)
    return data

# Endpoint to retrieve weather data (currently returns placeholder)
@router.get('/data')
def get_data():
    return {'data': 'no-data'}