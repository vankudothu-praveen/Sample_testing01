from fastapi import APIRouter
from app.api.v1.endpoints.auth import router as auth_router
from app.api.v1.endpoints.employees import router as employees_router

api_router = APIRouter()
api_router.include_router(auth_router)
api_router.include_router(employees_router)
