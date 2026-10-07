import asyncio
import pytest
from fastapi.testclient import TestClient
from sqlalchemy.ext.asyncio import async_sessionmaker, create_async_engine
from sqlalchemy.pool import StaticPool
from app.db.base import Base
from app.db.models import User, UserRole
from app.db.session import get_db
from app.main import app
from app.security import create_access_token, hash_password

@pytest.fixture
def client():
    engine = create_async_engine("sqlite+aiosqlite://", connect_args={"check_same_thread": False}, poolclass=StaticPool)
    session_factory = async_sessionmaker(engine, expire_on_commit=False)

    async def setup():
        async with engine.begin() as conn:
            await conn.run_sync(Base.metadata.create_all)
        async with session_factory() as db:
            db.add_all([
                User(username="admin", password_hash=hash_password("admin-pass"), role=UserRole.ADMIN),
                User(username="reader", password_hash=hash_password("reader-pass"), role=UserRole.USER),
            ])
            await db.commit()
    asyncio.run(setup())

    async def override_get_db():
        async with session_factory() as db:
            try:
                yield db
                await db.commit()
            except Exception:
                await db.rollback()
                raise
    app.dependency_overrides[get_db] = override_get_db
    with TestClient(app) as test_client:
        test_client.admin_headers = {"Authorization": f"Bearer {create_access_token(user_id=1, username='admin', role='ADMIN')}"}
        test_client.user_headers = {"Authorization": f"Bearer {create_access_token(user_id=2, username='reader', role='USER')}"}
        yield test_client
    app.dependency_overrides.clear()
    asyncio.run(engine.dispose())

@pytest.fixture
def employee_payload():
    return {"first_name": "Ada", "last_name": "Lovelace", "email": "ada@example.com", "department": "Engineering", "job_title": "Analyst", "date_of_joining": "2024-01-10", "employment_status": "ACTIVE"}
