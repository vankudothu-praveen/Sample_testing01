import logging
import time
import uuid
from contextlib import asynccontextmanager
from fastapi import FastAPI, Request
from fastapi.exceptions import RequestValidationError
from fastapi.responses import JSONResponse
from app.api.v1.router import api_router
from app.config import settings
from app.db.session import dispose_engine

logging.basicConfig(level=settings.log_level.upper(), format="%(asctime)s %(levelname)s %(name)s %(message)s")
logger = logging.getLogger("employee_service")

@asynccontextmanager
async def lifespan(_: FastAPI):
    yield
    await dispose_engine()

app = FastAPI(title=settings.app_name, version="1.0.0", lifespan=lifespan)
app.include_router(api_router, prefix="/api/v1")

@app.middleware("http")
async def request_logging(request: Request, call_next):
    request_id = request.headers.get("X-Request-ID") or str(uuid.uuid4())
    started = time.perf_counter()
    try:
        response = await call_next(request)
        response.headers["X-Request-ID"] = request_id
        logger.info("request_complete", extra={"request_id": request_id, "method": request.method, "path": request.url.path, "status_code": response.status_code, "duration_ms": round((time.perf_counter() - started) * 1000, 2)})
        return response
    except Exception:
        logger.exception("request_failed", extra={"request_id": request_id, "path": request.url.path})
        raise

@app.exception_handler(RequestValidationError)
async def validation_error_handler(_: Request, exc: RequestValidationError):
    return JSONResponse(status_code=422, content={"error_code": "VALIDATION_ERROR", "message": "Request validation failed", "details": exc.errors()})

@app.exception_handler(Exception)
async def unhandled_error_handler(_: Request, exc: Exception):
    logger.exception("unhandled_exception", exc_info=exc)
    return JSONResponse(status_code=500, content={"error_code": "INTERNAL_SERVER_ERROR", "message": "Internal server error"})

@app.get("/health", tags=["Operations"])
async def health():
    return {"status": "ok"}
