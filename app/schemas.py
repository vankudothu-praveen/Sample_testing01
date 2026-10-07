from datetime import date, datetime
from typing import Generic, TypeVar
from pydantic import BaseModel, ConfigDict, EmailStr, Field, field_validator
from app.db.models import EmploymentStatus

class LoginRequest(BaseModel):
    username: str = Field(min_length=1, max_length=100)
    password: str = Field(min_length=1)

class TokenResponse(BaseModel):
    access_token: str
    token_type: str = "bearer"

class EmployeeFields(BaseModel):
    first_name: str = Field(min_length=1, max_length=100)
    last_name: str = Field(min_length=1, max_length=100)
    email: EmailStr
    department: str = Field(min_length=1, max_length=100)
    job_title: str = Field(min_length=1, max_length=150)
    date_of_joining: date
    employment_status: EmploymentStatus

    @field_validator("first_name", "last_name", "department", "job_title", mode="before")
    @classmethod
    def trim_nonempty(cls, value):
        if isinstance(value, str):
            value = value.strip()
            if not value:
                raise ValueError("must not be blank")
        return value

class EmployeeCreate(EmployeeFields):
    pass

class EmployeeUpdate(BaseModel):
    first_name: str | None = Field(default=None, min_length=1, max_length=100)
    last_name: str | None = Field(default=None, min_length=1, max_length=100)
    email: EmailStr | None = None
    department: str | None = Field(default=None, min_length=1, max_length=100)
    job_title: str | None = Field(default=None, min_length=1, max_length=150)
    date_of_joining: date | None = None
    employment_status: EmploymentStatus | None = None

    @field_validator("first_name", "last_name", "department", "job_title", mode="before")
    @classmethod
    def trim_nonempty(cls, value):
        if isinstance(value, str):
            value = value.strip()
            if not value:
                raise ValueError("must not be blank")
        return value

class EmployeeResponse(EmployeeFields):
    model_config = ConfigDict(from_attributes=True)
    employee_id: int
    created_at: datetime
    updated_at: datetime

T = TypeVar("T")
class Pagination(BaseModel):
    page: int
    page_size: int
    total_records: int
    total_pages: int

class EmployeeListResponse(BaseModel, Generic[T]):
    items: list[T]
    pagination: Pagination

class ErrorResponse(BaseModel):
    error_code: str
    message: str
    details: object | None = None
    timestamp: datetime
