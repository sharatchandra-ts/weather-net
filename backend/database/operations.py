from sqlalchemy.orm import Session
from backend.models.weather_model import WeatherDB
from backend.database.db import SessionLocal, engine, Base


# Creates all the tables inside the engine
def init_db():
    Base.metadata.create_all(bind=engine)


# Dependency for FastAPI (yields a DB session)
def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()


# Add new weather data to DB
def add_weather(weather: WeatherDB, db: Session):
    try:
        db.add(weather)
        db.commit()
        db.refresh(weather)  # reload with generated values like ID
        return weather
    except Exception as e:
        print("Error in add_weather:", e)
        db.rollback()
        return None


# Delete a given weather object
def delete_weather(weather: WeatherDB, db: Session):
    try:
        db.delete(weather)
        db.commit()
        return True
    except Exception as e:
        print("Error in delete_weather:", e)
        db.rollback()
        return False


# Delete weather by ID
def delete_weather_with_id(id: int, db: Session):
    try:
        weather_to_delete = db.query(WeatherDB).filter_by(id=id).first()
        if weather_to_delete:
            db.delete(weather_to_delete)
            db.commit()
            return True
        else:
            print("Weather ID not found.")
            return False
    except Exception as e:
        print("Error in delete_weather_with_id:", e)
        db.rollback()
        return False
