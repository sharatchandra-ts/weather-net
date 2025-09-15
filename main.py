from fastapi import FastAPI
from contextlib import asynccontextmanager
import backend.database.operations as op
import backend.api.api as wapi

@asynccontextmanager
async def lifespan(app: FastAPI):
    # Startup
    op.init_db()
    yield
    # Shutdown (optional cleanup)
    # e.g., close DB connections, clear cache, etc.

app = FastAPI(
    title="Weather Station API",
    description="Receives ESP32 weather data and stores it in Postgres",
    version="1.0.0",
    lifespan=lifespan,
)

# Include routes
app.include_router(wapi.router, prefix="/weather", tags=["Weather"])