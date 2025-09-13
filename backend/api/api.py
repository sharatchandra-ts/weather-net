from fastapi import APIRouter, Depends
from sqlalchemy.orm import Session
import backend.database.operations as op
from backend.schemas.weather_schema import WeatherSchema

router = APIRouter()

# Endpoint to add new weather data to the database
@router.post('/data')
def post_data(data: list[WeatherSchema], db: Session = Depends(op.get_db)):
    print(data)
    for l in data:
        op.add_weather(weather=l.map_to_db(), db=db)
    return data

# Endpoint to retrieve all weather data
@router.get('/data')
def get_data(db: Session = Depends(op.get_db)):
    return op.read_weather_all(db=db)

# Endpoint to retrieve weather data by id
@router.get('/data/{id}')
def get_data(id:int, db: Session = Depends(op.get_db)):
    return op.read_weather(id=id, db=db)