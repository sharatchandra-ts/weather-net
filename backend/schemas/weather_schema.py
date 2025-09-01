from pydantic import BaseModel

class WeatherSchema(BaseModel):
    temperature: float
    humidity: float
    light_level: float
    air_quality: float
    machine: int

    def __repr__(self):
        return (f"<Weather(temperature={self.temperature}, "
                f"humidity={self.humidity}, "
                f"light_level={self.light_level}, "
                f"air_quality={self.air_quality},"
                f"machine={self.machine})>")    
    