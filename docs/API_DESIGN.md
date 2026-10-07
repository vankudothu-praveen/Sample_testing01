# Employee Management API Design

Base URI: `/api/v1` (URI versioning). Authentication: JWT bearer tokens. Database: PostgreSQL through SQLAlchemy async ORM, managed with Alembic.

## Requirement traceability

| Requirement | Implementation |
|---|---|
| Create employee | `POST /employees`, `EmployeeCreate`, admin dependency |
| Read employee by ID | `GET /employees/{employee_id}`, authenticated admin/user |
| Paginated list | `GET /employees`, page/page_size, total metadata |
| Update employee | `PUT /employees/{employee_id}`, admin dependency |
| Delete employee | `DELETE /employees/{employee_id}`, admin dependency |
| Employee data fields | Employee ORM model and Pydantic schemas |
| JWT authentication | `POST /auth/login`, signed expiring bearer token |
| ADMIN/USER RBAC | `app/dependencies.py`; write routes require ADMIN |
| PostgreSQL | `DATABASE_URL`, asyncpg, Alembic initial migration |
| Required fields, email format, uniqueness | Pydantic EmailStr/field validation and DB unique constraint; conflicts return 409 |
| Error handling | Validation and generic handlers in `app/main.py`; endpoint-specific HTTP errors |
| Logging | Request completion/failure logs with request IDs and duration |
| Unit tests | `tests/` with SQLite async database and TestClient |

## Endpoints

| Method | Path | Authorization | Result |
|---|---|---|---|
| POST | `/api/v1/auth/login` | Public | Access token |
| POST | `/api/v1/employees` | ADMIN | Create employee (201) |
| GET | `/api/v1/employees/{employee_id}` | ADMIN or USER | Employee (200) |
| GET | `/api/v1/employees` | ADMIN or USER | Items plus pagination metadata |
| PUT | `/api/v1/employees/{employee_id}` | ADMIN | Updated employee (200) |
| DELETE | `/api/v1/employees/{employee_id}` | ADMIN | No content (204) |

List supports `page` (>=1), `page_size` (1-100), `department`, `employment_status`, `sort_by` (first_name, last_name, department, date_of_joining), and `sort_order` (asc/desc). Status values: ACTIVE, INACTIVE, TERMINATED.

Common statuses: 401 invalid/missing authentication, 403 insufficient role, 404 unknown employee, 409 duplicate email, 422 invalid request, 500 unexpected server error. `.env.example` shows configuration keys; do not commit actual secrets.
