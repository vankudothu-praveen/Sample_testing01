# Employee Management API

A FastAPI service for employee records with PostgreSQL persistence, JWT bearer authentication, ADMIN/USER authorization, paginated/filterable employee listing, structured errors, and tests.

## Requirements
- Python 3.11+
- PostgreSQL 14+ (or Docker Compose)

## Run locally
```bash
cp .env.example .env
# Update DATABASE_URL and set a strong JWT_SECRET_KEY
python -m venv .venv && source .venv/bin/activate
pip install -r requirements.txt
alembic upgrade head
python -m app.create_admin --username admin --password 'change-me'
uvicorn app.main:app --reload
```

Swagger UI: http://localhost:8000/docs

Docker option: `docker compose up --build`. The service waits for PostgreSQL; apply migrations and create an admin user using the commands above (from a local Python environment configured for the same database).

## Authentication and roles
`POST /api/v1/auth/login` accepts `{"username":"...","password":"..."}` and returns a bearer token. Create initial users with the CLI; never commit real credentials or secrets. ADMIN can create/update/delete employees; ADMIN and USER can read. Tokens carry user ID, username, and role and expire according to configuration.

## Employee endpoints
- `POST /api/v1/employees` (ADMIN): create (201)
- `GET /api/v1/employees/{employee_id}` (authenticated): read (200)
- `GET /api/v1/employees` (authenticated): list with `page`, `page_size` (max 100), `sort_by`, `sort_order`, `department`, `employment_status`
- `PUT /api/v1/employees/{employee_id}` (ADMIN): update supplied fields (200)
- `DELETE /api/v1/employees/{employee_id}` (ADMIN): delete (204)

Employee fields: first_name, last_name, email, department, job_title, date_of_joining (ISO date), employment_status (ACTIVE, INACTIVE, TERMINATED). Email is unique. Invalid input returns 422, duplicate email 409, missing record 404, unauthenticated 401, and insufficient role 403. Errors use a consistent JSON shape.

## Configuration
See `.env.example`. The default local URL uses asyncpg. Keep `.env` out of version control. Set `JWT_SECRET_KEY` to a strong random value in every deployed environment.

## Migrations
```bash
alembic upgrade head
alembic revision --autogenerate -m "describe change"
```

## Tests
```bash
pytest
```
Tests cover schemas/security and API behavior using an isolated SQLite async database; production persistence uses PostgreSQL.
