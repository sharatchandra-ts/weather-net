from pydantic import BaseModel

class Weather(BaseModel):
    temperature: float
    humidity: float
    light_level: float
    air_quality: float
    