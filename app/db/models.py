import enum
from datetime import date, datetime
from sqlalchemy import Date, DateTime, Enum, Index, String, func
from sqlalchemy.orm import Mapped, mapped_column
from app.db.base import Base

class EmploymentStatus(str, enum.Enum):
    ACTIVE = "ACTIVE"
    INACTIVE = "INACTIVE"
    TERMINATED = "TERMINATED"

class UserRole(str, enum.Enum):
    ADMIN = "ADMIN"
    USER = "USER"

class Employee(Base):
    __tablename__ = "employees"
    __table_args__ = (Index("ix_employees_department", "department"), Index("ix_employees_employment_status", "employment_status"))

    employee_id: Mapped[int] = mapped_column(primary_key=True, autoincrement=True)
    first_name: Mapped[str] = mapped_column(String(100), nullable=False)
    last_name: Mapped[str] = mapped_column(String(100), nullable=False)
    email: Mapped[str] = mapped_column(String(255), unique=True, nullable=False, index=True)
    department: Mapped[str] = mapped_column(String(100), nullable=False)
    job_title: Mapped[str] = mapped_column(String(150), nullable=False)
    date_of_joining: Mapped[date] = mapped_column(Date, nullable=False)
    employment_status: Mapped[EmploymentStatus] = mapped_column(Enum(EmploymentStatus, name="employmentstatus"), nullable=False)
    created_at: Mapped[datetime] = mapped_column(DateTime(timezone=True), server_default=func.now(), nullable=False)
    updated_at: Mapped[datetime] = mapped_column(DateTime(timezone=True), server_default=func.now(), onupdate=func.now(), nullable=False)

class User(Base):
    __tablename__ = "users"
    user_id: Mapped[int] = mapped_column(primary_key=True, autoincrement=True)
    username: Mapped[str] = mapped_column(String(100), unique=True, nullable=False)
    password_hash: Mapped[str] = mapped_column(String(255), nullable=False)
    role: Mapped[UserRole] = mapped_column(Enum(UserRole, name="userrole"), nullable=False)
    created_at: Mapped[datetime] = mapped_column(DateTime(timezone=True), server_default=func.now(), nullable=False)
