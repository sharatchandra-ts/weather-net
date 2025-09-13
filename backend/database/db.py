from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker, declarative_base
import os
from dotenv import load_dotenv

# Load environment variables from .env
load_dotenv()

# This is to run locally

""" 
# Setting default values to handle null errors
DB_USER = os.getenv("DB_USER", "postgres")
DB_PASSWORD = os.getenv("DB_PASSWORD", "password")
DB_HOST = os.getenv("DB_HOST", "localhost")
DB_PORT = os.getenv("DB_PORT", "5432")   # default 5432
DB_NAME = os.getenv("DB_NAME", "testdb")

# Example: postgresql+psycopg2://postgres:your_password@localhost:5432/your_database_name

DATABASE_URL = (
    f"postgresql+psycopg2://{DB_USER}:{DB_PASSWORD}@{DB_HOST}:{DB_PORT}/{DB_NAME}"
) 
"""

DATABASE_URL = os.getenv("DATABASE_URL")

# Create SQLAlchemy engine
engine = create_engine(DATABASE_URL)

# SessionLocal will be used in routes to talk to DB
SessionLocal = sessionmaker(bind=engine)

# Base class for our models
Base = declarative_base()
