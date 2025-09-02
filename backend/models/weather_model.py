from sqlalchemy import Column, Integer, Float, DateTime, func
from backend.database.db import Base

class WeatherDB(Base):
    __tablename__ = 'weather'

    id = Column(Integer, primary_key=True, index=True)
    temperature = Column(Float, nullable=False)
    humidity = Column(Float, nullable=False)
    light_level = Column(Float, nullable=False)
    air_quality = Column(Float, nullable=False)
    timestamp = Column(DateTime(timezone=True), server_default=func.now(), index=True)
    machine = Column(Integer)

    def __repr__(self):
        return (f"<Weather(id={self.id}, " 
                f"temperature={self.temperature}, "
                f"humidity={self.humidity}, "
                f"light_level={self.light_level}, "
                f"air_quality={self.air_quality},"
                f"timestamp={self.timestamp},"
                f"machine={self.machine})>")