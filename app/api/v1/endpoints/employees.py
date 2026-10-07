import math
from typing import Annotated, Literal
from fastapi import APIRouter, Depends, HTTPException, Query, status
from sqlalchemy import func, select
from sqlalchemy.exc import IntegrityError
from sqlalchemy.ext.asyncio import AsyncSession
from app.db.models import Employee, EmploymentStatus, User
from app.db.session import get_db
from app.dependencies import get_current_user, require_admin
from app.schemas import EmployeeCreate, EmployeeListResponse, EmployeeResponse, EmployeeUpdate, Pagination

router = APIRouter(prefix="/employees", tags=["Employees"])
Db = Annotated[AsyncSession, Depends(get_db)]
CurrentUser = Annotated[User, Depends(get_current_user)]
AdminUser = Annotated[User, Depends(require_admin)]

@router.post("", response_model=EmployeeResponse, status_code=status.HTTP_201_CREATED)
async def create_employee(payload: EmployeeCreate, db: Db, _: AdminUser) -> Employee:
    if await db.scalar(select(Employee.employee_id).where(Employee.email == str(payload.email))):
        raise HTTPException(status_code=409, detail="An employee with this email already exists")
    employee = Employee(**payload.model_dump())
    db.add(employee)
    try:
        await db.flush()
        await db.refresh(employee)
    except IntegrityError as exc:
        await db.rollback()
        raise HTTPException(status_code=409, detail="An employee with this email already exists") from exc
    return employee

@router.get("", response_model=EmployeeListResponse[EmployeeResponse])
async def list_employees(
    db: Db,
    _: CurrentUser,
    page: Annotated[int, Query(ge=1)] = 1,
    page_size: Annotated[int, Query(ge=1, le=100)] = 20,
    sort_by: Literal["first_name", "last_name", "department", "date_of_joining"] = "last_name",
    sort_order: Literal["asc", "desc"] = "asc",
    department: str | None = None,
    employment_status: EmploymentStatus | None = None,
) -> EmployeeListResponse[EmployeeResponse]:
    filters = []
    if department:
        filters.append(Employee.department == department)
    if employment_status:
        filters.append(Employee.employment_status == employment_status)
    total = await db.scalar(select(func.count()).select_from(Employee).where(*filters)) or 0
    order_column = getattr(Employee, sort_by)
    order = order_column.desc() if sort_order == "desc" else order_column.asc()
    rows = await db.scalars(select(Employee).where(*filters).order_by(order, Employee.employee_id).offset((page - 1) * page_size).limit(page_size))
    items = list(rows.all())
    return EmployeeListResponse(items=items, pagination=Pagination(page=page, page_size=page_size, total_records=total, total_pages=math.ceil(total / page_size)))

@router.get("/{employee_id}", response_model=EmployeeResponse)
async def get_employee(employee_id: int, db: Db, _: CurrentUser) -> Employee:
    employee = await db.get(Employee, employee_id)
    if employee is None:
        raise HTTPException(status_code=404, detail="Employee not found")
    return employee

@router.put("/{employee_id}", response_model=EmployeeResponse)
async def update_employee(employee_id: int, payload: EmployeeUpdate, db: Db, _: AdminUser) -> Employee:
    employee = await db.get(Employee, employee_id)
    if employee is None:
        raise HTTPException(status_code=404, detail="Employee not found")
    changes = payload.model_dump(exclude_unset=True)
    if "email" in changes and changes["email"] is not None:
        changes["email"] = str(changes["email"])
        duplicate = await db.scalar(select(Employee.employee_id).where(Employee.email == changes["email"], Employee.employee_id != employee_id))
        if duplicate:
            raise HTTPException(status_code=409, detail="An employee with this email already exists")
    for key, value in changes.items():
        setattr(employee, key, value)
    try:
        await db.flush()
        await db.refresh(employee)
    except IntegrityError as exc:
        await db.rollback()
        raise HTTPException(status_code=409, detail="An employee with this email already exists") from exc
    return employee

@router.delete("/{employee_id}", status_code=status.HTTP_204_NO_CONTENT)
async def delete_employee(employee_id: int, db: Db, _: AdminUser) -> None:
    employee = await db.get(Employee, employee_id)
    if employee is None:
        raise HTTPException(status_code=404, detail="Employee not found")
    await db.delete(employee)
