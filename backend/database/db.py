from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker, declarative_base
import os
from dotenv import load_dotenv

# Load environment variables from .env
load_dotenv()

# Example: postgresql+psycopg2://user:password@localhost/mydb
DATABASE_URL = (
    f"postgresql://{os.getenv('DB_USER')}:"
    f"{os.getenv('DB_PASSWORD')}@"
    f"{os.getenv('DB_HOST')}:"
    f"{os.getenv('DB_PORT')}/"
    f"{os.getenv('DB_NAME')}"
)

# Create SQLAlchemy engine
engine = create_engine(DATABASE_URL)

# SessionLocal will be used in routes to talk to DB
SessionLocal = sessionmaker(bind=engine)

# Base class for our models
Base = declarative_base()
