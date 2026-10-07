import argparse
import asyncio
from sqlalchemy import select
from app.db.models import User, UserRole
from app.db.session import SessionLocal, dispose_engine
from app.security import hash_password

async def create_admin(username: str, password: str) -> None:
    async with SessionLocal() as db:
        existing = await db.scalar(select(User).where(User.username == username))
        if existing:
            raise SystemExit(f"User {username!r} already exists")
        db.add(User(username=username, password_hash=hash_password(password), role=UserRole.ADMIN))
        await db.commit()
    await dispose_engine()

def main():
    parser = argparse.ArgumentParser(description="Create an administrator account")
    parser.add_argument("--username", required=True)
    parser.add_argument("--password", required=True)
    args = parser.parse_args()
    asyncio.run(create_admin(args.username, args.password))

if __name__ == "__main__":
    main()
